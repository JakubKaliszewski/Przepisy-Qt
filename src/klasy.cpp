#include <klasy.h>

using namespace std;

/*SETY*/
void Przepis::setIDPrzepisu(int wartosc)
{
    this->idPrzepisu = wartosc;
}

void Przepis::setTytul(QString wartosc)
{
    this->tytul = wartosc;
}

void Przepis::setCzasPrzygotowania(int wartosc)
{
    this->czasPrzygotowania = wartosc;
}

void Przepis::setPrzygotowanie(QString wartosc)
{
    this->przygotowanie = wartosc;
}

void Przepis::setOpis(QString wartosc)
{
    this->opis = wartosc;
}

void Przepis::addSkladniki(QString wartosc)
{
    this->skladniki.push_back(wartosc);
}

void Przepis::addIlosc(QString wartosc)
{
    this->ilosc.push_back(wartosc);
}

void Przepis::setIMG(QByteArray wartosc)
{
    //QByteArray outByteArray = query.value( 0 ).toByteArray();
    QPixmap zwracanyobraz = QPixmap();
    QString nazwa;

    zwracanyobraz.loadFromData(wartosc);
    nazwa.append(this->getTytul()+".png");
    zwracanyobraz.save(nazwa, "PNG");
    this->obraz = nazwa;
}


void Przepis::setIMG(QPixmap wartosc)
{
    QString nazwa;

    nazwa.append(this->getTytul()+".png");
    wartosc.save(nazwa, "PNG");
    this->obraz = nazwa;
}

/*GETY*/

QString Przepis::getTytul()
{
    return this->tytul;
}

int Przepis::getIDPrzepisu()
{
    return this->idPrzepisu;
}

int Przepis::getCzasPrzygotowania()
{
    return this->czasPrzygotowania;
}

QString Przepis::getPrzygotowanie()
{
    return this->przygotowanie;
}

QString Przepis::getOpis()
{
    return this->opis;
}

QString Przepis::getSkladniki()
{
    int rozmiar = this->skladniki.size();
    QString zwracany;
    for(int i = 0; i < rozmiar; i++)
    {
        zwracany.append(this->skladniki[i] + "\n");
        //qDebug() << zwracany;
    }

    return zwracany;
}

QString Przepis::getIlosc()
{
    int rozmiar = this->ilosc.size();
    QString zwracany;
    for(int i = 0; i < rozmiar; i++)
    {
        zwracany.append(this->ilosc[i] + "\n");
    }

    return zwracany;
}

QString Przepis::getHTMLSkladnikIlosc()
{
    int rozmiar = this->skladniki.size();//bo skladnikow jest tyle samo co ich ilosci

    QString zwracany = "<ul>";
    for(int i = 0; i < rozmiar; i++)
    {
        zwracany.append("<li>" + this->skladniki[i] + " " + this->ilosc[i] + "</li>");
    }

    zwracany.append("</ul>");
    return zwracany;
}

QString Przepis::getIMG()
{
    return this->obraz;
}

/*KLASA SKLADNIKNAZWAILOSCID*/

/*SETY*/
void SkladnikNazwaIloscID::setID(int wartosc)
{
    this->ID = wartosc;
}

void SkladnikNazwaIloscID::setNazwa(QString wartosc)
{
    this->nazwa = wartosc;
}

void SkladnikNazwaIloscID::setIlosc(QString wartosc)
{
    this->ilosc = wartosc;
}
/*GETY*/
int SkladnikNazwaIloscID::getID()
{
    return this->ID;
}

QString SkladnikNazwaIloscID::getNazwa()
{
    return this->nazwa;
}

QString SkladnikNazwaIloscID::getIlosc()
{
    return this->ilosc;
}


/*POZOSTAŁE FUNKCJE I METODY*/


void DodajPrzepisSQL(Przepis dodawany, vector<SkladnikNazwaIloscID> skladniki)
{
    //QSqlDatabase db = QSqlDatabase::database("QSQLITE"); // it's already open!
    //QSqlQuery zapytanieUpdate(db);
//    if (!zapytanieUpdate.exec("PRAGMA foreign_keys = '0'"))
//    {
//        qDebug() << "   KLUCZ!***ERROR - update: "
//                << zapytanieUpdate.lastError().text();
//        qDebug() << "   ***query" << zapytanieUpdate.executedQuery();
//    }

    //QSqlQuery zapytanie;
    //QSqlQuery zapytanie2;
    QSqlQuery zapytanieUpdate;

    QFile file(dodawany.getIMG());//otrzymanie obrazu z obiektu
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray obraz = file.readAll();//zamiana na ciag bitów


    QSqlDatabase::database().transaction();
    QString cos;
//    cos.append("INSERT INTO `Przepisy`(`Tytul`) "
//               "VALUES ('"
//               + dodawany.getTytul() + "');" );

//    zapytanie.prepare("INSERT INTO `Przepisy`(`Tytul`) "
//                   "VALUES ('"
//                   + dodawany.getTytul() + "');" );


    zapytanieUpdate.prepare("INSERT INTO `Przepisy`(`ID_Przepisu`,`Tytul`,`Czas_przygotowania`,`Przygotowanie`,`IMG`,`Opis`) "
                   "VALUES ('"
                   + QString::number(dodawany.getIDPrzepisu()) + "','"
                   + dodawany.getTytul() + "','"
                   + QString::number(dodawany.getCzasPrzygotowania()) + "','"
                   + dodawany.getPrzygotowanie() + "',"
                   + ":grafika,'"
                   + dodawany.getOpis() + "');" );
    zapytanieUpdate.bindValue(":grafika", obraz);
//    query.prepare( "INSERT INTO imgTable (filename, imagedata) VALUES ('screenshot.png', :imageData)" );
//    query.bindValue( ":imageData", inByteArray );

    //qDebug()<<cos;

    if(!zapytanieUpdate.exec())
    {
        qDebug()<<"Zapytanie 1. nie wykonane!";
        qDebug() << "   ***ERROR - update: "
                << zapytanieUpdate.lastError().text();
        qDebug() << "   ***query" << zapytanieUpdate.executedQuery();
        return;
    }
    //qDebug()<<zapytanie.isActive();
    //zapytanie.finish();
    //qDebug()<<zapytanie.isActive();

    //zapytanie2.exec("Select * From Ilosc");

    for(int i = 0; i < skladniki.size(); i++)
    //for(int i = 0; i < 1; i++)
    {
        cos.clear();
        zapytanieUpdate.prepare("INSERT INTO `Ilosc` (`ID_skladnika`,`ID_przepisu`,`ilosc`)"
                       "VALUES ('"
                       + QString::number(skladniki[i].getID()) + "','"
                       + QString::number(dodawany.getIDPrzepisu()) + "','"
                       + skladniki[i].getIlosc() + "');" );

        cos.append("INSERT INTO `Ilosc` (`ID_skladnika`,`ID_przepisu`,`ilosc`)"
                    "VALUES ('"
                    + QString::number(skladniki[i].getID()) + "','"
                    + QString::number(dodawany.getIDPrzepisu()) + "','"
                    + skladniki[i].getIlosc() + "');" );

        if (!zapytanieUpdate.exec())
        {
            qDebug() << "   ***ERROR - update: "
                    << zapytanieUpdate.lastError().text();
            qDebug() << "   ***query" << zapytanieUpdate.executedQuery();
        }
    }

    if(!QSqlDatabase::database().commit())
        qDebug()<<"Brak obslugi!";

}

