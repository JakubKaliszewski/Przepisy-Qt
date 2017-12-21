#include "wybierzskladniki.h"
#include "ui_wybierzskladniki.h"

wybierzskladniki::wybierzskladniki(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wybierzskladniki)
{
    ui->setupUi(this);
    okno = new nowyskladnik(this);//metoda na heap, stertę

    WczytajSkladnikizBazy(ListaSkladnikow);
    UstawListeSkladnikow(ListaSkladnikow);

    connect(okno,SIGNAL(NowySkladnikDodano(QString)),this,SLOT(onNowySkladnikDodano(QString)));

}

wybierzskladniki::~wybierzskladniki()
{
    delete ui;
}

void wybierzskladniki::on_DodajBrakujacy_clicked()
{

    okno->show();
}


void wybierzskladniki::onNowySkladnikDodano(QString nazwaSkladnika)
{
    //qDebug() << "Jestem TU";
    QMessageBox messageBox;//utworzenie obiektu do wyświetlania komunikatów

    nazwaSkladnika = nazwaSkladnika.toLower();//parsuje na małe litery
    //qDebug() << nazwaSkladnika;

    if (!DodajSkladnikSQL(nazwaSkladnika))//dodanie do BazySQL
    {
        messageBox.critical(0,"Error", "Składnik "+ nazwaSkladnika + " nie może zostać dodany!<br/>Być może istnieje już taki składnik.");
        messageBox.setFixedSize(500,200);
        return;
    }

    SkladnikNazwaIloscID obiekt;
    ListaSkladnikow.size();
    obiekt.setID(ListaSkladnikow.size());
    obiekt.setNazwa(nazwaSkladnika);

    ListaSkladnikow.push_back(obiekt);
    ui->Lista->addItem(nazwaSkladnika);//dodanie do widgetu wyswietlajacego liste

}

void wybierzskladniki::UstawListeSkladnikow(vector<SkladnikNazwaIloscID> &ListaSkladnikow)
{
    int rozmiar = ListaSkladnikow.size();
    for(int i = 0; i < rozmiar; i++)
    {
        ui->Lista->addItem(ListaSkladnikow[i].getNazwa());
    }
}

void wybierzskladniki::on_pushButton_clicked()
{
    vector<SkladnikNazwaIloscID> wysylany;
    int iloscWpisow = ui->Tabela->verticalHeader()->count();
    int iloscWszystkichSkladnikow = ListaSkladnikow.size();

    for(int i = 0; i < iloscWpisow; i++)
    {
        SkladnikNazwaIloscID obiekt;

        obiekt.setNazwa(ui->Tabela->item(i,0)->text());//1. kolumna, nazwa
        obiekt.setIlosc(ui->Tabela->item(i,1)->text());//2. kolumna ilosc

        for(int j = 0; j < iloscWszystkichSkladnikow; j++)// by odnalezc id kazdego ze skladnikow
        {
            if(ListaSkladnikow[j].getNazwa().compare(obiekt.getNazwa()) == 0)
            {
                obiekt.setID(ListaSkladnikow[j].getID());
                break;
            }
        }


         wysylany.push_back(obiekt);//dodanie obiektu do vectora
    }

    emit wybranoSkladniki(wysylany);
    close();
}
