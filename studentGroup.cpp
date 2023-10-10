#include "studentGroup.h"

studentGroup::studentGroup() {
    numStudents = 0;
}

studentGroup::studentGroup(const std::string &weekday, double startTime, double duration, const std::string &type) {
    numStudents = 0;
    lessons.push_back(lesson(weekday, startTime, duration, type));
}

void studentGroup::addLesson(const std::string &weekday, double startTime, double duration, const std::string &type) {
    lessons.push_back(lesson(weekday, startTime, duration, type));
}

void studentGroup::addStudent() {
    numStudents++;
}