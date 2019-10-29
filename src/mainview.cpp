#include "mainview.h"
#include "ui_mainview.h"
#include "pch.hpp"
#include "customdatatypes.hpp"
#include "ExcelReader.hpp"


/* Constructor */
MainView::MainView(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainView)
{
    ui->setupUi(this);
    // disable the stop button when the application start
    //ui->btnStopServer->setEnabled(false);
    // start the ExchangeData slot when the signal newConnection is emmitted
    //connect(m_server, &QTcpServer::newConnection, this, &MainView::ExchangeData);
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
    ui->textBrowser->setText("hi there");
}


/* ------------------------- Call backs -------------------------- */
void MainView::on_btnOpenFile_clicked()
{
    // Filter for the file selection
    QString filter = "All files (*.*) ;; Excel files (*.xlsx)";
   // when clicked open a new window to select a file, the path is set to the home path
    QString digest_file = QFileDialog::getOpenFileName( this, "Open the reques file", QDir::homePath(), filter );
    // Fill the vacancies, convert to std string first
    PopulateVacanciesList( digest_file.toStdString() );
    // Display a message box
    //QMessageBox::information( this, "Some message", digest_file );
}


void MainView::on_btnCloseApp_clicked()
{
   // close the application
    exit(0);
}
