cmake_minimum_required(VERSION 3.26)
project(projaed)

set(CMAKE_CXX_STANDARD 17)

add_executable(projaed main.cpp
        turma.cpp
        turma.h
        cadeira.cpp
        cadeira.h
        aula.cpp
        aula.h
        tempo.cpp
        tempo.h
        estudante.cpp
        estudante.h
)
