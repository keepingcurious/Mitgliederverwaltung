//
// Created by Johannes Trottmann on 26.10.26.
//

#include "fanclub.hpp"

std::string Mitglied::getName() const{
    return Mitglied::nachname_;
}

std::string Mitglied::getSurname() const{
    return  Mitglied::vorname_;
}

std::string Mitglied::getDob() const{
    return Mitglied::geburtstag_;
}

std::string Mitglied::getMail() const{
    return Mitglied::anschrift_ + " " + std::to_string(Mitglied::plz_) + Mitglied::ort_ ;
}

std::string Mitglied::getPhone() const{
    return Mitglied::telephon_;
}

std::string Mitglied::getEmail() const{
    return Mitglied::email_;
}

std::string Mitglied::getEintritt() const{
    return Mitglied::eintritt_;
}

int Mitglied::getScore() const {
    return Mitglied::score_;
}

void Mitglied::setScore(int newScore) {
    Mitglied::score_ = newScore;
}

nlohmann::json openFile(const std::string& pfad) {
    try {
        // Datei zum Lesen öffnen
        std::ifstream eingabedatei(pfad);
        if (!eingabedatei.is_open()) {
            throw std::runtime_error("Konnte die Datei nicht öffnen. Existiert sie bereits?");
        }

        // JSON-Daten einlesen
        json j;
        eingabedatei >> j;
        return j;


    } catch (const json::parse_error& e) {
        std::cerr << "JSON-Formatierungsfehler: " << e.what() << "\n";
        throw;
    } catch (const std::exception& e) {
        std::cerr << "Fehler beim Lesen: " << e.what() << "\n";
        throw;
    }

}

std::vector<Mitglied> mitgliederEinlesen(const nlohmann::json& mitgliederJson) {
    std::vector<Mitglied> mitglieder;
    for (const auto& objekt:mitgliederJson)
    {
        mitglieder.emplace_back(
            objekt.value("vorname", ""),
            objekt.value("nachname", ""),
            objekt.value("geburtstag", ""),
            objekt.value("anschrift", ""),
            objekt.value("plz", 0),
            objekt.value("ort", ""),
            objekt.value("telephon", ""),
            objekt.value("email", ""),
            objekt.value("eintritt", ""),
            objekt.value("score", 0),
            objekt.value("mitgliedsnummer", 0));
    }
    return mitglieder;
}
template<typename BasicJsonType>
void to_json(BasicJsonType& mitgliederJson, const Mitglied& m) {
    mitgliederJson = nlohmann::ordered_json{
        {"vorname", m.vorname_},
        {"nachname", m.nachname_},
        {"geburtstag", m.geburtstag_},
        {"anschrift", m.anschrift_},
        {"plz", m.plz_},
        {"ort", m.ort_},
        {"telephon", m.telephon_},
        {"email", m.email_},
        {"score", m.score_},
            {"mitgliedsnummer", m.mitgliedsnummer_}
    };
}

void mitgliederSchreiben(const std::vector<Mitglied>& mitglieder, const std::string pfad) {
    nlohmann::ordered_json ausgabeJson = mitglieder;

    std::ofstream ausgabedatei(pfad);
    if (!ausgabedatei.is_open()) {
        std::cerr << "Fehler beim Lesen: " << std::endl;
    }
    else
        ausgabedatei << ausgabeJson.dump(4);
}
