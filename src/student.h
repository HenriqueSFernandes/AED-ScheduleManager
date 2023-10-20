#ifndef PROJAED_STUDENT_H
#define PROJAED_STUDENT_H

#include <set>
#include <tuple>
#include <string>
#include "studentGroup.h"
using namespace std;
class Student {
public:
    Student(string studentId, string name);
    std::string getStudentID() const;
    void setStudentID(const std::string& studentId);
    void addStudentGroup( studentGroup GroupToAdd);
    void removeGroup(studentGroup GroupToRemove);
    set<studentGroup> getStudentGroups();
    bool operator<(const Student& other) const {
        return studentID < other.studentID;
    }

    std::string getName() const;
    void setName(const std::string& name);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
private:
    std::string studentID;
    std::string name;
    set<studentGroup> StudentGroups;


};


#endif //PROJAED_STUDENT_H
