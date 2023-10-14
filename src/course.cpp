#include "course.h"

course::course(std::string classCode, std::string ucCode, std::string weekday, double startHour, double duration,
               std::string type) {
    this->ucCode = ucCode;
    this->classes.insert({classCode, studentGroup(classCode, weekday, startHour, duration, type)});
}

course::course() {
    this->ucCode = "";

}

void course::addClass(std::string classCode, std::string weekday, double startHour, double duration,
                      std::string type) {
    if (classes.find(classCode) != classes.end()) {
        classes[classCode].addLesson(weekday, startHour, duration, type);
    } else {
        classes.insert({classCode, studentGroup(classCode, weekday, startHour, duration, type)});
    }
}

std::map<std::string, studentGroup> course::getClasses() {
    return this->classes;
}

std::ostream &operator<<(std::ostream &os, const course &c) {
    os << "UcCode: " << c.ucCode << "\nClasses:\n";
    for(const auto& i : c.classes){
        os << std::endl << i.second;
    }
    return os;
}
