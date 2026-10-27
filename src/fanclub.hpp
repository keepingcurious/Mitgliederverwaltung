#pragma once
#include<string>
#include<chrono>
#include<fstream>
#include<iostream>
#include<vector>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Mitglied {
public:
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getSurname() const;
    [[nodiscard]] std::string getDob() const;
    [[nodiscard]] std::string getMail() const;
    [[nodiscard]] std::string getPhone () const;
    [[nodiscard]] std::string getEmail() const;
    [[nodiscard]] std::string getEintritt () const;
    [[nodiscard]] int getScore() const;
    void setScore(int newScore);


    // Konstruktor
    Mitglied(std::string vorname, std::string nachname, std::string geburtstag, std::string anschrift,
        int plz, std::string ort, std::string telephon, std::string email, std::string eintritt,
        int score, int mitgliedsnummer):
        vorname_(std::move(vorname)), nachname_(std::move(nachname)),
        geburtstag_(std::move(geburtstag)), anschrift_(std::move(anschrift)), plz_(plz),
        ort_(std::move(ort)), telephon_(std::move(telephon)), email_(std::move(email)),
        eintritt_(std::move(eintritt)), score_(score), mitgliedsnummer_(mitgliedsnummer) {}

    Mitglied from_json(const json& j){
        std::string vorname = j.at("vorname").get<std::string>();
        std::string nachname = j.at("nachname").get<std::string>();
        std::string geburtstag = j.at("geburtstag").get<std::string>();
        std::string anschrift = j.at("anschrift").get<std::string>();
        int plz = j.at("plz").get<int>();
        std::string telephon = j.at("telephon").get<std::string>();
        std::string email = j.at("email").get<std::string>();
        std::string eintritt = j.at("eintritt").get<std::string>();
        int score = j.at("score").get<int>();
        int mitgliedsnummer = j.at("mitgliedsnummer").get<int>();

        return {vorname, nachname, geburtstag, anschrift, plz,
            anschrift, telephon, email, eintritt, score, mitgliedsnummer};
    }

    json toJson() const {
        return json{
            {"vorname",vorname_},
            {"nachname",nachname_},
            {"geburtstag",geburtstag_},
            {"anschrift",anschrift_},
            {"plz",plz_},
                {"ort",ort_},
            {"telephon",telephon_},
            {"email",email_},
            {"eintritt",eintritt_},
            {"score",score_}};

    }
    template<typename BasicJsonType>
    friend void to_json(BasicJsonType& mitgliederJson, const Mitglied& mitglied);

private:
    std::string vorname_;
    std::string nachname_;
    std::string geburtstag_;
    std::string anschrift_;
    int plz_;
    std::string ort_;
    std::string telephon_;
    std::string email_;
    std::string eintritt_;
    int score_;
    int mitgliedsnummer_;

};

nlohmann::json openFile(const std::string& pfad);

std::vector<Mitglied> mitgliederEinlesen(const nlohmann::json& j);

void mitgliederSchreiben(const std::vector<Mitglied>& mitglieder, std::string pfad);
