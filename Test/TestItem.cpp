//
// Created by HP on 07/02/2026.
//
#include "gtest/gtest.h"
#include "../Item.h"

TEST(ItemTest, Creation){
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    EXPECT_EQ(vino.getName(), "Vino");
    EXPECT_EQ(vino.getCategory(), Category::Alcolici);
    EXPECT_EQ(vino.getQuantity(), 1);
    EXPECT_EQ(vino.getPrice(), 21.80);
    EXPECT_EQ(vino.isPurchased(), false);
    EXPECT_EQ(vino.getInfo(), "5/2/2026 , Chianti");
}

TEST(ItemTest, InvalidYear){
    Informations info(5, 2, 2026, "Chianti");
    EXPECT_THROW(info.setDate(5, 2, 2020), std::invalid_argument);
}

TEST(ItemTest, InvalidMonth){
    Informations info(5, 2, 2026, "Chianti");
    EXPECT_THROW(info.setDate(5, 14, 2026), std::invalid_argument);
}

TEST(ItemTest, InvalidDay){
    Informations info(50, 2, 2026, "Chianti");
    EXPECT_THROW(info.setDate(50, 2, 2026), std::invalid_argument);
}

TEST(ItemTest, SetQuantity){
    Item mela("Mela", 5, 2, 2026, "Melinda", Category::Frutta, 2, 0.90, false);
    EXPECT_EQ(mela.getQuantity(), 2);
    mela.setQuantity(3);
    EXPECT_EQ(mela.getQuantity(), 3);
}

TEST(ItemTest, InvalidSetQuantity){
    Item mela("Mela", 5, 2, 2026, "Melinda", Category::Frutta, 2, 0.90, false);
    EXPECT_EQ(mela.getQuantity(), 2);
    EXPECT_THROW(mela.setQuantity(-5), std::invalid_argument);
}

TEST(ItemTest, SetPrice){
    Item carne("Carne", 5, 2, 2026, "Amadori", Category::Carne, 3, 1.50, false);
    EXPECT_EQ(carne.getPrice(), 4.50);
    carne.setQuantity(5);
    EXPECT_EQ(carne.getPrice(), 7.50);
}

TEST(ItemTest, InvalidSetPrice){
    Item carne("Carne", 5, 2, 2026, "Amadori", Category::Carne, 3, 1.50, false);
    EXPECT_EQ(carne.getPrice(), 4.50);
    EXPECT_THROW(carne.setPrice(0), std::invalid_argument);
}

TEST(ItemTest, IsPurchased){
    Item torta("Torta", 5, 2, 2026, "Mulino Bianco", Category::Dolci, 1, 2.30, false);
    EXPECT_EQ(torta.isPurchased(), false);
    torta.setStatus(true);
    EXPECT_EQ(torta.isPurchased(), true);
}

TEST(ItemTest, GetInfo){
    Informations info(5, 2, 2026, "Chianti");
    Item vino("Vino", 5, 2, 2026, "Chianti", Category::Alcolici, 1, 21.80, false);
    EXPECT_EQ(vino.getInfo(), "5/2/2026 , Chianti");
}

TEST(ItemTest, MultipleItems){
    Item torta("Torta", 5, 2, 2026, "Mulino Bianco", Category::Dolci, 1, 2.30, false);
    Item carne("Carne", 5, 2, 2026, "Amadori", Category::Carne, 3, 1.50, false);
    EXPECT_EQ(torta.getName(), "Torta");
    EXPECT_EQ(torta.getCategory(), Category::Dolci);
    EXPECT_EQ(carne.getName(), "Carne");
    EXPECT_EQ(carne.getCategory(), Category::Carne);
}