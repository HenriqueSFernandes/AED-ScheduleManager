#include "student.h"
Student::Student(string studentId, string name, set<studentGroup> group) {
    this->studentID = studentId;
    this->name = name;
    this->StudentGroups=group;
}
void Student::addStudentGroup( studentGroup GroupToAdd){
    this->StudentGroups.insert(GroupToAdd);
}
void Student::removeGroup(studentGroup GroupToRemove){
    cout<<"Chamado o remove group"<<endl;
    for( auto& sg : StudentGroups){
        if(sg.getUcCode()==GroupToRemove.getUcCode() and sg.getClassCode()==GroupToRemove.getClassCode()){
            this->StudentGroups.erase(sg);

        }
    }
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