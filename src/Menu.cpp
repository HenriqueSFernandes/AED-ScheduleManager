//
// Created by nowayjose on 20/10/2023.
//

#include "Menu.h"
#include "ControlUnit.h"
void Menu::createMenu(){
    this->Control=ControlUnit();


    int InputOption;
    std::cout<<"Hello welcome to my Schedule Management System What would you like to do?"<<endl;
    std::cout<<"1) Get Schedule of Student"<<endl;
    this->Control.Start();
    Menu::SeeStudentSchedule();

}
void Menu::SeeStudentSchedule(){
    std::cout<<"Enter the UPCODE OF THE STUDENT"<<endl;
    string upcode;
    cin>>upcode;
    this->Control.DisplayStudentSchedule(upcode);
}