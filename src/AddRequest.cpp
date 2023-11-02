#include "AddRequest.h"

// Constructor
AddRequest::AddRequest(const std::string &studentID, const std::string &ucCode, const std::string &classCode)
        : Request("add"), studentID(studentID), ucCode(ucCode), classCode(classCode) {
}

// Getters
std::string AddRequest::getStudentID() const {
    return studentID;
}

std::string AddRequest::getUCCode() const {
    return ucCode;
}

std::string AddRequest::getClassCode() const {
    return classCode;
}

// Setters
void AddRequest::setStudentID(const std::string &studentID) {
    this->studentID = studentID;
}

void AddRequest::setUCCode(const std::string &ucCode) {
    this->ucCode = ucCode;
}

void AddRequest::setClassCode(const std::string &classCode) {
    this->classCode = classCode;
}
