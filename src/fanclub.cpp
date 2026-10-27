//
// Created by Johannes Trottmann on 26.10.26.
//

#include "fanclub.hpp"

std::string Mitglied::getName() {
    return Mitglied::nachname_;
}

std::string Mitglied::getSurname() {
    return  Mitglied::vorname_;
}

std::chrono::year_month_day Mitglied::getDob() {
    return Mitglied::geburtstag_;
}

std::string Mitglied::getMail() {
    return Mitglied::anschrift_ + " " + std::to_string(Mitglied::plz_) + Mitglied::ort_ ;
}

std::string Mitglied::getPhone() {
    return Mitglied::telephon_;
}

std::string Mitglied::getEmail() {
    return Mitglied::email_;
}

int Mitglied::getScore() {
    return Mitglied::score_;
}

