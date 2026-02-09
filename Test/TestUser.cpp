//
// Created by HP on 09/02/2026.
//

#include "gtest/gtest.h"
#include "../User.h"

TEST(UserTest, CreateList){
    User userName("Niccolò");
    userName.createList("Spesa");
    auto it = userName.getList("Spesa");
    ASSERT_NE(it , nullptr);
    EXPECT_EQ(it->getListName(), "Spesa");
}

TEST(UserTest, GetList){
    User userName("Niccolò");
    userName.createList("Spesa");
    auto it = userName.getList("Spesa");
    EXPECT_EQ(userName.getList("Spesa"), it);
    EXPECT_THROW(userName.getList("Prodotti Igiene"), std::invalid_argument);
}

TEST(UserTest, AddItemToList){
    User userName("Niccolò");
    userName.createList("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    userName.addItemToList("Spesa", vino);
    auto it = userName.getList("Spesa");
    ASSERT_NE(it, nullptr);
    EXPECT_EQ(it->getItemCount(), 1);
}

TEST(UserTest, RemoveItemFromList){
    User userName("Niccolò");
    userName.createList("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    userName.addItemToList("Spesa", vino);
    auto it = userName.getList("Spesa");
    EXPECT_EQ(userName.getList("Spesa"), it);
    userName.removeItemFromList("Spesa", "Vino");
    EXPECT_EQ(it->getItemCount(), 0);
    ASSERT_NE(userName.getList("Spesa"), nullptr);
}

TEST(TestUser, GetName){
    User userName("Niccolò");
    EXPECT_EQ(userName.getUserName(), "Niccolò");
}

TEST(TestUser, UpdateQuantity){
    User userName("Niccolò");
    userName.createList("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    userName.addItemToList("Spesa", vino);
    userName.updateQuantity("Spesa", "Vino", 2);
}

TEST(TestUser, UpdateStatus){
    User userName("Niccolò");
    userName.createList("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    userName.addItemToList("Spesa", vino);
    userName.updateStatus("Spesa", "Vino", true);
}

TEST(TestUser, ShareList){
    User* Niccolò = new User("Niccolò");
    User* Chiara= new User("Chiara");
    Niccolò->createList("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    Item cartaIG("Carta Igienica", 5, 2, 2026, "Rotoloni Regina", Category::Non_alimentari, 2, 0.90, true);
    Niccolò->addItemToList("Spesa", vino);
    Niccolò->addItemToList("Spesa", cartaIG);
    Niccolò->shareList(Chiara, "Spesa");
    EXPECT_NE(Chiara->getList("Spesa"), nullptr);
    EXPECT_EQ(Chiara->getList("Spesa")->getItemCount(),2);
    Item torta("Torta", 5, 2, 2026, "Mulino Bianco", Category::Dolci, 1, 2.30, false);
    Chiara->addItemToList("Spesa", torta);
    EXPECT_EQ(Niccolò->getList("Spesa")->getItemCount(), 3);
    Chiara->showAllList();
    Chiara->removeItemFromList("Spesa","Vino");
    EXPECT_EQ(Chiara->getList("Spesa")->getItemCount(),2);
}

TEST(UserTest, ShowSingleAndAllList){
    User userName("Niccolò");
    userName.createList("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    userName.createList("Vino");
    userName.addItemToList("Spesa", vino);
    userName.showSingleList("Spesa");
    Item cartaIG("Carta Igienica", 5, 2, 2026, "Rotoloni Regina", Category::Non_alimentari, 2, 0.90, true);
    userName.createList("Prodotti Igiene");
    userName.addItemToList("Prodotti Igiene", cartaIG);
    userName.showSingleList("Prodotti Igiene");
    userName.showAllList();
}