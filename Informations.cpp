//
// Created by HP on 05/02/2026.
//

#include <iostream>
#include "Informations.h"

void Informations::setDate(int d, int m, int y){
    if(y >= 2026){
        if(y % 4 == 0) {
            days[1] = 29;  // anno bisestile
        }
        if(m<0 || m>12){
            throw std::invalid_argument("Mese non valido");
        }
        if(d<0 || d>days[m-1]){
            throw std::invalid_argument("Giorno non valido");
        }
        day = d;
        month = m;
        year = y;
    }
    else{
        throw std::invalid_argument("Anno non valido");
    }
};

std::string Informations::getDate() const{
    return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
};

std::string Informations::getBrand() const{
    return brand;
};

std::string Informations::getIngredients() const{
    std::string listaIngredienti;
    for(auto const i : ingredients){
        listaIngredienti += i + ", ";
    }
    return listaIngredienti;
};