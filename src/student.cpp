#include "student.h"
Student::Student(string studentId, string name) {
    this->studentID = studentId;
    this->name = name;

}
void Student::addStudentGroup( studentGroup GroupToAdd){
    this->StudentGroups.insert(GroupToAdd);
}
void Student::removeGroup(studentGroup GroupToRemove){
    this->StudentGroups.erase(GroupToRemove);
}
set<studentGroup> Student::getStudentGroups(){
    return this->StudentGroups;
}
void removeGroup();
set<studentGroup> getStudentGroups();
// Getter and Setter implementations
std::string Student::getStudentID() const {
    return studentID;
}

void Student::setStudentID(const std::string& studentId) {
    studentID = studentId;
}

std::string Student::getName() const {
    return name;
}

void Student::setName(const std::string& name) {
    this->name = name;
}

// Overload the << operator to output Student objects
std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "Student ID: " << student.getStudentID() << "\n";
    os << "Name: " << student.getName() << "\n";

    return os;
}