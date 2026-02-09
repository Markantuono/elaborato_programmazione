//
// Created by HP on 08/02/2026.
//

#include "gtest/gtest.h"
#include "../List.h"

TEST(ListTest, AddItem){
    List listName("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    listName.addItem(vino);
    EXPECT_EQ(listName.getItemCount(), 1);
    EXPECT_THROW(listName.addItem(vino), std::invalid_argument);
}

TEST(ListTest, RemoveItem){
    List listName("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    listName.addItem(vino);
    EXPECT_EQ(listName.getItemCount(), 1);
    listName.removeItem("Vino");
    EXPECT_EQ(listName.getItemCount(), 0);
    EXPECT_THROW(listName.removeItem("Torta"), std::invalid_argument);
}

TEST(ListTest, SetInvalidQuantity){
    List listName("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    listName.addItem(vino);
    EXPECT_THROW(listName.setNewQuantity("Vino" , -3), std::invalid_argument);
}

TEST(ListTest, SetAndGetPurchasedStatus){
    List listName("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    listName.addItem(vino);
    listName.setPurchasedStatus("Vino" , true);
    EXPECT_EQ(listName.getItemStatus("Vino"), true);
    EXPECT_THROW(listName.setPurchasedStatus("Torta" , true), std::invalid_argument);
    EXPECT_THROW(listName.getItemStatus("Torta"), std::invalid_argument);
}

TEST(ListTest, GetListName){
    List listName("Spesa");
    EXPECT_EQ(listName.getListName(), "Spesa");
}

TEST(ListTest, GetTotalPrice){
    List listName("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 2, 21.80, false);
    listName.addItem(vino);
    EXPECT_EQ(listName.getTotalPrice(), 43.60); // p:21.80 x q:2
}

TEST(ListTest, ShowList){
    List listName("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    Item cartaIG("Carta Igienica", 5, 2, 2026, "Rotoloni Regina", Category::Non_alimentari, 2, 0.90, true);
    listName.addItem(vino);
    listName.addItem(cartaIG);
    EXPECT_EQ(listName.showList(), "Carta Igienica x 2\n"
                                   "Vino x 1\n");
}