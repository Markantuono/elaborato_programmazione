//
// Created by HP on 05/02/2026.
//

#ifndef ELABORATO_PROGRAMMAZIONE_INFORMATIONS_H
#define ELABORATO_PROGRAMMAZIONE_INFORMATIONS_H

#include <iostream>
#include <vector>

class Informations{
private:
    int day, month, year;
    std::string brand;
    std::vector<std::string> ingredients;
    std::vector<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
public:
    Informations(int d, int m, int y, const std::string& b): day(d), month(m), year(y), brand(b){}

    void setDate(int d, int m, int y);

    std::string getDate() const;

    std::string getBrand() const;

    std::string getIngredients() const;
};

#endif //ELABORATO_PROGRAMMAZIONE_INFORMATIONS_H
