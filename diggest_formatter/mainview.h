#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
class MainView;
}

// forward declaration of the classess used for the TCP connection
class QTcpServer;
class QTcpSocket;

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private slots:
    void on_btnStartServer_clicked();
    void on_btnStopServer_clicked();


    void on_btnOpenFile_clicked();

private:
    Ui::MainView *ui;

    // pointer to a QTcpServer and socket variables
    QTcpServer* m_server;
    QTcpSocket* m_socket;

    // generated using the refactoring tool
    bool StartServer();
    void StopServer();
    void ExchangeData();
    void EchoReadData();
    void PopulateVacanciesList();
    void ReadVacancies(std::string InputFile);
};

#endif // MAINVIEW_H
