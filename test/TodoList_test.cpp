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
        list.aggiungiAttivita(Attivita("Test 1", false));
        list.aggiungiAttivita(Attivita("Test 2", true));
    }

    TodoList list;
};

TEST_F(TodoListTest, AggiungiAttivitaTest) {
    Attivita att("Test 3", false);
    list.aggiungiAttivita(att);

    auto attivita = list.getAttivita();
    EXPECT_EQ(attivita.size(), 3);
    EXPECT_EQ(attivita.back().getDescrizione(), "Test 3");
}

TEST_F(TodoListTest, RimuoviAttivitaTest) {
    list.rimuoviAttivita(0);

    auto attivita = list.getAttivita();
    EXPECT_EQ(attivita.size(), 1);
    EXPECT_EQ(attivita.front().getDescrizione(), "Test 2");
}

TEST_F(TodoListTest, RimuoviAttivitaInvalidIndexTest) {
    list.rimuoviAttivita(10);  // Out of bounds

    auto attivita = list.getAttivita();
    EXPECT_EQ(attivita.size(), 2);  // List size should remain the same
}

TEST_F(TodoListTest, SalvaSuDiscoTest) {
    std::string filename = "test_output.txt";
    list.salvaSuDisco(filename);

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "Test 1,0");

    std::getline(file, line);
    EXPECT_EQ(line, "Test 2,1");

    file.close();
    std::remove(filename.c_str());  // Clean up
}

TEST_F(TodoListTest, CaricaDaDiscoTest) {
    std::string filename = "test_input.txt";
    std::ofstream file(filename);
    file << "Test 3,1\n";
    file << "Test 4,0\n";
    file.close();

    list.caricaDaDisco(filename);

    auto attivita = list.getAttivita();
    EXPECT_EQ(attivita.size(), 2);
    EXPECT_EQ(attivita[0].getDescrizione(), "Test 3");
    EXPECT_TRUE(attivita[0].isCompletata());
    EXPECT_EQ(attivita[1].getDescrizione(), "Test 4");
    EXPECT_FALSE(attivita[1].isCompletata());

    std::remove(filename.c_str());  // Clean up
}