//
// Created by HP on 08/02/2026.
//

#include "gtest/gtest.h"
#include "../List.h"

TEST(ListTest, AddItem){
    List list("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    list.addItem(vino);
    EXPECT_EQ(list.getItemCount(), 1);
    list.addItem(vino);
    EXPECT_EQ(list.getItemCount(), 2);
}

TEST(ListTest, RemoveItem){
    List list("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    list.addItem(vino);
    EXPECT_EQ(list.getItemCount(), 1);
    list.removeItem("Vino");
    EXPECT_EQ(list.getItemCount(), 0);
    EXPECT_THROW(list.removeItem("Torta"), std::invalid_argument);
}

TEST(ListTest, SetInvalidQuantity){
    List list("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    list.addItem(vino);
    EXPECT_THROW(list.setNewQuantity("Vino" , -3), std::invalid_argument);
}

TEST(ListTest, SetAndGetPurchasedStatus){
    List list("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    list.addItem(vino);
    list.setPurchasedStatus("Vino" , true);
    EXPECT_EQ(list.getItemStatus("Vino"), true);
    EXPECT_THROW(list.setPurchasedStatus("Torta" , true), std::invalid_argument);
    EXPECT_THROW(list.getItemStatus("Torta"), std::invalid_argument);
}

TEST(ListTest, GetListName){
    List list("Spesa");
    EXPECT_EQ(list.getListName(), "Spesa");
}

TEST(ListTest, GetTotalPrice){
    List list("Spesa");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 2, 21.80, false);
    list.addItem(vino);
    EXPECT_EQ(list.getTotalPrice(), 43.60); // p:21.80 x q:2
}