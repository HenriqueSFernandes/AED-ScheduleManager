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
    std::cout<< "Select 1 fot Student schedule 2 for class schedule"<<endl;
    int option;
    cin>>option;
    if(option==1){
        Menu::SeeStudentSchedule();
    }else if(option==2){
        Menu::SeeClassSchedule();
    } else if(option==3){
        Menu::SeeNumStudentsAtLeastNUCs();
    }


}
void Menu::SeeStudentSchedule(){
    std::cout<<"Enter the UPCODE OF THE STUDENT"<<endl;
    string upcode;
    cin>>upcode;
    this->Control.DisplayStudentSchedule(upcode);
}
void Menu::SeeClassSchedule(){
    std::cout<<"Enter the Class Code"<<endl;
    string classCode;
    cin>>classCode;
    std::cout<<"Enter the Uc Code"<<endl;
    string ucCode;
    cin>>ucCode;
    this->Control.DisplayClassSchedule(classCode,ucCode);
}
void Menu::SeeNumStudentsAtLeastNUCs(){

    std::cout<<"Enter the N "<<endl;
    int n;
    cin>>n;
    int result= this->Control.StudentsInAtLeastNUcs(n);
    std::cout<<"There are "<<result<<" students with at least "<<n<<" UCs"<<endl;

}