#include "studentGroup.h"

studentGroup::studentGroup() {
    numStudents = 0;
    classCode = "";
}

studentGroup::studentGroup(const std::string &classCode, const std::string &weekday, double startTime, double duration, const std::string &type) {
    numStudents = 0;
    this->classCode = classCode;
    lessons.push_back(lesson(weekday, startTime, duration, type));
}

void studentGroup::addLesson(const std::string &weekday, double startTime, double duration, const std::string &type) {
    lessons.push_back(lesson(weekday, startTime, duration, type));
}

void studentGroup::addStudent() {
    numStudents++;
}

std::ostream &operator<<(std::ostream &os, const studentGroup &studentGroup) {
    os << "Class Code: " << studentGroup.classCode << std::endl << "Students: " << studentGroup.numStudents << "\nLessons:\n";
    for (const auto& i : studentGroup.lessons){
        os << '\t' << i << std::endl;
    }
}
