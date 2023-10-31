cmake_minimum_required(VERSION 3.26)
project(projaed)

set(CMAKE_CXX_STANDARD 17)

#file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable(projaed main.cpp
        src/studentGroup.cpp
        src/studentGroup.h
        src/lesson.cpp
        src/lesson.h
        src/lessontime.cpp
        src/lessontime.h
        src/student.cpp
        src/student.h
        src/ControlUnit.cpp
        src/ControlUnit.h
        src/Menu.cpp
        src/Menu.h
        src/Schedule.cpp
        src/Schedule.h
        src/Request.h
        src/SwitchRequest.cpp
        src/SwitchRequest.h
        src/AddRequest.cpp
        src/AddRequest.h
        src/RemoveRequest.cpp
        src/RemoveRequest.h
)
