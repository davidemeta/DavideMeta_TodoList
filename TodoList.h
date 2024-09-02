//
// Created by Davide Meta on 27/08/24.
//

#ifndef TODOLIST_H
#define TODOLIST_H
#include <fstream>
#include <vector>
#include <string>
#include "Attivita.h"

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

#endif //TODOLIST_H
