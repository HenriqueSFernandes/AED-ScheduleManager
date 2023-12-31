/// @file studentGroup.h
#ifndef STUDENTGROUP_H
#define STUDENTGROUP_H

#include <iostream>
#include <string>

/**
 * @brief Class used to represent a class (group of students).
 */
class studentGroup {
public:
    /**
     * @brief Default constructor.
     */
    studentGroup() = default;

    /**
     * @brief Parameterized constructor.
     * @param ucCode String representing the course code.
     * @param classCode String representing the class code.
     */
    studentGroup(const std::string &ucCode, const std::string &classCode);

    /**
     * @brief Gets the class code.
     * @return A string representing the class code.
     */
    const std::string &getClassCode() const {
        return classCode;
    }

    /**
     * @brief Gets the course code.
     * @return A string representing the course code.
     */
    const std::string &getUcCode() const {
        return UcCode;
    }

    bool operator<(const studentGroup &other) const {
        // Define a comparison logic here based on your criteria.
        // For example, you can compare based on class code or other fields.
        return this->classCode + this->UcCode < other.classCode + other.UcCode;
    }

    friend std::ostream &operator<<(std::ostream &os, const studentGroup &group) {
        os << "UcCode: " << group.UcCode << ", Class Code: " << group.classCode;
        return os;
    }


private:

    std::string classCode;
    std::string UcCode;


};

#endif