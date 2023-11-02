#include "RemoveRequest.h"

// Constructor
RemoveRequest::RemoveRequest(const std::string &studentID, const std::string &ucCode, const std::string &classCode)
        : Request("remove"), studentID(studentID), ucCode(ucCode), classCode(classCode) {
}

// Getters
std::string RemoveRequest::getStudentID() const {
    return studentID;
}

std::string RemoveRequest::getUCCode() const {
    return ucCode;
}

std::string RemoveRequest::getClassCode() const {
    return classCode;
}

// Setters
void RemoveRequest::setStudentID(const std::string &studentID) {
    this->studentID = studentID;
}

void RemoveRequest::setUCCode(const std::string &ucCode) {
    this->ucCode = ucCode;
}

void RemoveRequest::setClassCode(const std::string &classCode) {
    this->classCode = classCode;
}
