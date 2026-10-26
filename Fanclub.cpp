//
// Created by Johannes Trottmann on 26.10.26.
//

#include "fanclub.hpp"

std::string Mitglied::getName() {
    return Mitglied::nachname;
}

std::string Mitglied::getSurname() {
    return  Mitglied::vorname;
}

std::string Mitglied::getMail() {
    return Mitglied::anschrift + Mitglied::plz + Mitglied::ort ;
}

std::string Mitglied::getPhone() {
    return Mitglied::telephon;
}

std::string Mitglied::getEmail() {
    return Mitglied::email;
}

int Mitglied::getScore() {
    return Mitglied::score;
}

