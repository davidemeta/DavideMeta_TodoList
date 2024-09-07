//
// Created by Davide Meta on 28/08/24.
//
#include "gtest/gtest.h"
#include "../Attivita.h"

TEST(AttivitaTest, ConstructorTest) {
    Attivita att("Descrizione", true);
    EXPECT_EQ(att.getDescrizione(), "Descrizione");
    EXPECT_TRUE(att.isCompletato());
}

TEST(AttivitaTest, DefaultConstructorTest) {
    Attivita att("Descrizione");
    EXPECT_EQ(att.getDescrizione(), "Descrizione");
    EXPECT_FALSE(att.isCompletato());
}

TEST(AttivitaTest, SetCompletatoTest) {
    Attivita att("Descrizione", false);
    att.setCompletato(true);
    EXPECT_TRUE(att.isCompletato());
}

TEST(AttivitaTest, ToStringTest) {
    Attivita att("Descrizione", true);
    EXPECT_EQ(att.toString(), "Descrizione|1");
}

TEST(AttivitaTest, FromStringTest) {
    Attivita att = Attivita::fromString("Descrizione|1");
    EXPECT_EQ(att.getDescrizione(), "Descrizione");
    EXPECT_TRUE(att.isCompletato());

    Attivita att2 = Attivita::fromString("Descrizione|0");
    EXPECT_EQ(att2.getDescrizione(), "Descrizione");
    EXPECT_FALSE(att2.isCompletato());
}