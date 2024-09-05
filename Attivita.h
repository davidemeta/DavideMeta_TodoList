//
// Created by Davide Meta on 27/08/24.
//

#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <string>

class Attivita {
public:
    Attivita(const std::string &descrizione, bool completato = false)
        : descrizione(descrizione), completato(completato) {}

    std::string getDescrizione() const {
        return descrizione;
    }

    bool isCompletato() const {
        return completato;
    }

    void setCompletato(bool completato) {
        this->completato = completato;
    }

    std::string toString() const {
        return descrizione + "|" + (completato ? "1" : "0");
    }

    static Attivita fromString(const std::string &str) {
        size_t pos = str.find('|');
        std::string descrizione = str.substr(0, pos);
        bool completato = (str.substr(pos + 1) == "1");
        return Attivita(descrizione, completato);
    }

private:
    std::string descrizione;
    bool completato;
};

#endif // ATTIVITA_H