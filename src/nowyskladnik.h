#ifndef NOWYSKLADNIK_H
#define NOWYSKLADNIK_H

#include <QDialog>
#include <klasy.h>

extern vector<Przepis> listaObiektow;//ustawienie vectora jako obiektu globalnego


namespace Ui {
class nowyskladnik;
}

class nowyskladnik : public QDialog
{
    Q_OBJECT

public:
    explicit nowyskladnik(QWidget *parent = 0);
    ~nowyskladnik();

signals:
    void NowySkladnikDodano(QString);//gdy ma nastapic dodanie nowego skladnika

private slots:

    void on_Zatwierdz_clicked();

    void on_Anuluj_clicked();

private:
    Ui::nowyskladnik *ui;
};

#endif // NOWYSKLADNIK_H
