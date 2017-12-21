#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    okno = new dodajPrzepis(this);//metoda na heap, stertę

    connect(okno,SIGNAL(odswiezycListePrzepisow()),this,SLOT(UstawListePrzepisow()));


    WczytajDaneZBazy(listaObiektow);

    UstawListePrzepisow();//ustawia ListBox w mainwindow


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionZamknij_triggered()
{
    QApplication::quit();
}

void MainWindow::UstawListePrzepisow()
{
    // Create model
    listaPrzepisow = new QStringListModel(this);

    // Make data
    QStringList lista;

    int rozmiar = listaObiektow.size();
    for(int i = 0; i < rozmiar; i++)
    {
        lista.append(listaObiektow[i].getTytul());
    }

    // Populate our model
    listaPrzepisow->setStringList(lista);

    // Glue model and view together
    ui->listaPrzepisow->setModel(listaPrzepisow);
}

void MainWindow::on_listaPrzepisow_clicked(const QModelIndex &index)//odpowiedzialna za tresci w textBrowser
{
        ui->textBrowser->clear();

        ui->textBrowser->insertHtml(
                    "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.0//EN' 'http://www.w3.org/TR/REC-html40/strict.dtd'>"
                    "<html><head><meta name='qrichtext' content='1' /><style type='text/css'>"
                    "p, li { white-space: pre-wrap; }"
                    "</style></head><body style=' font-family:'Cantarell'; font-size:9pt; font-weight:400; font-style:normal;'>"
                    "<p align='center' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><span style=' font-size:20pt; font-weight:600;'>"
                    + listaObiektow[index.row()].getTytul() + "</span></p>"
                    "<p align='justify' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><span style=' font-size:12pt;'>"
                    + listaObiektow[index.row()].getOpis() + "</span></p>"
                    "<p align='justify' style='-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:20pt;'><br /></p>"
                    "<p style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><span style=' font-size:14pt; font-weight:600;'>Czas przygotowania: "
                    + QString::number(listaObiektow[index.row()].getCzasPrzygotowania()) + "</span><span style=' font-size:12pt;'> minut</span></p>"
                    "<p align='justify' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><span style=' font-size:14pt; font-weight:600;'>Składniki:</span><span style=' font-size:12pt;'> </span></p>"
                    "<p align='justify' style=' margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><span style=' font-size:12pt;'>"
                    + listaObiektow[index.row()].getHTMLSkladnikIlosc() + "</span></p>"
                    "<p style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><span style=' font-size:14pt; font-weight:600;'>Przygotowanie:</span></p>"
                    "<p align='justify'><span style=' font-size:12pt;'>"
                    + listaObiektow[index.row()].getPrzygotowanie() + "</p>"
                    "<p align='justify' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'>"
                    "<img src='" + listaObiektow[index.row()].getIMG() +"'/></p></body></html>"
                    );
}


void MainWindow::on_actionDodaj_Przepis_triggered()
{
    //dodajPrzepis okno;//metoda na stack, stos
    //okno.setModal(true);
    //okno.exec();

    okno->show();

}


