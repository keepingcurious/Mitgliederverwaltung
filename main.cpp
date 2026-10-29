#include <iostream>
#include <fstream>
#include <QApplication>
#include <QPushButton>
#include "fanclub.hpp"
#include "nlohmann/json.hpp"
#include "spiele.hpp"

using json = nlohmann::json;


int main(int argc, char *argv[]) {
    const std::string dateipfad = "__USER_HOME__/repos/Mitgliederverwaltung/mitglieder.json";
    json mitgliederJson = openFile(dateipfad);
    std::vector<Mitglied> mitglieder;
    mitglieder = mitgliederEinlesen(mitgliederJson);

    mitgliederSchreiben(mitglieder, dateipfad);


    const std::string dateipfadSpieleBuli = "__USER_HOME__/repos/Mitgliederverwaltung/spieleBuli.json";
    const std::string dateipfadSpieleDfb = "__USER_HOME__/repos/Mitgliederverwaltung/spieleDfb.json";
    const std::string dateipfadSpieleUcl = "__USER_HOME__/repos/Mitgliederverwaltung/spieleUcl.json";


    /*// 1. Datei öffnen (nutzt deine vorhandene openFile-Funktion)
    nlohmann::json spieleJson = openFile(dateipfadSpieleBuli);

    // 2. OpenLigaDB-Daten parsen und NUR die Bayern-Spiele extrahieren
    std::vector<Spiel> bayernSpiele = parseBayernSpiele(spieleJson);

    // 3. Testweise ausgeben
    std::cout << "Anzahl der gefundenen Bayern-Spiele: " << bayernSpiele.size() << "\n";'*/

    std::vector<Spiel> spieleSaison;
    spieleSaison = ladeBayernSpiele(dateipfadSpieleBuli, dateipfadSpieleDfb, dateipfadSpieleUcl);
    auto [first, last] = std::ranges::unique(spieleSaison);
    spieleSaison.erase(first, last);
    std::cout<<"test"<<std::endl;

    QApplication app(argc, argv);

    QPushButton button("Hallo aus CLion mit Qt!");
    button.resize(300, 100);
    button.show();

    return app.exec();
}