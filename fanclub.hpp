#pragma once
#include<string>

class Mitglied {
public:
    std::string getName();
    std::string getPhone();
    std::string getMail();
    std::string getEmail();
    std::string getSurname();
    int getScore();

private:
    std::string vorname;
    std::string nachname;
    std::string geb;
    std::string plz;
    std::string ort;
    std::string anschrift;
    int score;
    std::string email;
    std::string telephon;



};