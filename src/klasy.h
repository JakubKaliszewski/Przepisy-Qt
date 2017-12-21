#ifndef KLASY_H
#define KLASY_H

#include <QMainWindow>
#include <vector>
#include <QtSql>
#include <QMessageBox>
//#include <QStringList>
//#include <QStringListModel>
//#include <QSqlDatabase>
//#include <QSqlDriver>
//#include <QSqlError>
//#include <QSqlQuery>
//#include <QDebug>

//#include <QFile>


using namespace std;

class Przepis// : public QObject
{
    //Q_OBJECT

public:
    Przepis(){};
    ~Przepis(){};

public slots:

    /*SETY*/
    void setIDPrzepisu(int wartosc);
    void setTytul(QString wartosc);
    void setCzasPrzygotowania(int wartosc);
    void setPrzygotowanie(QString wartosc);
    void setOpis(QString wartosc);
    void addSkladniki(QString wartosc);
    void addIlosc(QString wartosc);
    void setIMG(QByteArray wartosc);
    void setIMG(QPixmap wartosc);

    /*GETY*/
    int getIDPrzepisu();
    QString getTytul();
    int getCzasPrzygotowania();
    QString getPrzygotowanie();
    QString getOpis();
    QString getSkladniki();
    QString getIlosc();
    QString getHTMLSkladnikIlosc();
    QString getIMG();


private:
    int idPrzepisu;
    QString tytul;
    int czasPrzygotowania;
    QString przygotowanie;
    QString opis;
    vector<QString> skladniki;
    vector<QString> ilosc;
    QString obraz;

};


class SkladnikNazwaIloscID
{
public:
    SkladnikNazwaIloscID(){};
    ~SkladnikNazwaIloscID(){};

public slots:
    /*SETY*/
    void setID(int wartosc);
    void setNazwa(QString wartosc);
    void setIlosc(QString wartosc);

    /*GETY*/
    int getID();
    QString getNazwa();
    QString getIlosc();

private:
    int ID;
    QString nazwa;
    QString ilosc;
};

void DodajPrzepisSQL(Przepis dodawany, vector<SkladnikNazwaIloscID> skladniki);

bool WczytajDaneZBazy(vector<Przepis>& przepisyObiekty);

bool WczytajSkladnikizBazy(vector<SkladnikNazwaIloscID>& ListaSkladnikow);

bool DodajSkladnikSQL(QString nazwaSkladnika);

#endif // KLASY_H
