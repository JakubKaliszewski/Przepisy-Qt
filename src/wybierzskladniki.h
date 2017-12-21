#ifndef WYBIERZSKLADNIKI_H
#define WYBIERZSKLADNIKI_H

#include <nowyskladnik.h>
#include <QDialog>
#include <klasy.h>

extern vector<Przepis> listaObiektow;//ustawienie vectora jako obiektu globalne


namespace Ui {
class wybierzskladniki;
}

class wybierzskladniki : public QDialog
{
    Q_OBJECT

public:
    explicit wybierzskladniki(QWidget *parent = 0);
    ~wybierzskladniki();
    vector<SkladnikNazwaIloscID> ListaSkladnikow;

signals:
    void wybranoSkladniki(vector<SkladnikNazwaIloscID>);

private slots:
    void on_DodajBrakujacy_clicked();
    void onNowySkladnikDodano(QString);
    void UstawListeSkladnikow(vector<SkladnikNazwaIloscID>& ListaSkladnikow);


    void on_pushButton_clicked();

private:
    Ui::wybierzskladniki *ui;
    nowyskladnik *okno;
};

#endif // WYBIERZSKLADNIKI_H
