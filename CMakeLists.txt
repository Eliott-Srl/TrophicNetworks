cmake_minimum_required(VERSION 3.28)
project(TrophicNetworks C)

set(CMAKE_C_STANDARD 11)

add_executable(TrophicNetworks main.c
        Graphe/Graphe.h
        Graphe/Graphe.c
        Processing/Processing.c
        Processing/Processing.h
        Simulation/Simulation.c
        Simulation/Simulation.h
        Utils/Utils.c
        Utils/Utils.h)
