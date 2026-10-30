//
// Created by Johannes Trottmann on 27.10.26.
//

#include <algorithm>
#include "spiele.hpp"
#include "fanclub.hpp"


// Konstruktor
Spiel::Spiel(std::string datum, std::string ort, std::string gegner, std::string wettbewerb, bool isAway)
    : datum_(std::move(datum)), ort_(std::move(ort)), gegner_(std::move(gegner)),
wettbewerb_(std::move(wettbewerb)), isAway_(isAway) {}

// Getters
std::string Spiel::getDatum() const {
    return datum_;
}
std::string Spiel::getOrt() const {
    return ort_;
}
std::string Spiel::getGegner() const {
    return gegner_;
}
bool Spiel::getIsAway() const {
    return Spiel::isAway_;
}
std::string Spiel::getWettbewerb() const {
    return Spiel::wettbewerb_;
}

// to_json für nlohmann::json / ordered_json
template<typename BasicJsonType>
void to_json(BasicJsonType& j, const Spiel& s) {
    j = nlohmann::ordered_json{
        {"datum", s.datum_},
        {"ort", s.ort_},
        {"gegner", s.gegner_},
        {"wettbewerb", s.wettbewerb_},
        {"isAway", s.isAway_}
    };
}

// from_json
template<typename BasicJsonType>
void from_json(const BasicJsonType& j, Spiel& s) {
    s.datum_ = j.value("datum", "");
    s.ort_ = j.value("ort", "");
    s.gegner_ = j.value("gegner", "");
    s.wettbewerb_ = j.value("wettbewer", "");
    s.isAway_ = j.value("isAway", false);
}

// Saison-Berechnung (August = Start der neuen Saison)
int getCurrentSeasonYear() {
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime{};
#if defined(_WIN32)
    localtime_s(&localTime, &nowTime);
#else
    localtime_r(&nowTime, &localTime);
#endif

    int currentYear = localTime.tm_year + 1900;
    int currentMonth = localTime.tm_mon + 1; // 1 = Januar, 8 = August

    if (currentMonth < 8) {
        return currentYear - 1;
    }
    return currentYear;
}

std::string getApiUrlForCurrentSeason() {
    return "https://api.openligadb.de/getmatchdata/bl1/" + std::to_string(getCurrentSeasonYear());
}

// Parst das OpenLigaDB-JSON und holt für Bayern-Spiele nur Datum und Ort
std::vector<Spiel> parseBayernSpiele(const nlohmann::json& openLigaJson) {
    std::vector<Spiel> bayernSpiele;

    if (!openLigaJson.is_array()) {
        return bayernSpiele;
    }

    for (const auto& match : openLigaJson) {
        std::string team1 = match["team1"].value("teamName", "");
        std::string team2 = match["team2"].value("teamName", "");

        std::string leagueName = match.value("leagueName", "");
        std::string ort = "";
        std::string wettbewerb = "";

        bool isTeam1Bayern = (team1.find("Bayern") != std::string::npos);
        bool isTeam2Bayern = (team2.find("Bayern") != std::string::npos);

        if (isTeam1Bayern || isTeam2Bayern) {
            std::string datum = match.value("matchDateTime", "");

            bool isAway = isTeam2Bayern;
            std::string gegner = isAway ? team1 : team2;

            if (leagueName.find("1. Fußball-Bundesliga") != std::string::npos) {
                wettbewerb = "Bundesliga";
            }
            else if (leagueName.find("DFB Pokal") != std::string::npos) {
                wettbewerb = "DFB Pokal";
            } else if ( leagueName.find("Champions League") != std::string::npos) {
                wettbewerb = "Champions League";
            }

            // Ort/Stadion aus der API auslesen
            std::string ort = "";
            if (match.contains("location") && !match["location"].is_null()) {
                ort = match["location"].value("locationCity", "");
                std::string stadium = match["location"].value("locationStadium", "");
                if (!stadium.empty()) {
                    ort = stadium + (ort.empty() ? "" : ", " + ort);
                }
            }

            // Fallback, falls kein Ort in der API eingetragen ist
            if (ort.empty()) {
                ort = (team1.find("Bayern") != std::string::npos) ? "München (Allianz Arena)" : "Auswärts (" + team1 + ")";
            }

            bayernSpiele.emplace_back(datum, ort, gegner, wettbewerb, isAway);
        }
    }

    return bayernSpiele;
}

std::vector<Spiel> ladeBayernSpiele(std::string blPfad, std::string dfbPfad, std::string uclPfad) {
    //
    nlohmann::json spieleBuLiJson;
    try {
        spieleBuLiJson = openFile(blPfad);
    } catch (const std::exception& e) {
        // Gibt dir den exakten Grund im GitHub-Log aus
        std::cerr << "Fehler in openFile: " << e.what() << std::endl;
        throw; // Oder sauber behandeln
    }


    // 2. OpenLigaDB-Daten parsen und NUR die Bayern-Spiele extrahieren
    std::vector<Spiel> spieleBuLi = parseBayernSpiele(spieleBuLiJson);

    //
    nlohmann::json spieleDfbJson = openFile(dfbPfad);

    // 2. OpenLigaDB-Daten parsen und NUR die Bayern-Spiele extrahieren
    std::vector<Spiel> spieleDfb = parseBayernSpiele(spieleDfbJson);

    //
    nlohmann::json spieleUclJson = openFile(uclPfad);

    // 2. OpenLigaDB-Daten parsen und NUR die Bayern-Spiele extrahieren
    std::vector<Spiel> spieleUcl = parseBayernSpiele(spieleUclJson);

    std::vector<Spiel> alleFcbSpiele;
    alleFcbSpiele.insert(alleFcbSpiele.end(), spieleBuLi.begin(), spieleBuLi.end());
    alleFcbSpiele.insert(alleFcbSpiele.end(), spieleDfb.begin(), spieleDfb.end());
    alleFcbSpiele.insert(alleFcbSpiele.end(), spieleUcl.begin(), spieleUcl.end());
    std::ranges::sort(alleFcbSpiele, [](const Spiel& a, const Spiel& b) {
        return a.getDatum() < b.getDatum();
    });
    return alleFcbSpiele;



}