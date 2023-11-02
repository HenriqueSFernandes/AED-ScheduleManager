/// @file SwitchRequest.h
#ifndef PROJAED_SWITCHREQUEST_H
#define PROJAED_SWITCHREQUEST_H

#include "Request.h"
#include <string>

/**
 * @brief Request of type switch.
 */
class SwitchRequest : public Request {
private:
    std::string studentID;
    std::string ucCode1;
    std::string ucCode2;
    std::string classCode1;
    std::string classCode2;

public:
    /**
     * @brief Parameterized constructor.
     * @param studentID String representing the student ID.
     * @param ucCode1 String representing the current course code.
     * @param ucCode2 String representing the new course code.
     * @param classCode1 String representing the current class code.
     * @param classCode2 String representing the new class code.
     */
    SwitchRequest(const std::string &studentID, const std::string &ucCode1, const std::string &ucCode2,
                  const std::string &classCode1, const std::string &classCode2);

    /**
     * @brief Gets the student ID.
     * @return A string representing the student ID.
     */
    std::string getStudentID() const;

    /**
     * @brief Gets the current course code.
     * @return A string representing the current course code.
     */
    std::string getUCCode1() const;

    /**
     * @brief Gets the new course code.
     * @return A string representing the new course code.
     */
    std::string getUCCode2() const;

    /**
     * @brief Gets the current class code.
     * @return A string representing the current class code.
     */
    std::string getClassCode1() const;

    /**
     * @brief Gets the new class code.
     * @return A string representing the new class code.
     */
    std::string getClassCode2() const;

};

#endif // PROJAED_SWITCHREQUEST_H