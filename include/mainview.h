#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
class MainView;
}


class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private slots:
    void on_btnOpenFile_clicked();
    void on_btnCloseApp_clicked();

private:
    Ui::MainView *ui;

    // generated using the refactoring tool
    void PopulateVacanciesList(std::string digest_file );
};

#endif // MAINVIEW_H
