#include "RemoveRequest.h"

// Constructor
RemoveRequest::RemoveRequest(const std::string &upCodeStudent, const std::string &uCCode, const std::string &classCode)
        : Request("remove"), upCodeStudent(upCodeStudent), uCCode(uCCode), classCode(classCode) {
}

// Getters
std::string RemoveRequest::getUpCodeStudent() const {
    return upCodeStudent;
}

std::string RemoveRequest::getUCCode() const {
    return uCCode;
}

std::string RemoveRequest::getClassCode() const {
    return classCode;
}

// Setters
void RemoveRequest::setUpCodeStudent(const std::string &upCodeStudent) {
    this->upCodeStudent = upCodeStudent;
}

void RemoveRequest::setUCCode(const std::string &uCCode) {
    this->uCCode = uCCode;
}

void RemoveRequest::setClassCode(const std::string &classCode) {
    this->classCode = classCode;
}
