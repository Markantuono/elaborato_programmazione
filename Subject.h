//
// Created by HP on 05/02/2026.
//

#ifndef ELABORATO_PROGRAMMAZIONE_SUBJECT_H
#define ELABORATO_PROGRAMMAZIONE_SUBJECT_H

#include <iostream>
#include "Observer.h"

class Subject{
public:
    virtual void attach(Observer* o) = 0;
    virtual void detach(Observer* o) = 0;
    virtual void notify() = 0;

    virtual ~Subject() = default;
};

#endif //ELABORATO_PROGRAMMAZIONE_SUBJECT_H
