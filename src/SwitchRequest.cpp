// SwitchRequest.cpp

#include "SwitchRequest.h"

// Constructor
SwitchRequest::SwitchRequest( const std::string &upCodeStudent,
                             const std::string &uCCode1, const std::string &uCCode2,
                             const std::string &classCode1, const std::string &classCode2)
        : Request("switch"), upCodeStudent(upCodeStudent), uCCode_1(uCCode1), uCCode_2(uCCode2), classCode_1(classCode1),
          classCode_2(classCode2) {
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

