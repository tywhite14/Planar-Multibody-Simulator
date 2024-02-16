cmake_minimum_required(VERSION 3.10)
project(PMS)

set(BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BULD_TYPE ${BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/linux/${BUILD_TYPE})

add_executable( PMS
    src/Body.cpp
    src/Clock.cpp
    src/Force.cpp
    src/Joint.cpp
    src/main.cpp
    src/Matrix.cpp
    src/Sim.cpp
    src/Solver.cpp
    src/Utils.cpp
    src/Vect2d.cpp
    )
