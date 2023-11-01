#ifndef PROJAED_SWITCHREQUEST_H
#define PROJAED_SWITCHREQUEST_H

#include "Request.h"
#include <string>

class SwitchRequest : public Request {
private:
    std::string upCodeStudent;
    std::string uCCode_1;
    std::string uCCode_2;
    std::string classCode_1;
    std::string classCode_2;

public:
    // Constructor
    SwitchRequest(const std::string &upCodeStudent, const std::string &uCCode1, const std::string &uCCode2,
                  const std::string &classCode1, const std::string &classCode2);

    // Getters
    std::string getUpCodeStudent() const;

    std::string getUCCode1() const;

    std::string getUCCode2() const;

    std::string getClassCode1() const;

    std::string getClassCode2() const;


};

#endif // PROJAED_SWITCHREQUEST_H