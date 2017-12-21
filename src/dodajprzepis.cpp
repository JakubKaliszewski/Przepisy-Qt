#include "dodajprzepis.h"
#include "ui_dodajprzepis.h"

using namespace std;

dodajPrzepis::dodajPrzepis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodajPrzepis)
{
    ui->setupUi(this);
    okno = new wybierzskladniki(this);//metoda na heap, stertę


    obiekt = new Przepis();
    skladniki = new vector<SkladnikNazwaIloscID>;


    connect(okno,SIGNAL(wybranoSkladniki(vector<SkladnikNazwaIloscID>)),this,SLOT(onWybranoSkladniki(vector<SkladnikNazwaIloscID>)));

}

dodajPrzepis::~dodajPrzepis()
{
    delete ui;
}

void dodajPrzepis::onWybranoSkladniki(vector<SkladnikNazwaIloscID> Skladniki)
{
    ui->pushButton_3->setEnabled(false);
    skladniki->assign(Skladniki.begin(), Skladniki.end());
    //skladniki = Skladniki;
    //Dodanie do obiektu tych danych
    int iloscSkladnikow = Skladniki.size();

    for(int i = 0; i < iloscSkladnikow; i++)
    {
        obiekt->addSkladniki(Skladniki[i].getNazwa());
        obiekt->addIlosc(Skladniki[i].getIlosc());
    }
    //ID skladnika do SQL TEŻ POTRZEBA, CAły nowy obiekt ma już wszystkie dane, lecz to sprawdź w debug
}


void dodajPrzepis::on_pushButton_3_clicked()
{
    okno->show();
}


    //odebranie sygnału z listą obiektów
    //stworzenie nowego obiektu, następnie dodanie go do listy
    //dodanie nowego przepisu do bazy danych--tu wymagane wszystko
    //lista skladnik + lista ilosc
    //wysłanie sygnału z listą do okna głównego



//dodanie IMG do bazy SQL
// Set up database
//   QString dbName( "myDatabase.db3" );
//   QFile::remove( dbName ); // delete sqlite file if it exists from a previous run
//   QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
//   db.setDatabaseName( dbName );
//   db.open();
//   QSqlQuery query = QSqlQuery( db );
//   query.exec( "CREATE TABLE IF NOT EXISTS imgTable ( filename TEXT, imagedata BLOB )" );

//   // Generate an image (in this case a screenshot) and store it in a QByteArray
//   QScreen *screen = app.primaryScreen();
//   QPixmap inPixmap = screen->grabWindow( 0 );
//   QByteArray inByteArray;
//   QBuffer inBuffer( &inByteArray );
//   inBuffer.open( QIODevice::WriteOnly );
//   inPixmap.save( &inBuffer, "PNG" ); // write inPixmap into inByteArray in PNG format

//   // Alternatively, load an image file directly into a QByteArray
//   // QFile file("screenshot.png");
//   // if (!file.open(QIODevice::ReadOnly)) return;
//   // QByteArray inByteArray = file.readAll();

//   // Insert image bytes into the database
//   // Note: make sure to wrap the :placeholder in parenthesis
//   query.prepare( "INSERT INTO imgTable (filename, imagedata) VALUES ('screenshot.png', :imageData)" );
//   query.bindValue( ":imageData", inByteArray );
//   if( !query.exec() )
//       qDebug() << "Error inserting image into table:\n" << query.lastError();

//   // Get image data back from database
//   if( !query.exec( "SELECT imagedata from imgTable" ))
//       qDebug() << "Error getting image from table:\n" << query.lastError();
//   query.first();
//   QByteArray outByteArray = query.value( 0 ).toByteArray();
//   QPixmap outPixmap = QPixmap();
//   outPixmap.loadFromData( outByteArray );
//   db.close();

//   // Display image
//   QLabel myLabel;
//   myLabel.setPixmap( outPixmap );
//   myLabel.show();

void dodajPrzepis::on_OKButton_clicked()
{
    //Dodaj do obiektu
    obiekt->setIDPrzepisu(listaObiektow.size()+1);
    obiekt->setTytul(ui->tytul->text());
    obiekt->setOpis(ui->opis->toPlainText());
    obiekt->setCzasPrzygotowania(ui->minuty->text().toInt());
    obiekt->setPrzygotowanie(ui->przygotowanie->toPlainText());

    listaObiektow.push_back(*obiekt);


    DodajPrzepisSQL(*obiekt, *skladniki);

    close();
    emit odswiezycListePrzepisow();
}

void dodajPrzepis::on_AnulujButton_clicked()
{
    delete obiekt;
    close();
    //CzyscFormularz();
}

void dodajPrzepis::on_ZdjecieButton_clicked()
{
   QString sciezkaObraz = QFileDialog::getOpenFileName(this,
         tr("Wybierz zdjęcie do dania..."), ".", tr("Obrazy (*.png *.xpm *.jpg)"));

    QPixmap obraz, miniaturka;
    obraz.load(sciezkaObraz);//zaladowanie obrazu
    miniaturka = obraz.scaled(180,101,Qt::KeepAspectRatio);//skala do miniaturki
    QGraphicsScene *scena = new QGraphicsScene;//utworzenie sceny na potrzeby graphicsview

    scena->addPixmap(miniaturka);//sekcja za miniaturkę w formularzu
    ui->graphicsView->setScene(scena);
    ui->graphicsView->show();

    obraz = obraz.scaled(720,405,Qt::KeepAspectRatio);//skala ustawiona do zapisu w bazie
    obiekt->setIMG(obraz);//ustawienie obrazu w obiekcie

}

void dodajPrzepis::CzyscFormularz()
{
    ui->graphicsView->clearMask();
    ui->minuty->clear();
    ui->opis->clear();
    ui->przygotowanie->clear();
    ui->tytul->clear();
}
