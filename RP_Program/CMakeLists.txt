cmake_minimum_required(VERSION 3.17)
project(semestralProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(semestralProject main.cpp CubicGraph.cpp CubicGraph.h GraphExceptions.cpp GraphExceptions.h GraphList.cpp GraphList.h PsiFunction.h BacktrackPsi.cpp BacktrackPsi.h ReccursiveFactorPsi.cpp ReccursiveFactorPsi.h GraphLoader.h GraphLoader.cpp)