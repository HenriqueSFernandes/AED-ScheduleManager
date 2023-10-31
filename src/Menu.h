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

    void endMenu();

    void listingMenu();

    void requestMenu();

    void scheduleMenu();

    void studentMenu();

    void SeeStudentsInUc(function<bool(Student,Student)> comp);

    void SeeStudentsInYear(function<bool(Student,Student)> comp);

    void SeeStudentsInClass(function<bool(Student,Student)> comp);

    void AdicionarAlunoATurmaImediatamente();

    void createRequest();

    void RemoverAlunoATurmaImediatamente();

    void TrocarTurmaInstantaneamente();

    function<bool(Student, Student)> optionStudentMenu();

    //TESTING
    void Testing();

private:
    ControlUnit Control;

    void SeeUcFromMostStudents();


    void SeeNumStudentsInExactNUCs();
};


#endif //PROJAED_MENU_H
