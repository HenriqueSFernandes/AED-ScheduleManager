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
    void endMenu();
    void listingMenu();
    //Mudanças Leo
    void SeeStudentsInUc();
    void SeeStudentsInYear();
    void SeeStudentsInClass();
    //Fim Mudanças

private:
    ControlUnit Control;

};


#endif //PROJAED_MENU_H
