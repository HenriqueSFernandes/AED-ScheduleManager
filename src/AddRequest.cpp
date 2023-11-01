#include "AddRequest.h"

// Constructor
AddRequest::AddRequest(const std::string &upCodeStudent, const std::string &uCCode, const std::string &classCode)
        : Request("add"), upCodeStudent(upCodeStudent), uCCode(uCCode), classCode(classCode) {
}

// Getters
std::string AddRequest::getUpCodeStudent() const {
    return upCodeStudent;
}

std::string AddRequest::getUCCode() const {
    return uCCode;
}

std::string AddRequest::getClassCode() const {
    return classCode;
}

// Setters
void AddRequest::setUpCodeStudent(const std::string &upCodeStudent) {
    this->upCodeStudent = upCodeStudent;
}

void AddRequest::setUCCode(const std::string &uCCode) {
    this->uCCode = uCCode;
}

void AddRequest::setClassCode(const std::string &classCode) {
    this->classCode = classCode;
}
