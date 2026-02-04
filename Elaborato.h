//
// Created by HP on 27/01/2026.
//

#ifndef ELABORATO_PROGRAMMAZIONE_ELABORATO_H
#define ELABORATO_PROGRAMMAZIONE_ELABORATO_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stdexcept>
#include <algorithm>
#include <memory>

class List; //Forward declaration

class Observer{
public:
    virtual ~Observer() = default;

    virtual void update(List* list) = 0;
    virtual void attach(std::shared_ptr<List> list) = 0;
    virtual void detach(std::shared_ptr<List> list) = 0;
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
    Informazioni(int d, int m, int y, const std::string& b): day(d), month(m), year(y), brand(b){}

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

    std::string getDate() const{
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
    Item(const std::string& n, Informazioni& i, Category& c, int q, double p, bool pc = false): name(n), info(i), category(c), quantity(q), price(p), purchased(pc){}

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

    std::string getName() const{
        return name;
    }

    Category getCategory() const{
        return category;
    }

    int getQuantity() const{
        return quantity;
    }

    double getPrice() const{
        return price * quantity;
    }

    bool isPurchased() const{
        return purchased;
    }

    Informazioni getInfo() const{
        return info;
    }
};

class List: public Subject{
private:
    std::string listName;
    std::map<std::string, Item> items;
    std::list<Observer*> observers;
public:
    List(const std::string& ln): listName(ln){}

    void addItem(const Item& item) {
        auto it = items.find(item.getName());

        if (it == items.end()) {
            items.emplace(item.getName(), item);
        } else {
            int newQuantity = it->second.getQuantity() + 1;
            it->second.setQuantity(newQuantity);
        }
        notify();
    }

    auto findItem(const std::string& name){
        return items.find(name);
    }

    void setNewQuantity(const std::string& name, int newQuantity){
        auto it = findItem(name);

        if (it != items.end()){
            if (it->second.getQuantity() != newQuantity) {
                it->second.setQuantity(newQuantity);
                notify();
            }
        }
    }

    void setPurchasedStatus(const std::string& name, bool purchased){
        auto it = findItem(name);

        if(it != items.end()){
            if(it->second.isPurchased() != purchased){
                it->second.setStatus(purchased);
                notify();
            }
        }
    }

    void removeItem(const std::string& name){
        auto it = findItem(name);

        if(it != items.end()){
            items.erase(it);
            notify();
        }
    }

    std::string getListName() const{
        return listName;
    }

    int getItemCount() const{
        int count = 0;
        for(const auto item : items){
            count++;
        }
        return count;
    }

    double getTotalPrice() const{
        double totalPrice = 0;
        for(const auto& [name, item] : items){
            totalPrice += item.getPrice();
        }
        return totalPrice;
    }

    std::string showList() const{
        double totalPurchased = 0;
        double totalNotPurchased = 0;

        std::cout << "-PRODOTTI ACQUISTATI-" << std::endl;
        for(const auto& [name, item] : items){
            if(item.isPurchased()){
                totalPurchased += item.getPrice();
                std::cout << "-" << item.getName() << "x" << item.getQuantity() << std::endl;
            }
        }
        std::cout << "Totale speso:" << totalPurchased << "€" << std::endl;

        std::cout << "-PRODOTTI DA ACQUISTARE-" << std::endl;
        for(const auto& [name, item] : items){
            if (!item.isPurchased()){
                totalNotPurchased += item.getPrice();
                std::cout << "-" << item.getName() << "x" << item.getQuantity() << std::endl;
            }
        }
        std::cout << "Totale da spendere:" << totalNotPurchased << "€" << std::endl;

        std::cout << "Totale complessivo:" << totalPurchased + totalNotPurchased << "€" << std::endl;
    }

    virtual void attach(Observer* o) override{
        observers.push_back(o);
    }

    virtual void detach(Observer* o) override{
        observers.remove(o);
    }

    virtual void notify() override{
        for(auto it = std::begin(observers); it != observers.end(); it++){
            (*it)->update(this);
        }
    }

    virtual ~List() = default;
};

class User: public Observer{
private:
    std::string userName;
    std::map<std::string, std::shared_ptr<List>> lists;
public:
    User(const std::string& un): userName(un){}

    virtual void update(List* list) override{
        std::cout << "La lista: " << list->getListName() << " è stata modificatata" << std::endl;
        std::cout << "-STATO ATTUALE-" << std::endl;
        std::cout << "Numero prodotti:" << list->getItemCount() << std::endl;
        std::cout << "Lista completa:" << list->showList() << std::endl;
    }

    virtual void attach(std::shared_ptr<List> list) override {
        auto it = list->getListName();

        if(list == nullptr){
            throw std::invalid_argument("Lista nulla");
        }
        else if (lists.find(it) == lists.end()){
            lists[it] = list;
            list->attach(this);
        }
        else{
            throw std::invalid_argument("Lista già esistente");
        }
    }

    void createList(const std::string& listName){
        if(lists.find(listName) != lists.end()){
            throw std::invalid_argument("Lista già esistente");
        }
        else{
            auto it = std::make_shared<List>(listName);
        }
    }

    void shareList(User* user, const std::string& listName){
        auto it = getList(listName);
        user->attach(it);
        std::cout << "Lista: " << it->getListName() << ", condivisa con l'Utente: " << user->getUserName() << std::endl;
    }

    std::string getUserName() const{
        return userName;
    }

    std::shared_ptr<List> getList(const std::string& listName) const{
        auto it = lists.find(listName);

        if(it != lists.end()){
            return it->second;
        }
        else{
            throw std::invalid_argument("Lista non esistente");
        }
    }

    void addItemToList(const std::string& listName, const Item& item){
        if(lists.find(listName) != lists.end()){
            lists[listName]->addItem(item);
        }
        else{
            throw std::invalid_argument("Lista non trovata");
        }
    }

    void updateQuantity(const std::string& listName, const std::string& name,  int newQuantity){
        auto it = getList(listName);
        it->setNewQuantity(name, newQuantity);
    }

    void updateStatus(const std::string& listName, const std::string& name, bool purchased){
        auto it = getList(listName);
        it->setPurchasedStatus(name, purchased);
    }

    void removeItemFromList(const std::string& listName, const std::string& itemName){
        if(lists.find(listName) != lists.end()){
            lists[listName]->removeItem(itemName);
        }
        else{
            throw std::invalid_argument("Lista non trovata");
        }
    }

    std::string showAllList() const{
        std::cout << "Utente: " << userName << " gestisce le liste:" << std::endl;
        for(const auto& l : lists){
            std::cout << "~" << l.first << std::endl;
            l.second->showList();
        }
    }

    virtual void detach(std::shared_ptr<List> list) override;

    virtual ~User() = default;
};

#endif //ELABORATO_PROGRAMMAZIONE_ELABORATO_H
