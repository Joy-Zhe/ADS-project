cmake_minimum_required(VERSION 3.24)
project(Project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project1 main.cpp SPlayTree.h AVLTree.h AVLTree.cpp BBalpha.h BBalpha.cpp SPlayTree.cpp BST.cpp timeSpan.cpp)
