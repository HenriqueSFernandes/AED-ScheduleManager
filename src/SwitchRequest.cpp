// SwitchRequest.cpp

#include "SwitchRequest.h"

// Constructor
SwitchRequest::SwitchRequest( std::string type, const std::string& upCodeStudent,
                             const std::string& uCCode1, const std::string& uCCode2,
                             const std::string& classCode1, const std::string& classCode2)
        : Request(type), upCodeStudent(upCodeStudent),uCCode_1(uCCode1), uCCode_2(uCCode2), classCode_1(classCode1), classCode_2(classCode2) {
}

// Getters
std::string SwitchRequest::getUpCodeStudent() const {
    return upCodeStudent;
}



std::string SwitchRequest::getUCCode1() const {
    return uCCode_1;
}

std::string SwitchRequest::getUCCode2() const {
    return uCCode_2;
}

std::string SwitchRequest::getClassCode1() const {
    return classCode_1;
}

std::string SwitchRequest::getClassCode2() const {
    return classCode_2;
}

// Setters
void SwitchRequest::setUpCodeStudent1(const std::string& upCodeStudent1) {
    upCodeStudent_1 = upCodeStudent1;
}

void SwitchRequest::setUpCodeStudent2(const std::string& upCodeStudent2) {
    upCodeStudent_2 = upCodeStudent2;
}

void SwitchRequest::setUCCode1(const std::string& uCCode1) {
    uCCode_1 = uCCode1;
}

void SwitchRequest::setUCCode2(const std::string& uCCode2) {
    uCCode_2 = uCCode2;
}

void SwitchRequest::setClassCode1(const std::string& classCode1) {
    classCode_1 = classCode1;
}

void SwitchRequest::setClassCode2(const std::string& classCode2) {
    classCode_2 = classCode2;
}
