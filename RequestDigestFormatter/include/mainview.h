#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "customdatatypes.hpp"

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

    void on_listWidget_itemSelectionChanged();

private:
    Ui::MainView *ui;
    std::vector<vacancy> m_vacancies;

    void PopulateVacanciesList( std::string digest_file );
};

#endif // MAINVIEW_H
