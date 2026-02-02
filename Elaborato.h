//
// Created by HP on 27/01/2026.
//

#ifndef ELABORATO_PROGRAMMAZIONE_ELABORATO_H
#define ELABORATO_PROGRAMMAZIONE_ELABORATO_H

#include <iostream>
#include <vector>
#include <list>
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
    std::vector<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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
        std::string result;
        for(auto const i : ingredients){
            result += i + ", ";
        }
        return result;
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
    bool purchased;
public:
    Item(std::string& n, Informazioni& i, Category& c, int q, double p, bool pc = false): name(n), info(i), category(c), quantity(q), price(p), purchased(pc){}

    void setCategory(Category newCategory){
        category = newCategory;
    }

    void setQuantity(int q){
        if (q <= 0) {
            throw std::invalid_argument("Quantità non valida");
        }
        quantity = q;
    }

    void setPrice(int p){
        if(p <= 0) {
            throw std::invalid_argument("Prezzo non valido");
        }
        price = p;
    }

    void setStatus(bool value){
        purchased = value;
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

    bool isPurchased(){
        return purchased;
    }

    Informazioni getInfo(){
        return info;
    }
};

class List: public Subject{
private:
    std::string shoppingList;
    std::vector<Item*> items;
    std::list<Observer*> observers;
public:
    List(std::string& sl,std::vector<Item*>& i, std::list<Observer*>& o): shoppingList(sl), items(i), observers(o){}

    void addItem(){
        for (auto const i : items) {
                items.push_back(i);
                notify();
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

    void setNewQuantity(std::string& name, int newQuantity){
        auto it = findItem(name);

        if (it != items.end()){
            if ((*it)->getQuantity() != newQuantity) {
                (*it)->setQuantity(newQuantity);
                notify();
            }
        }
    }

    void setPurchasedStatus(std::string& name, bool purchased){
        auto it = findItem(name);

        if(it != items.end()){
            if((*it)->isPurchased() != purchased){
                (*it)->setStatus(purchased);
                notify();
            }
        }
    }

    void removeItem(std::string& name){
        auto it = findItem(name);

        if(it != items.end()){
            delete *it;
            items.erase(it);
            notify();
        }
    }

    int getItemCount() const {
        return items.size();
    }

    double getTotalPrice(){
        double totalPrice = 0;
        for (auto it = items.begin(); it != items.end(); ++it){
            totalPrice += (*it)->getPrice();
        }
        return totalPrice;
    }

    virtual void attach(Observer* o) override{
        observers.push_back(o);
    }

    virtual void detach(Observer* o) override{
        observers.remove(o);
    }

    virtual void notify() override{
        for(auto it = std::begin(observers); it != observers.end(); it++){
            (*it)->update();
        }
    }

    virtual ~List() = default;
};

class User: public Observer{
private:
    std::string name;
    std::vector<List*> lists;
public:
    User(List* l);

    virtual void update(List* l){
        std::cout << "Numero prodotti:" << l->getItemCount() << std::endl;
    }

    virtual void attach(List* l){
        lists.push_back(l);
        l->attach(this);
    }

    virtual void detach();

    virtual ~User() = default;
};

#endif //ELABORATO_PROGRAMMAZIONE_ELABORATO_H
