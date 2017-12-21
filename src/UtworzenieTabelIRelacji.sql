CREATE TABLE `Przepisy` (
	`ID_przepisu`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`Tytul`	TEXT NOT NULL,
	`Czas_przygotowania`	INTEGER NOT NULL,
	`Przygotowanie`	TEXT NOT NULL,
	`IMG`	BLOB NOT NULL
);
CREATE TABLE `sqlite_sequence` (
	`name`	TEXT,
	`seq`	TEXT
);
CREATE TABLE `Skladniki` (
	`ID_skladnika`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`Nazwa`	TEXT NOT NULL
);


CREATE TABLE `Ilosc` (
	`ID_ilosc`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`ID_skladnika`	INTEGER NOT NULL,
	`ID_przepisu`	INTEGER NOT NULL,
	`ilosc`	TEXT NOT NULL,
	FOREIGN KEY(ID_skladnika) REFERENCES Skladniki(ID_skladnika), 
	FOREIGN KEY(ID_przepisu) REFERENCES Przepisy(ID_przepisu)
);

