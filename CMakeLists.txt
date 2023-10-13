cmake_minimum_required(VERSION 3.26)
project(projaed)

set(CMAKE_CXX_STANDARD 17)

#file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

add_executable(projaed main.cpp
        src/studentGroup.cpp
        src/studentGroup.h
        src/course.cpp
        src/course.h
        src/lesson.cpp
        src/lesson.h
        src/time.cpp
        src/time.h
        src/student.cpp
        src/student.h
)
