/// @file AddRequest.h
#ifndef PROJAED_ADDREQUEST_H
#define PROJAED_ADDREQUEST_H

#include <string>
#include "Request.h"

/**
 * @brief Request of type add.
 */
class AddRequest : public Request {
private:
    std::string studentID;
    std::string ucCode;
    std::string classCode;


public:
    /**
     * @brief Parameterized constructor.
     * @param studentID String representing the student ID.
     * @param ucCode String representing the course code.
     * @param classCode String representing the class code.
     */
    AddRequest(const std::string &studentID, const std::string &ucCode, const std::string &classCode);

    /**
     * @brief Gets the student ID.
     * @return A string representing the studentID.
     */
    std::string getStudentID() const;

    /**
     * @brief Gets the course code.
     * @return A string representing the course code.
     */
    std::string getUCCode() const;

    /**
     * @brief Gets the class code.
     * @return A string representing the class code.
     */
    std::string getClassCode() const;

    /**
     * @brief Sets a new student ID.
     * @param studentID The new student ID.
     */
    void setStudentID(const std::string &studentID);

    /**
     * @brief Sets a new couse code.
     * @param ucCode The new course code.
     */
    void setUCCode(const std::string &ucCode);

    /**
     * @brief Sets a new class code.
     * @param classCode The new class code.
     */
    void setClassCode(const std::string &classCode);
};

#endif //PROJAED_ADDREQUEST_H
