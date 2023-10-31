//
// Created by nowayjose on 28/10/2023.
//


#include "RemoveRequest.h"

// Constructor
RemoveRequest::RemoveRequest(std::string type, const std::string &upCodeStudent, const std::string &uCCode,
                             const std::string &classCode)
        : Request(type), upCodeStudent(upCodeStudent), uCCode(uCCode), classCode(classCode) {
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
