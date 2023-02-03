cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

project(MyProject VERSION 1.0)
add_executable(MyProject main.cpp)
target_link_libraries(MyProject sfml-graphics)

