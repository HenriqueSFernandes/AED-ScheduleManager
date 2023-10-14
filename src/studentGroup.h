#ifndef PROJAED_STUDENTGROUP_H
#define PROJAED_STUDENTGROUP_H


#include <vector>
#include <string>
#include "lesson.h"
#include <iostream>

class studentGroup {
public:
    studentGroup();

    studentGroup(const std::string &classCode, const std::string &weekday, double startTime, double duration,
                 const std::string &type);

    void addLesson(const std::string &weekday, double startTime, double duration, const std::string &type);

    void addStudent();

    std::vector<lesson> getLessons();

    friend std::ostream &operator<<(std::ostream &os, const studentGroup &studentGroup);

private:
    int numStudents;
    std::string classCode;
    std::vector<lesson> lessons;
};


#endif //PROJAED_STUDENTGROUP_H
