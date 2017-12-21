#ifndef FUNKCJE_H
#define FUNKCJE_H

#include "mainwindow.h"
#include <QApplication>
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


bool DatabaseConnect();
void DatabaseCloseConnect();
void DatabasePopulate();
void MOnSearchClicked();

#endif // FUNKCJE_H
