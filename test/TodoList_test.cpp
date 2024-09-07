//
// Created by Davide Meta on 28/08/24.
//
#include <gtest/gtest.h>
#include "../Attivita.h"
#include "../TodoList.h"
#include <fstream>

// Test fixture for TodoList
class TodoListTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up initial state
        list.aggiungiAttivita(Attivita("Descrizione 1", false));
        list.aggiungiAttivita(Attivita("Descrizione 2", true));
    }

    TodoList list;
};

TEST_F(TodoListTest, AggiungiAttivitaTest) {
    Attivita att("Descrizione 3", false);
    list.aggiungiAttivita(att);

    auto attivita = list.getAttivita();
    EXPECT_EQ(attivita.size(), 3);
    EXPECT_EQ(attivita.back().getDescrizione(), "Descrizione 3");
}

TEST_F(TodoListTest, RimuoviAttivitaTest) {
    list.rimuoviAttivita(0);

    auto attivita = list.getAttivita();
    EXPECT_EQ(attivita.size(), 1);
    EXPECT_EQ(attivita.front().getDescrizione(), "Descrizione 2");
}

TEST_F(TodoListTest, RimuoviAttivitaInvalidIndexTest) {
    list.rimuoviAttivita(10); // Out of bounds

    auto attivita = list.getAttivita();
    EXPECT_EQ(attivita.size(), 2); // List size should remain the same
}

TEST_F(TodoListTest, SalvaSuDiscoTest) {
    std::string filename = "test_output.txt";
    list.salvaSuDisco(filename);

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "Descrizione 1|0");

    std::getline(file, line);
    EXPECT_EQ(line, "Descrizione 2|1");

    file.close();
    std::remove(filename.c_str()); // Clean up
}

TEST_F(TodoListTest, CaricaDaDiscoTest) {
    std::string filename = "test_input.txt";
    std::ofstream file(filename);
    file << "Descrizione 3|1\n";
    file << "Descrizione 4|0\n";
    file << "Descrizione 5|1\n";
    file.close();

    list.caricaDaDisco(filename);

    auto attivita = list.getAttivita();
    EXPECT_EQ(attivita.size(), 3);
    EXPECT_EQ(attivita[0].getDescrizione(), "Descrizione 3");
    EXPECT_TRUE(attivita[0].isCompletato());
    EXPECT_EQ(attivita[1].getDescrizione(), "Descrizione 4");
    EXPECT_FALSE(attivita[1].isCompletato());
    EXPECT_EQ(attivita[2].getDescrizione(), "Descrizione 5");
    EXPECT_TRUE(attivita[2].isCompletato());

    std::remove(filename.c_str()); // Clean up
}

TEST_F(TodoListTest, CountRemainingActivitiesTest) {
    list.aggiungiAttivita(Attivita("Descrizione 6", true));
    list.aggiungiAttivita(Attivita("Descrizione 7", true));

    list.aggiungiAttivita(Attivita("Descrizione 8", false));
    list.aggiungiAttivita(Attivita("Descrizione 9", false));

    //REMINDER: Il test da 3 attività rimaste perché è presente l'attività 1 in  Setup() che è falso
    EXPECT_EQ(list.countRemainingActivities(), 3);
}

TEST_F(TodoListTest, CercaAttivitaTest) {
    list.aggiungiAttivita(Attivita("Pane"));
    list.aggiungiAttivita(Attivita("Carne"));
    list.aggiungiAttivita(Attivita("Pesce"));
    list.aggiungiAttivita(Attivita("Pane"));

    std::vector<Attivita> risultati = list.cercaAttivita("Pane");
    EXPECT_EQ(risultati.size(), 2);
}