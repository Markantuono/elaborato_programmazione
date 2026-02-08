//
// Created by HP on 05/02/2026.
//

#ifndef ELABORATO_PROGRAMMAZIONE_LIST_H
#define ELABORATO_PROGRAMMAZIONE_LIST_H

#include <iostream>
#include <map>
#include <list>
#include "Observer.h"
#include "Subject.h"
#include "Item.h"


class List: public Subject{
private:
    std::string listName;
    std::map<std::string, Item> items;
    std::list<Observer*> observers;
public:
    List(const std::string& ln): listName(ln){}

    void addItem(const Item& item);

    auto findItem(const std::string& name);

    void setNewQuantity(const std::string& name, int newQuantity);

    void setPurchasedStatus(const std::string& name, bool purchased);

    void removeItem(const std::string& name);

    std::string getListName() const;

    bool getItemStatus(const std::string& name);

    int getItemCount() const;

    double getTotalPrice() const;

    std::string showList() const;

    virtual void attach(Observer* o) override;

    virtual void detach(Observer* o) override;

    virtual void notify() override;

    virtual ~List() = default;
};

#endif //ELABORATO_PROGRAMMAZIONE_LIST_H
