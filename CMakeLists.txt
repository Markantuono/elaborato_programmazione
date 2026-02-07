cmake_minimum_required(VERSION 3.27)
project(elaborato_programmazione)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

set(SOURCE_FILES
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

add_executable(elaborato_programmazione main.cpp)

add_library(core ${SOURCE_FILES})

target_link_libraries(elaborato_programmazione core)