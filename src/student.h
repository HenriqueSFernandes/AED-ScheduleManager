#ifndef PROJAED_STUDENT_H
#define PROJAED_STUDENT_H

#include <set>
#include <tuple>
#include <string>
#include "studentGroup.h"
using namespace std;
class Student {
public:
    Student(){};
    Student(string studentId, string name, set<studentGroup> group);
    std::string getStudentID() const;
    void setStudentID(const std::string& studentId);

    void addStudentGroup( studentGroup GroupToAdd);
    void removeGroup(studentGroup GroupToRemove);
    set<studentGroup> getStudentGroups();
    bool operator<(const Student& other) const {
        return studentID < other.studentID;
    }
    bool operator==(const Student& other) const {
        // Implement your equality comparison logic here
        // This function should not modify the state of the object.
        // It should only compare the object's attributes.
        return (this->studentID== other.studentID) && (this->name == other.name);
    }

    std::string getName() const;
    void setName(const std::string& name);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    bool isinuc(string uc);
    bool isinclass(string uc, string studgroup);
private:
    std::string studentID;
    std::string name;
    std::set<studentGroup> StudentGroups;



};


#endif //PROJAED_STUDENT_H
