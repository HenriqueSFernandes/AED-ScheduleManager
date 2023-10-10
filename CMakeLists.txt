cmake_minimum_required(VERSION 3.26)
project(projaed)

set(CMAKE_CXX_STANDARD 17)

add_executable(projaed main.cpp
        studentGroup.cpp
        studentGroup.h
        course.cpp
        course.h
        lesson.cpp
        lesson.h
        time.cpp
        time.h
        student.cpp
        student.h
)
