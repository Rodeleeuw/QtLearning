#include "mainview.h"
#include "ui_mainview.h"
#include "pch.hpp"
#include "customdatatypes.hpp"
#include "ExcelReader.hpp"

// port to listen
static int PORT_NUMBER = 23;
// wait constant
static int WAIT_MS = 200;

/* Constructor */
MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView),
    m_server(new QTcpServer(this)), // initialize the member in the initializer list
    m_socket(nullptr)

{
    ui->setupUi(this);
    // disable the stop button when the application start
    //ui->btnStopServer->setEnabled(false);
    // start the ExchangeData slot when the signal newConnection is emmitted
    connect(m_server, &QTcpServer::newConnection, this, &MainView::ExchangeData);
}

/* Destructor */
MainView::~MainView()
{
    delete ui;
}


/* ----------------------- class functions --------------------- */

/* This method fills the list of the vacancies read
 * from the diggest.txt */
void MainView::PopulateVacanciesList(std::string digest_file)
{
    // open and parse the request file
    ExcelReader reader( digest_file );
    reader.FillVacancies();
    // Fill the list
    for( auto& vacancy : reader.GetVacancies() )
    {
        // You need to convert the std string to QString first
        ui->listWidget->addItem( QString::fromStdString( vacancy.name ) );
    }
}



bool MainView::StartServer()
{
    bool result = m_server->listen(QHostAddress::Any, PORT_NUMBER);

    if(!result)
    {
        // display a message, pass the parent, title of window, message (repplace $1 with the actual error)
        QMessageBox::critical(this, tr("Echo Server"), tr("Unable to start the server: %1").arg(m_server->errorString()));
        return false;
    }
     return true;
}


void MainView::StopServer()
{
    // close the connection
    m_server->close();

    // chech that the socket is nor null and that is still open
    // if we dont check we take the risk of calling close() on a dangling pointer
    if((m_socket != nullptr) && m_socket->isOpen())
    {
        // close the socket
        m_socket->close();
    }
}


void MainView::ExchangeData()
{
    // ask the server to give us the socket for the next pending connection
    m_socket = m_server->nextPendingConnection();

    if(m_socket->isOpen())
    {
        connect(m_socket, &QTcpSocket::readyRead, this, &MainView::EchoReadData);
    }
}


// Read the data and send it back wrapped in some ersatz
// tags to make it clear it comes from the server
void MainView::EchoReadData()
{
    // print this to be sure that we got it from the server
    m_socket->write("<echoserver>\n");
    // create a QString to hold all the data we read
    QString result;
    // read the data and as long as there is more keep appengind it to the result
    while(!m_socket->atEnd())
    {
        result.append(m_socket->readAll());
        // wait for some time to ensure we get all the data
        m_socket->waitForReadyRead(WAIT_MS);
    }

    // convert into a char* with QPrintable and print it out
    m_socket->write(qPrintable(result));

    // close the tag
    m_socket->write("\n</echoserver>\n");
}

/* ------------------------- Call backs -------------------------- */
void MainView::on_btnOpenFile_clicked()
{
   // when clicked open a new window to select a file, the path is set to the home path
    QString digest_file = QFileDialog::getOpenFileName( this, "Open the reques file", QDir::homePath() );
    // Fill the vacancies, convert to std string first
    PopulateVacanciesList( digest_file.toStdString() );
}


void MainView::on_btnCloseApp_clicked()
{
   // close the application
    exit(0);
}
