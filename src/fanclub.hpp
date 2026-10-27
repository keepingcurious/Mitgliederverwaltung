#pragma once
#include<string>
#include<chrono>

class Mitglied {
public:
    std::string getName();
    std::string getSurname();

    std::chrono::year_month_day getDob();
    std::string getMail();
    std::string getPhone();
    std::string getEmail();

    int getScore();

    // Konstruktor
    Mitglied(std::string vorname, std::string nachname, std::chrono::year_month_day geburtstag, std::string anschrift,
        int plz, std::string ort, std::string telephon, std::string email, std::chrono::year_month_day eintritt,
        int score):
        vorname_(std::move(vorname)), nachname_(std::move(nachname)),
        geburtstag_(std::move(geburtstag)), anschrift_(std::move(anschrift)), plz_(plz),
        ort_(std::move(ort)), telephon_(std::move(telephon)), email_(std::move(email)),
        eintritt_(std::move(eintritt)), score_(score) {}

private:
    std::string vorname_;
    std::string nachname_;
    std::chrono::year_month_day geburtstag_;
    std::string anschrift_;
    int plz_;
    std::string ort_;
    std::string telephon_;
    std::string email_;
    std::chrono::year_month_day eintritt_;
    int score_;

};