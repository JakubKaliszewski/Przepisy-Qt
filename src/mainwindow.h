#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dodajprzepis.h"
#include "klasy.h"
#include <vector>
#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QFile>

using namespace std;

extern vector<Przepis> listaObiektow;//ustawienie vectora jako obiektu globalnego



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void wybranoPrzepis(QModelIndex, vector<Przepis>);


private slots:
    //void onFontChanged(QString);

    void on_actionZamknij_triggered();

    void on_listaPrzepisow_clicked(const QModelIndex &index);

    void UstawListePrzepisow();
    //vector<Przepis>& przepisyObiekty
    //void odbiorca(vector<Przepis>& przepisyObiekty);


    void on_actionDodaj_Przepis_triggered();

    //void onwybranoPrzepis(const QModelIndex &index, vector<Przepis>& przepisyObiekty);
    
    //void on_listaPrzepisow_clicked(const QModelIndex &index, vector<Przepis>& przepisyObiekty);

    //void WyswietlPrzepis(vector<Przepis>& przepisyObiekty);


private:
    Ui::MainWindow *ui;
    dodajPrzepis *okno;

    QStringListModel *listaPrzepisow;//do listy
/*
     * QStringListModel is an editable model that can be used for simple cases
     * where you need to display a number of strings in a view widget,
     * such as a QListView or a QComboBox.
     *
*/

};

#endif // MAINWINDOW_H
