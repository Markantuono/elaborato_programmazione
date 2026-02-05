//
// Created by HP on 05/02/2026.
//

#ifndef ELABORATO_PROGRAMMAZIONE_OBSERVER_H
#define ELABORATO_PROGRAMMAZIONE_OBSERVER_H

#include <iostream>
#include <memory>

class List; //Forward Declaration

class Observer{
public:
    virtual ~Observer() = default;

    virtual void update(List* list) = 0;
    virtual void attach(std::shared_ptr<List> list) = 0;
    virtual void detach(std::shared_ptr<List> list) = 0;
};

#endif //ELABORATO_PROGRAMMAZIONE_OBSERVER_H
