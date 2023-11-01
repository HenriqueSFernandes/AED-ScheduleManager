#ifndef PROJAED_ADDREQUEST_H
#define PROJAED_ADDREQUEST_H

#include <string>
#include "Request.h"

class AddRequest : public Request {
private:
    std::string upCodeStudent;
    std::string uCCode;
    std::string classCode;


public:
    // Constructor
    AddRequest(const std::string &upCodeStudent, const std::string &uCCode, const std::string &classCode);

    // Getters
    std::string getUpCodeStudent() const;

    std::string getUCCode() const;

    std::string getClassCode() const;

    // Setters
    void setUpCodeStudent(const std::string &upCodeStudent);

    void setUCCode(const std::string &uCCode);

    void setClassCode(const std::string &classCode);
};

#endif //PROJAED_ADDREQUEST_H
