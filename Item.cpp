//
// Created by HP on 05/02/2026.
//

#include <iostream>
#include "Informations.h"
#include "Item.h"

void Item::setCategory(Category newCategory){
    category = newCategory;
};

void Item::setQuantity(int q){
    if (q <= 0) {
        throw std::invalid_argument("Quantità non valida");
    }
    quantity = q;
};

void Item::setPrice(int p){
    if(p <= 0) {
        throw std::invalid_argument("Prezzo non valido");
    }
    price = p;
};

void Item::setStatus(bool value){
    purchased = value;
};

std::string Item::getName() const{
    return name;
};

Category Item::getCategory() const{
    return category;
};

int Item::getQuantity() const{
    return quantity;
};

double Item::getPrice() const{
    return price * quantity;
};

bool Item::isPurchased() const{
    return purchased;
};

Informations Item::getInfo() const{
    return info;
};