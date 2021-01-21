cmake_minimum_required(VERSION 3.17)
project(AAL_pomidorki)

set(CMAKE_CXX_STANDARD 14)

include_directories(Projekt/include)

add_executable(AAL_pomidorki
        Projekt/include/algorithm.hpp
        Projekt/include/base.hpp
        Projekt/include/field.hpp
        Projekt/include/generator.hpp
        Projekt/include/naive.hpp
        Projekt/src/algorithm.cpp
        Projekt/src/generator.cpp
        Projekt/src/main.cpp
        Projekt/src/naive.cpp)

project(AAL_generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(Projekt/include)

add_executable(AAL_generator
        Projekt/include/field.hpp
        Projekt/include/generator.hpp
        Projekt/src/generator.cpp
        Projekt/src/externalGenerator.cpp

)


