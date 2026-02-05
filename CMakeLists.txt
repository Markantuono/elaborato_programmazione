cmake_minimum_required(VERSION 3.27)
project(elaborato_programmazione)

set(CMAKE_CXX_STANDARD 17)

add_executable(elaborato_programmazione main.cpp
        Observer.h
        Subject.h
        Informations.h
        Item.h
        List.h
        User.h
        Informations.cpp
        Item.cpp
        List.cpp
        User.cpp
)
