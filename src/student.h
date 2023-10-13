#ifndef PROJAED_STUDENT_H
#define PROJAED_STUDENT_H


#include <tuple>
#include <string>
#include "course.h"

class student {
public:
private:
    std::string studentID;
    std::string name;
    std::map<course, std::string> courseToClass;

};


#endif //PROJAED_STUDENT_H
