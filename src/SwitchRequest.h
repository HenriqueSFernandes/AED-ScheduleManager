// SwitchRequest.h

#ifndef PROJAED_SWITCHREQUEST_H
#define PROJAED_SWITCHREQUEST_H

#include "Request.h"
#include <string>

class SwitchRequest : public Request {
private:
    std::string upCodeStudent_1;
    std::string upCodeStudent_2;
    std::string uCCode_1;
    std::string uCCode_2;
    std::string classCode_1;
    std::string classCode_2;

public:
    // Constructor
    SwitchRequest(int requestId, const std::string& upCodeStudent1, const std::string& upCodeStudent2,
                  const std::string& uCCode1, const std::string& uCCode2,
                  const std::string& classCode1, const std::string& classCode2);

    // Getters
    std::string getUpCodeStudent1() const;
    std::string getUpCodeStudent2() const;
    std::string getUCCode1() const;
    std::string getUCCode2() const;
    std::string getClassCode1() const;
    std::string getClassCode2() const;

    // Setters
    void setUpCodeStudent1(const std::string& upCodeStudent1);
    void setUpCodeStudent2(const std::string& upCodeStudent2);
    void setUCCode1(const std::string& uCCode1);
    void setUCCode2(const std::string& uCCode2);
    void setClassCode1(const std::string& classCode1);
    void setClassCode2(const std::string& classCode2);
};

#endif // PROJAED_SWITCHREQUEST_H
