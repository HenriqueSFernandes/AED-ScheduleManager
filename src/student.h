/// @file student.h
#ifndef PROJAED_STUDENT_H
#define PROJAED_STUDENT_H

#include <set>
#include <tuple>
#include <string>
#include "studentGroup.h"

using namespace std;

/**
 * @brief Class used to represent a student.
 */
class Student {
public:
    /**
     * @brief Default constructor.
     */
    Student() = default;

    /**
     * @brief Parameterized constructor.
     * @param studentId String representing the student ID.
     * @param name String representing the name of the student.
     * @param group A set with the classes the student has.
     */
    Student(string studentId, string name, set<studentGroup> group);

    /**
     * @brief Gets the student ID.
     * @return A string representing the student ID.
     */
    std::string getStudentID() const;

    /**
     * @brief Gets all the classes the student belongs to.
     * @return A set of classes that the student belongs to.
     */
    set<studentGroup> getStudentGroups() const;

    /**
     * @brief Gets the name of the student.
     * @return A string representing the name of the student.
     */
    std::string getName() const;

    /**
     * @brief Sets the newName of the student.
     * @param newName A string representing the newName of the student
     */
    void setName(const std::string &newName);

    /**
     * @brief Sets the student ID.
     * @param studentId A string representing the new student ID.
     */
    void setStudentID(const std::string &studentId);

    /**
     * @brief Adds a new class to the student.
     * @param GroupToAdd
     */
    void addStudentGroup(const studentGroup& GroupToAdd);

    /**
     * @brief Removes a class from the student.
     * @param GroupToRemove
     */
    void removeGroup(const studentGroup& GroupToRemove);

    /**
     * @brief Detects if the student is enrolled in a certain course.
     * @param uc String representing a course.
     * @return Returns true if the student is enrolled in a certain course.
     */
    bool isInUC(const string& uc) const;

    /**
     * @brief Detects if the student is enrolled in a certain class from a course.
     *
     * Complexity is O(n) where n is the amount of class the student has.
     * @param ucCode String representing a course.
     * @param studentGroup String representing a class.
     * @return Returns true if the student is enrolled in a certain class form a course.
     */
    bool isInClass(const string& ucCode, const string& studentGroup) const;

    bool operator<(const Student &other) const {
        return studentID < other.studentID;
    }

    bool operator==(const Student &other) const {
        return (this->studentID == other.studentID) && (this->name == other.name);
    }

    friend std::ostream &operator<<(std::ostream &os, const Student &student);

private:
    std::string studentID;
    std::string name;
    std::set<studentGroup> StudentGroups;
};


#endif //PROJAED_STUDENT_H
