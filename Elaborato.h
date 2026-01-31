//
// Created by HP on 27/01/2026.
//

#ifndef ELABORATO_PROGRAMMAZIONE_ELABORATO_H
#define ELABORATO_PROGRAMMAZIONE_ELABORATO_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

class Observer{
public:
    virtual ~Observer() = default;

    virtual void update() = 0;
    virtual void attach() = 0;
    virtual void detach() = 0;
};

class Subject{
public:
    virtual void attach(Observer* o) = 0;
    virtual void detach(Observer* o) = 0;
    virtual void notify() = 0;

    virtual ~Subject() = default;
};

class Informazioni{
private:
    int day, month, year;
    std::string brand;
    std::vector<std::string> ingredients;
    std::vector<int> days = {30, 28, 30, 31, 30, 31, 30, 31, 30, 31, 30, 31};
public:
    Informazioni(int d, int m, int y, std::string& b, std::vector<std::string>& i, std::vector<int>& ds): day(d), month(m), year(y), brand(b), ingredients(i), days(ds){}

    void setDate(int d, int m, int y){
        if(y >= 2026){
            if(y % 4 == 0) {
                days[1] = 29;  // anno bisestile
            }
            if(m<0 || m>12){
                std::invalid_argument("Mese non valido");
            }
            if(d<0 || d>days[m-1]){
                std::invalid_argument("Giorno non valido");
            }
            day = d;
            month = m;
            year = y;
        }
        else{
            std::invalid_argument("Anno non valido");
        }
    }

    std::string getDate(){
        return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }

    std::string getBrand(){
        return brand;
    }

    std::string getIngredients(){
        for(auto const i : ingredients){
            return i;
        }
    };
};

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
    Informazioni info;
    Category category;
    int quantity;
    double price;
public:
    Item(std::string& n, Informazioni& i, Category& c, int q, double p): name(n), info(i),category(c), quantity(q), price(p){}

    void setCategory(Category newCategory){
        category = newCategory;
    }

    void setQuantity(int q){
        quantity = q;
    }

    void setPrice(int p){
        price = p;
    }

    std::string getName(){
        return name;
    }

    Category getCategory(){
        return category;
    }

    int getQuantity(){
        return quantity;
    }

    double getPrice(){
        return price * quantity;
    }

    Informazioni getInfo(){
        return info;
    }
};

class List: public Subject{
private:
    std::string shoppingList;
    std::vector<Item*> items;
    std::vector<Observer*> observers;
    double totalPrice;
public:
    List(std::string& sl,std::vector<Item*>& i, std::vector<Observer*>& o): shoppingList(sl), items(i), observers(o){}

    void addItem(){
        for (auto const i : items) {
                items.push_back(i);
        }
    }

    auto findItem(std::string& name){
        for (auto it = items.begin(); it != items.end(); ++it){
            if (*it && (*it)->getName() == name) {
                return it;
            }
        }
        return items.end();
    }

    void removeItem(std::string& name){
        auto it = findItem(name);

        if(it != items.end()){
            delete *it;
            items.erase(it);
        }
    }

    void getTotalPrice(){}

    virtual void attach(Observer* o) override;
    virtual void detach(Observer* o) override;
    virtual void notify() override;

    virtual ~List() = default;
};

#endif //ELABORATO_PROGRAMMAZIONE_ELABORATO_H
