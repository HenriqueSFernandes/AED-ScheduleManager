//
// Created by nowayjose on 20/10/2023.
//

#ifndef PROJAED_MENU_H
#define PROJAED_MENU_H

#include "ControlUnit.h"

class Menu {
public:
    void createMenu();

    void SeeStudentSchedule();

    void SeeClassSchedule();

    void SeeNumStudentsAtLeastNUCs();

    void SeeNumStudentsAtMostNUCs();

    void SeeNumStudentsInNUCs();

    void listingMenu();

    void requestMenu();

    void scheduleMenu();

    void studentMenu();

    void SeeStudentsInUc(function<bool(Student,Student)> comp);

    void SeeStudentsInYear(function<bool(Student,Student)> comp);

    void SeeStudentsInClass(function<bool(Student,Student)> comp);

    void createRequest();

    function<bool(Student, Student)> optionStudentMenu();

private:
    ControlUnit Control;

    void SeeUcFromMostStudents();


    void SeeNumStudentsInExactNUCs();
};


#endif //PROJAED_MENU_H
