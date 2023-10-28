// SwitchRequest.h

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
    SwitchRequest( std::string type,const std::string& upCodeStudent,
                  const std::string& uCCode1, const std::string& uCCode2,
                  const std::string& classCode1, const std::string& classCode2);

    // Getters
    std::string getUpCodeStudent() const;
    std::string getUCCode1() const;
    std::string getUCCode2() const;
    std::string getClassCode1() const;
    std::string getClassCode2() const;

    // Setters
    void setUpCodeStudent(const std::string& upCodeStudent);
    void setUCCode1(const std::string& uCCode1);
    void setUCCode2(const std::string& uCCode2);
    void setClassCode1(const std::string& classCode1);
    void setClassCode2(const std::string& classCode2);
};

#endif // PROJAED_SWITCHREQUEST_H
