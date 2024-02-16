cmake_minimum_required(VERSION 3.10)
project(PMS)
set (CMAKE_CXX_STANDARD 14)

add_executable( PMS
    models/demo.h
    src/Body.cpp
    src/Body.h
    src/Clock.cpp
    src/Clock.h
    src/Force.cpp
    src/Force.h
    src/Joint.cpp
    src/Joint.h
    src/log.h
    src/main.cpp
    src/Matrix.cpp
    src/Matrix.h
    src/PMS.h
    src/Sim.cpp
    src/Sim.h
    src/Solver.cpp
    src/Solver.h
    src/Structs.h
    src/Utils.cpp
    src/Utils.h
    src/Vect2d.cpp
    src/Vect2d.h
    )