bool WczytajDaneZBazy(vector<Przepis>& przepisyObiekty)
{
    QMessageBox messageBox;//utworzenie obiektu do wyświetlania komunikatów
    QSqlQuery zapytanie;//utworzenie obiektu na przechowanie zapytania
    QSqlQuery zapytanie2;

    zapytanie.prepare("SELECT * FROM Przepisy");

    if(!zapytanie.exec())
    {
        messageBox.critical(0,"Error", "Nie można załadować przepisów z Bazy!!\nNastąpi zamknięcie programu.");
        messageBox.setFixedSize(500,200);
        return false; //bo zapytanie nie wykonane!
    }
    else
    {
        while (zapytanie.next())//->tresc while'a do dokończenia
        {
            Przepis obiekt;
            obiekt.setIDPrzepisu(zapytanie.value(0).toInt());
            obiekt.setTytul(zapytanie.value(1).toString());
            obiekt.setCzasPrzygotowania(zapytanie.value(2).toInt());
            obiekt.setPrzygotowanie(zapytanie.value(3).toString());
            obiekt.setIMG(zapytanie.value(4).toByteArray());
            obiekt.setOpis(zapytanie.value(5).toString());

            zapytanie2.prepare(
"SELECT Skladniki.Nazwa, Ilosc.ilosc FROM Skladniki, Ilosc WHERE Skladniki.ID_skladnika = Ilosc.ID_skladnika AND Ilosc.ID_przepisu = " + zapytanie.value(0).toString());

            if(!zapytanie2.exec())
            {
                messageBox.critical(0,"Error", "Nie można załadować przepisów z Bazy!!\nNastąpi zamknięcie programu.");
                messageBox.setFixedSize(500,200);
                return false; //bo zapytanie nie wykonane!
            }

            while(zapytanie2.next())
            {
                obiekt.addSkladniki(zapytanie2.value(0).toString());
                obiekt.addIlosc(zapytanie2.value(1).toString());
            }

            przepisyObiekty.push_back(obiekt);
        }
        return true;//wszystko wykonane!
    }
}


bool WczytajSkladnikizBazy(vector<SkladnikNazwaIloscID>& ListaSkladnikow)
{
    QMessageBox messageBox;//utworzenie obiektu do wyświetlania komunikatów
    QSqlQuery zapytanie;//utworzenie obiektu na przechowanie zapytania

    zapytanie.prepare("SELECT * FROM Skladniki");

    if(!zapytanie.exec())
    {
        messageBox.critical(0,"Error", "Nie można załadować skladnikow z Bazy!!\nNastąpi zamknięcie programu.");
        messageBox.setFixedSize(500,200);
        return false; //bo zapytanie nie wykonane!
    }
    else
    {
        while (zapytanie.next())
        {
            SkladnikNazwaIloscID obiekt;
            obiekt.setID(zapytanie.value(0).toInt());
            obiekt.setNazwa(zapytanie.value(1).toString());

            ListaSkladnikow.push_back(obiekt);
        }
        return true;//wszystko wykonane!
    }
}

bool DodajSkladnikSQL(QString nazwaSkladnika)
{
    QSqlQuery zapytanie;
    QMessageBox messageBox;//utworzenie obiektu do wyświetlania komunikatów


    zapytanie.prepare("SELECT Nazwa FROM Skladniki");

    if(!zapytanie.exec())
    {
        messageBox.critical(0,"Error", "Nie można dodać składnika do Bazy!!");
        messageBox.setFixedSize(500,200);
        return false; //bo zapytanie nie wykonane!
    }

    while(zapytanie.next())
    {
        if(nazwaSkladnika.compare(zapytanie.value(0).toString()) == 0)
            return false;
    }

    zapytanie.prepare("INSERT INTO `Skladniki`(`Nazwa`) VALUES ('" + nazwaSkladnika + "');");

    if(!zapytanie.exec())
        return false;

    return true;
}
