#include "mainview.h"
#include "ui_mainview.h"
#include "pch.hpp"
#include "customdatatypes.hpp"

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
    ui->btnStopServer->setEnabled(false);
    // start the ExchangeData slot when the signal newConnection is emmitted
    connect(m_server, &QTcpServer::newConnection, this, &MainView::ExchangeData);
    ReadVacancies("/home/alex/digest_formatter_GUI/diggest_formatter/textfile.txt");
}

/* Destructor */
MainView::~MainView()
{
    delete ui;
}


/* ----------------------- class functions --------------------- */

/* This method fills the list of the vacancies read
 * from the diggest.txt */
void MainView::PopulateVacanciesList()
{
    //For the list
    ui->listWidget->addItem("hello");
    for(unsigned int i = 0; i < 10; i++)
    {
        // Populate the list
        ui->listWidget->addItem(QString::number(i) + "item");
    }
}

/* Read the vacancies from exelfile.
 * @param InputFile The input file in .xlxs extension
 * @return VacanciesList The extracted list of vacancies
 */
void MainView::ReadVacancies(std::string InputFile)
{
    std::cout<< "Opening file" << std::endl;
    // Open the file
    std::ifstream infile(InputFile);
    // do a check
    if(!infile.is_open())
    {
        std::cout<< "The file was not opened correctly!\nTerminating\n" << std::endl;
        // trow or end the app here
        exit(-1);
    }

    std::cout<< "File opened correclty" << std::endl;
    //parse file here

   // close the file
    infile.close();


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
   // when clicked open a new window
   // select a file to open
   // parse it
   // fill the list
}

// this was automatically created using "go to slot" in the design view
void MainView::on_btnStartServer_clicked()
{
    // call the server and check if it succeds
    if(StartServer())
    {
        /* After the button is pressed, disable the start button and
         * enable the stop button
         */
        ui->btnStartServer->setEnabled(false);
        ui->btnStopServer->setEnabled(true);
    }
}


// this was automatically created using "go to slot" in the design view
void MainView::on_btnStopServer_clicked()
{
    // called when the button is pressed
    StopServer();

    /* After the button is pressed, enable the start button and
     * disable the stop button
     */
    ui->btnStartServer->setEnabled(true);
    ui->btnStopServer->setEnabled(false);
}


