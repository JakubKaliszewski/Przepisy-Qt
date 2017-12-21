#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QMessageBox>
#include <vector>
#include "klasy.h"

using namespace std;

bool PolaczZBaza()//zwraca false gdy błąd z nawiązaniem połączenia
{
    QMessageBox messageBox;//utworzenie obiektu do wyświetlania komunikatów
    QString LokalizacjaBazy = "./bazaDanych";//zmienna ze ścieżką do Bazy Danych

    if(!QFile::exists(LokalizacjaBazy))//Sprawdzenie czy plik bazy danych istnieje
    {
        messageBox.critical(0,"Error","Plik bazy danych nie istnieje!<br>Nastąpi zamknięcie programu!");
        messageBox.setFixedSize(500,200);
        return false;
    }

    else//gdy plik bazodanowy isnieje
    {
        const QString DRIVER("QSQLITE");//ustawienie silnika sql

        if(QSqlDatabase::isDriverAvailable(DRIVER))//sprawdzenie czy istnieje polaczenie z kontrolerem bazy QSQLITE
        {
            QSqlDatabase bazaDanych = QSqlDatabase::addDatabase(DRIVER);//utworzenie obiektu bazodanowego na którym pracuje

            bazaDanych.setDatabaseName(LokalizacjaBazy);//podanie ścieżki pliku dla bazyDanych

            if(!bazaDanych.open())
            {
                messageBox.critical(0,"Error",bazaDanych.lastError().text());
                messageBox.setFixedSize(500,200);
                return false;
            }

            QSqlQuery zapytanie;
            if(!zapytanie.exec("PRAGMA foreign_keys = '1'")) return false;//ustawienie obslugi kluczy obcych w
            if(!zapytanie.exec("PRAGMA locking_mode = UNLOCKED")) return false;

            return true;
        }
        else
        {
            messageBox.critical(0,"Error","ERROR: no driver " + DRIVER + " available!");
            messageBox.setFixedSize(500,200);
            return false;
        }
    }
}


void ZamknijBaze()
{
    //bazaDanych.close();
}



//void DatabasePopulate()//wykonywanie zapytan do bazy
//{
//    QSqlQuery query;

//    if(!query.exec("INSERT INTO people(name) VALUES('Eddie Guerrero')"))
//        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
//    if(!query.exec("INSERT INTO people(name) VALUES('Gordon Ramsay')"))
//        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
//    if(!query.exec("INSERT INTO people(name) VALUES('Alan Sugar')"))
//        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
//    if(!query.exec("INSERT INTO people(name) VALUES('Dana Scully')"))
//        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
//    if(!query.exec("INSERT INTO people(name) VALUES('Lila	Wolfe')"))
//        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
//    if(!query.exec("INSERT INTO people(name) VALUES('Ashley Williams')"))
//        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
//    if(!query.exec("INSERT INTO people(name) VALUES('Karen Bryant')"))
//        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
//    if(!query.exec("INSERT INTO people(name) VALUES('Jon Snow')"))
//        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
//    if(!query.exec("INSERT INTO people(name) VALUES('Linus Torvalds')"))
//        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
//    if(!query.exec("INSERT INTO people(name) VALUES('Hayley Moore')"))
//        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
//}


//void OnSearchClicked()
//{
//    QSqlQuery query;
//    query.prepare("SELECT name FROM people WHERE id = ?");
//    query.addBindValue(mInputText->text().toInt());

//    if(!query.exec())
//        qWarning() << "MainWindow::OnSearchClicked - ERROR: " << query.lastError().text();

//    if(query.first())
//        mOutputText->setText(query.value(0).toString());
//    else
//        mOutputText->setText("person not found");
//}


#endif // INITDB_H
