//
// Created by HP on 05/02/2026.
//

#include <iostream>
#include <map>
#include <memory>
#include "List.h"
#include "User.h"

void User::update(List* list){
    std::cout << "La lista: " << list->getListName() << " è stata modificatata" << std::endl;
    std::cout << "-STATO ATTUALE-" << std::endl;
    std::cout << "Numero prodotti:" << list->getItemCount() << std::endl;
    std::cout << "Lista completa:" << list->showList() << std::endl;
};

void User::attach(std::shared_ptr<List> list){
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
};

void User::createList(const std::string& listName){
    if(lists.find(listName) != lists.end()){
        throw std::invalid_argument("Lista già esistente");
    }
    else{
        auto it = std::make_shared<List>(listName);
    }
};

void User::shareList(User* user, const std::string& listName){
    auto it = getList(listName);
    user->attach(it);
    std::cout << "Lista: " << it->getListName() << ", condivisa con l'Utente: " << user->getUserName() << std::endl;
};

std::string User::getUserName() const{
    return userName;
};

std::shared_ptr<List> User::getList(const std::string& listName) const{
    auto it = lists.find(listName);

    if(it != lists.end()){
        return it->second;
    }
    else{
        throw std::invalid_argument("Lista non esistente");
    }
};

void User::addItemToList(const std::string& listName, const Item& item){
    if(lists.find(listName) != lists.end()){
        lists[listName]->addItem(item);
    }
    else{
        throw std::invalid_argument("Lista non trovata");
    }
};

void User::updateQuantity(const std::string& listName, const std::string& name,  int newQuantity){
    auto it = getList(listName);
    it->setNewQuantity(name, newQuantity);
};

void User::updateStatus(const std::string& listName, const std::string& name, bool purchased){
    auto it = getList(listName);
    it->setPurchasedStatus(name, purchased);
};

void User::removeItemFromList(const std::string& listName, const std::string& itemName){
    if(lists.find(listName) != lists.end()){
        lists[listName]->removeItem(itemName);
    }
    else{
        throw std::invalid_argument("Lista non trovata");
    }
};

std::string User::showAllList() const{
    std::cout << "Utente: " << userName << " gestisce le liste:" << std::endl;
    for(const auto& l : lists){
        std::cout << "~" << l.first << std::endl;
        l.second->showList();
    }
};
