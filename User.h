//
// Created by HP on 05/02/2026.
//

#ifndef ELABORATO_PROGRAMMAZIONE_USER_H
#define ELABORATO_PROGRAMMAZIONE_USER_H

#include <iostream>
#include <map>
#include <list>
#include <memory>
#include "Observer.h"
#include "List.h"

class User: public Observer{
private:
    std::string userName;
    std::map<std::string, std::shared_ptr<List>> lists;
public:
    User(const std::string& un): userName(un){}

    virtual void update(List* list) override;

    virtual void attach(std::shared_ptr<List> list) override;

    void createList(const std::string& listName);

    void shareList(User* user, const std::string& listName);

    std::string getUserName() const;

    std::shared_ptr<List> getList(const std::string& listName) const;

    void addItemToList(const std::string& listName, const Item& item);

    void updateQuantity(const std::string& listName, const std::string& name,  int newQuantity);

    void updateStatus(const std::string& listName, const std::string& name, bool purchased);

    void removeItemFromList(const std::string& listName, const std::string& itemName);

    std::string showAllList() const;

    virtual void detach(std::shared_ptr<List> list) override;

    virtual ~User() = default;
};

#endif //ELABORATO_PROGRAMMAZIONE_USER_H
