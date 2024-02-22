cmake_minimum_required (VERSION 3.10)
project (PMS)

add_compile_definitions (_DEBUG)
set (BUILD_TYPE Debug)
set (CMAKE_CXX_flags "${CMAKE_CXX_FLAGS} -std=c++14")
set (CMAKE_BULD_TYPE ${BUILD_TYPE})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/linux/${BUILD_TYPE})

file (GLOB src_files 
"${PROJECT_SOURCE_DIR}/src/sim/*.cpp"
"${PROJECT_SOURCE_DIR}/src/main.cpp"
"${PROJECT_SOURCE_DIR}/src/utils/*.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/src/utils")

add_executable (PMS ${src_files})
   