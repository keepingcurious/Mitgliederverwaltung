#include <iostream>
#include <fstream>
#include "fanclub.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    const std::string dateipfad = "/Users/johannes/repos/Mitgliederverwaltung/mitglieder.json";
    try {
        // Datei zum Lesen öffnen
        std::ifstream eingabedatei(dateipfad);
        if (!eingabedatei.is_open()) {
            throw std::runtime_error("Konnte die Datei nicht öffnen. Existiert sie bereits?");
        }

        // JSON-Daten einlesen
        json j;
        eingabedatei >> j;
        std::cout << j.dump(4) << std::endl;


    } catch (const json::parse_error& e) {
        std::cerr << "JSON-Formatierungsfehler: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Fehler beim Lesen: " << e.what() << "\n";
    }

    return 0;
}// TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.