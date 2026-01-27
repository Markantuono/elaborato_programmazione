//
// Created by HP on 27/01/2026.
//

#ifndef ELABORATO_PROGRAMMAZIONE_ELABORATO_H
#define ELABORATO_PROGRAMMAZIONE_ELABORATO_H

#include <iostream>
#include <vector>

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

#endif //ELABORATO_PROGRAMMAZIONE_ELABORATO_H
