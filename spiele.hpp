//
// Created by Johannes Trottmann on 27.10.26.
//
#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Spiel {
public:
    // Konstruktor (nur Datum und Ort)
    Spiel(std::string datum, std::string ort, std::string gegner, std::string wettbewerb, bool isAway);

    // Getters
    [[nodiscard]] std::string getDatum() const;
    [[nodiscard]] std::string getOrt() const;
    [[nodiscard]] std::string getGegner() const;
    [[nodiscard]] std::string getWettbewerb() const;
    [[nodiscard]] bool getIsAway() const;

    // JSON-Serialisierung
    template<typename BasicJsonType>
    friend void to_json(BasicJsonType& j, const Spiel& s);

    template<typename BasicJsonType>
    friend void from_json(const BasicJsonType& j, Spiel& s);

    bool operator==(const Spiel& other) const {
        return datum_ == other.datum_ &&
               ort_ == other.ort_ &&
               gegner_ == other.gegner_;
               wettbewerb_ == other.wettbewerb_;

    }

private:
    std::string datum_;
    std::string ort_;
    std::string gegner_;
    std::string wettbewerb_;
    bool isAway_;
};

// Ermittelt das Saisonjahr (Saisonstart im August)
[[nodiscard]] int getCurrentSeasonYear();

// Baut die API-URL auf
[[nodiscard]] std::string getApiUrlForCurrentSeason();

// Filtert nur Bayern-Spiele und liest Datum & Ort (Stadion) aus
std::vector<Spiel> parseBayernSpiele(const nlohmann::json& openLigaJson);

std::vector<Spiel> ladeBayernSpiele(std::string blPfad, std::string dfbPfad, std::string uclPfad);