#ifndef DODAJPRZEPIS_H
#define DODAJPRZEPIS_H

#include <wybierzskladniki.h>
#include <QAbstractButton>
#include <QDialog>
#include <QFileDialog>
#include <vector>
#include <klasy.h>

using namespace std;

extern vector<Przepis> listaObiektow;//ustawienie vectora jako obiektu globalnego


namespace Ui {
class dodajPrzepis;
}

class dodajPrzepis : public QDialog
{
    Q_OBJECT

public:
    explicit dodajPrzepis(QWidget *parent = 0);
    ~dodajPrzepis();

signals:
    void odswiezycListePrzepisow();


private slots:
    void onWybranoSkladniki(vector<SkladnikNazwaIloscID>);

    void on_pushButton_3_clicked();

    void on_OKButton_clicked();

    void on_AnulujButton_clicked();

    void on_ZdjecieButton_clicked();

    void CzyscFormularz();

private:
    Ui::dodajPrzepis *ui;
    wybierzskladniki *okno;
    Przepis *obiekt;
    vector<SkladnikNazwaIloscID> *skladniki;
};

#endif // DODAJPRZEPIS_H
