#include "nowyskladnik.h"
#include "ui_nowyskladnik.h"

nowyskladnik::nowyskladnik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nowyskladnik)
{
    ui->setupUi(this);
}

nowyskladnik::~nowyskladnik()
{
    delete ui;
}


void nowyskladnik::on_Zatwierdz_clicked()
{
    emit NowySkladnikDodano(ui->lineEdit->text());
    close();
}

void nowyskladnik::on_Anuluj_clicked()
{
    close();
}
