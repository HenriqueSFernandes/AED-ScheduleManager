#ifndef STUDENTGROUP_H
#define STUDENTGROUP_H

#include <iostream>
#include <string>

class studentGroup {
public:
    // Constructors
    studentGroup() = default;

    studentGroup(const std::string &uccode, const std::string &classCode);

    const std::string &getClassCode() const {
        return classCode;
    }

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