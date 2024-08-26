#include <iostream>
#include <fstream>
#include <vector>
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

class TodoList {
public:
    void aggiungiAttivita(const Attivita &attivita) {
        attivitaList.push_back(attivita);
    }

    void rimuoviAttivita(int index) {
        if (index >= 0 && index < attivitaList.size()) {
            attivitaList.erase(attivitaList.begin() + index);
        }
    }

    std::vector<Attivita> getAttivita() const {
        return attivitaList;
    }

    void salvaSuDisco(const std::string &filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto &attivita: attivitaList) {
                file << attivita.toString() << std::endl;
            }
            file.close();
        } else {
            std::cerr << "Impossibile aprire il file per la scrittura." << std::endl;
        }
    }

    void caricaDaDisco(const std::string &filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            attivitaList.clear();
            std::string line;
            while (std::getline(file, line)) {
                attivitaList.push_back(Attivita::fromString(line));
            }
            file.close();
        } else {
            std::cerr << "Impossibile aprire il file per la lettura." << std::endl;
        }
    }

private:
    std::vector<Attivita> attivitaList;
};

int main() {
}
