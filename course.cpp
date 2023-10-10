#include "course.h"

course::course(std::string classCode, std::string ucCode, std::string weekday, double startHour, double duration,
               std::string type) {
    this->ucCode = ucCode;
    this->classes.insert({classCode, studentGroup(weekday, startHour, duration, type)});
}

void course::addClass(std::string classCode, std::string weekday, double startHour, double duration,
                      std::string type) {
    if (classes.find(classCode) != classes.end()){
        classes[classCode].addLesson(weekday, startHour, duration, type);
    }
    else{
        classes.insert({classCode, studentGroup(weekday, startHour, duration, type)});
    }
}