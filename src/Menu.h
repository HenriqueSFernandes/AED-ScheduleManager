/// @file Menu.h
#ifndef PROJAED_MENU_H
#define PROJAED_MENU_H

#include "ControlUnit.h"

/**
 * @brief Class used to represent the menu the user uses to navigate.
 */
class Menu {
public:
    /**
     * @brief Creates the menu.
     */
    void createMenu();

    /**
     * @brief Displays the schedule of a student.
     */
    void SeeStudentSchedule();

    /**
     * @brief Displays the schedule of a class.
     */
    void SeeClassSchedule();

    /**
     * @brief Displays the student enrolled in exactly N courses.
     */
    void SeeNumStudentsInExactNUCs();

    /**
     * @brief Displays the students enrolled in at least N courses.
     */
    void SeeNumStudentsAtLeastNUCs();

    /**
     * @brief Displays the student enrolled in at most N courses.
     */
    void SeeNumStudentsAtMostNUCs();

    /**
     * @brief Displays all the courses starting with the one with the most student.
     */
    void SeeUcFromMostStudents();

    /**
     * @brief Enters the submenu for listing the students in courses.
     */
    void SeeNumStudentsInNUCs();

    /**
     * @brief Enters the listing menu, which allows the user to list students, see schedules etc.
     */
    void listingMenu();

    /**
     * @brief Enters the request menu, which allows the user to create, delete and manage requests.
     */
    void requestMenu();

    /**
     * @brief Enters the schedule menu, which allows the user to see the schedule for a student or a class.
     */
    void scheduleMenu();

    /**
     * @brief Enters the student menu, which allows the user to see all students from a year, course or class.
     */
    void studentMenu();

    /**
     * @brief Lists all the students in a specific course.
     * @param comp A boolean function that compares the students, allowing the program to list the students in different ways.
     */
    void SeeStudentsInUc(function<bool(Student, Student)> comp);

    /**
     * @brief Lists all the students in a specific year.
     * @param comp A boolean function that compares the students, allowing the program to list the students in different ways.
     */
    void SeeStudentsInYear(function<bool(Student, Student)> comp);

    /**
     * @brief Lists all the students in a specific class.
     * @param comp A boolean function that compares the students, allowing the program to list the students in different ways.
     */
    void SeeStudentsInClass(function<bool(Student, Student)> comp);

    /**
     * @brief Enters the menu for creating request, allowing users to add, remove or switch classes.
     */
    void createRequest();

    /**
     * @brief Allows the user to select different sorting options for displaying the students.
     * @return A boolean function the compares students.
     */
    function<bool(Student, Student)> optionStudentMenu();

private:
    ControlUnit Control;

};


#endif //PROJAED_MENU_H
