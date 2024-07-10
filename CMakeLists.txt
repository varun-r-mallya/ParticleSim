cmake_minimum_required(VERSION 3.7)
project(ParticleSim)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

if (MSVC)
    set_target_properties(
            ${PROJECT_NAME} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/")
endif ()


add_executable(ParticleSim src/main.cpp src/ball.hpp src/ball.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")