#ifndef PROJAED_COURSE_H
#define PROJAED_COURSE_H


#include <string>
#include <vector>
#include <map>
#include "studentGroup.h"
#include <iostream>

class course {
public:
    course(std::string classCode, std::string ucCode, std::string weekday, double startHour, double duration,
           std::string type);

    course();

    void addClass(std::string classCode, std::string weekday, double startHour, double duration, std::string type);

    std::map<std::string, studentGroup> getClasses();
    friend std::ostream& operator<<(std::ostream& os, const course& c);

private:
    std::string ucCode;
    std::map<std::string, studentGroup> classes;
};


#endif //PROJAED_COURSE_H
