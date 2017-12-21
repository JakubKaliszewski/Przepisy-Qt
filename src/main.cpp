#include "mainwindow.h"
#include "initdb.h"
#include <QApplication>

vector<Przepis> listaObiektow;//ustawienie vectora jako obiektu globalnego


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!PolaczZBaza()) return 0;//utworzenie połączenia z bazą danych, gdy zwróci false-błąd to zamknie program
    MainWindow w;
    w.show();
    return a.exec();
}

