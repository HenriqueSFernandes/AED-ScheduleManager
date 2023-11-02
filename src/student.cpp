#include "student.h"
#include <utility>
#include <algorithm>

Student::Student(string studentId, string name, set<studentGroup> group) {
    this->studentID = std::move(studentId);
    this->name = std::move(name);
    this->StudentGroups = std::move(group);
}

void Student::addStudentGroup(const studentGroup &GroupToAdd) {
    this->StudentGroups.insert(GroupToAdd);
}

void Student::removeGroup(const studentGroup &GroupToRemove) {
    for (auto &sg: StudentGroups) {
        if (sg.getUcCode() == GroupToRemove.getUcCode() and sg.getClassCode() == GroupToRemove.getClassCode()) {
            this->StudentGroups.erase(sg);

        }
    }
}

set<studentGroup> Student::getStudentGroups() const {
    return this->StudentGroups;
}

void removeGroup();

set<studentGroup> getStudentGroups();

// Getter and Setter implementations
string Student::getStudentID() const {
    return studentID;
}

void Student::setStudentID(const string &studentId) {
    studentID = studentId;
}

string Student::getName() const {
    return name;
}

void Student::setName(const string &newName) {
    this->name = newName;
}

// Overload the << operator to output Student objects
ostream &operator<<(ostream &os, const Student &student) {
    os << "Student ID: " << student.getStudentID() << "\n";
    os << "Name: " << student.getName() << "\n";

    return os;
}


bool Student::isInUC(const string &uc) const {
    return any_of(StudentGroups.begin(), StudentGroups.end(),
        [&uc](auto group) {
            return group.getUcCode() == uc;
        }
    );
}

bool Student::isInClass(const string &ucCode, const string &studentGroup) const {
    return any_of(StudentGroups.begin(), StudentGroups.end(), [&ucCode, &studentGroup](auto group) {
        return group.getClassCode() == studentGroup && group.getUcCode() == ucCode;
    });
}