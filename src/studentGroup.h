#ifndef PROJAED_STUDENTGROUP_H
#define PROJAED_STUDENTGROUP_H


#include <vector>
#include <string>
#include "lesson.h"

class studentGroup {
public:
    studentGroup();
    studentGroup(const std::string &weekday, double startTime, double duration, const std::string &type);
    void addLesson(const std::string &weekday, double startTime, double duration, const std::string &type);
    void addStudent();
private:
    int numStudents;
    std::string classId;
    std::vector<lesson> lessons;
};


#endif //PROJAED_STUDENTGROUP_H
