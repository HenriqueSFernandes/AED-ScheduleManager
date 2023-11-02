#include "SwitchRequest.h"

// Constructor
SwitchRequest::SwitchRequest(const std::string &studentID, const std::string &ucCode1, const std::string &ucCode2,
                             const std::string &classCode1, const std::string &classCode2) : Request("switch"),
                                                                                             studentID(
                                                                                                     studentID),
                                                                                             ucCode1(ucCode1),
                                                                                             ucCode2(ucCode2),
                                                                                             classCode1(classCode1),
                                                                                             classCode2(classCode2) {
}

// Getters
std::string SwitchRequest::getStudentID() const {
    return studentID;
}


std::string SwitchRequest::getUCCode1() const {
    return ucCode1;
}

std::string SwitchRequest::getUCCode2() const {
    return ucCode2;
}

std::string SwitchRequest::getClassCode1() const {
    return classCode1;
}

std::string SwitchRequest::getClassCode2() const {
    return classCode2;
}

