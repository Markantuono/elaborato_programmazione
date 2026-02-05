//
// Created by HP on 05/02/2026.
//

#ifndef ELABORATO_PROGRAMMAZIONE_ITEM_H
#define ELABORATO_PROGRAMMAZIONE_ITEM_H

#include <iostream>
#include "Informations.h"

enum class Category{
    Frutta,
    Verdura,
    Latticini,
    Carne,
    Pesce,
    Dolci,
    Snack,
    Bevande,
    Alcolici,
    Confezionati,
    Non_alimentari,
};

class Item{
private:
    std::string name;
    Informations info;
    Category category;
    int quantity;
    double price;
    bool purchased;
public:
    Item(const std::string& n, int d, int m, int y, const std::string& b, Category c, int q, double p, bool pc = false): name(n), info(d, m, y, b), category(c), quantity(q), price(p), purchased(pc){}

    void setCategory(Category newCategory);

    void setQuantity(int q);

    void setPrice(int p);

    void setStatus(bool value);

    std::string getName() const;

    Category getCategory() const;

    int getQuantity() const;

    double getPrice() const;

    bool isPurchased() const;

    Informations getInfo() const;
};


#endif //ELABORATO_PROGRAMMAZIONE_ITEM_H
