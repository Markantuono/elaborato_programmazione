//
// Created by HP on 05/02/2026.
//

#include <iostream>
#include <map>
#include <list>
#include "Observer.h"
#include "Item.h"
#include "List.h"

void List::addItem(const Item& item) {
    auto it = items.find(item.getName());

    if (it == items.end()) {
        items.emplace(item.getName(), item);
    } else {
        int newQuantity = it->second.getQuantity() + 1;
        it->second.setQuantity(newQuantity);
    }
    notify();
};

auto List::findItem(const std::string& name){
    return items.find(name);
};

void List::setNewQuantity(const std::string& name, int newQuantity){
    auto it = findItem(name);

    if (it != items.end()){
        if (it->second.getQuantity() != newQuantity) {
            it->second.setQuantity(newQuantity);
            notify();
        }
    }
    else throw std::invalid_argument("Questo Item non esiste all'interno della lista");
};

void List::setPurchasedStatus(const std::string& name, bool purchased){
    auto it = findItem(name);

    if(it != items.end()){
        if(it->second.isPurchased() != purchased){
            it->second.setStatus(purchased);
            notify();
        }
    }
    else throw std::invalid_argument("Questo Item non esiste all'interno della lista");
};

void List::removeItem(const std::string& name){
    auto it = findItem(name);

    if(it != items.end()){
        items.erase(it);
        notify();
    }
    else throw std::invalid_argument("Questo Item non esiste all'interno della lista");
};

std::string List::getListName() const{
    return listName;
};

bool List::getItemStatus(const std::string& name){
    auto it = findItem(name);

    if(it != items.end()){
        return it->second.isPurchased();
    }
    else{
        throw std::invalid_argument("Questo item non esiste all'interno della lista");
    }
}

int List::getItemCount() const{
    int count = 0;
    for(const auto item : items){
        count++;
    }
    return count;
};

double List::getTotalPrice() const{
    double totalPrice = 0;
    for(const auto& [name, item] : items){
        totalPrice += item.getPrice();
    }
    return totalPrice;
};

std::string List::showList() const{
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
};

void List::attach(Observer* o){
    observers.push_back(o);
};

void List::detach(Observer* o){
    observers.remove(o);
};

void List::notify(){
    for(auto it = std::begin(observers); it != observers.end(); it++){
        (*it)->update(this);
    }
};