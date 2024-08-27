//
// Created by Davide Meta on 27/08/24.
//

#ifndef ATTIVITA_H
#define ATTIVITA_H
#include <string>
#include <sstream>

class Attivita {
public:
    Attivita(const std::string &descrizione, bool completata = false)
        : descrizione(descrizione), completata(completata) {
    }

    std::string getDescrizione() const {
        return descrizione;
    }

    bool isCompletata() const {
        return completata;
    }

    void setCompletata(bool completata) {
        this->completata = completata;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << descrizione << "," << completata;
        return ss.str();
    }

    static Attivita fromString(const std::string &str) {
        std::stringstream ss(str);
        std::string descrizione;
        std::string completataStr;
        std::getline(ss, descrizione, ',');
        std::getline(ss, completataStr);
        bool completata = (completataStr == "1");
        return Attivita(descrizione, completata);
    }

private:
    std::string descrizione;
    bool completata;
};

#endif //ATTIVITA_H
