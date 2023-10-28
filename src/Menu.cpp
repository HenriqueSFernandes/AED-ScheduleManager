//
// Created by nowayjose on 20/10/2023.
//

#include "Menu.h"
#include "ControlUnit.h"
#include "Request.h" //depois retirado acho eu so para teste
//Initializes the main menu and display the options
void Menu::createMenu(){
    this->Control = ControlUnit();

    int InputOption;
    std::cout << "Hello, welcome to my Schedule Management System. What would you like to do?" << std::endl;
    std::cout << "1) Get Schedule of Student" << std::endl;
    this->Control.Start();
    std::cout << "Select an option:" << std::endl;
    std::cout << "1. See Student Schedule" << std::endl;
    std::cout << "2. See Class Schedule" << std::endl;
    std::cout << "3. See Number of Students with at least NUCs" << std::endl;
    std::cout << "4. See Students in a UC" << std::endl;
    std::cout << "5. See Students in a Class" << std::endl;
    std::cout << "6. See Students in a Year" << std::endl;
    std::cout << "7. See UC with Most Students" << std::endl;
    std::cout << "7. TESTE ALTERAR TURMA TEMPORARIO" << std::endl; //TESTE

    int option;
    std::cin >> option;

    switch (option) {
        case 1:
            Menu::SeeStudentSchedule();
            break;
        case 2:
            Menu::SeeClassSchedule();
            break;
        case 3:
            Menu::SeeNumStudentsAtLeastNUCs();
            break;
        case 4:
            Menu::SeeStudentsInUc();
            break;
        case 5:
            Menu::SeeStudentsInClass();
            break;
        case 6:
            Menu::SeeStudentsInYear();
            break;
        case 7:
            Menu::SeeUcFromMostStudents();
            break;
        case 8:
            Menu::AdicionarAlunoATurmaImediatamente();
            break;
        default:
            std::cout << "Invalid option. Please select a valid option." << std::endl;
            break;
    }


}
void Menu::SeeStudentSchedule(){



    this->Control.DisplayStudentSchedule();
}
void Menu::SeeClassSchedule(){

    //std::cout<<"Enter the Uc Code"<<endl;
    //string ucCode;
    //cin>>ucCode;
    //this->Control.DisplayClassSchedule(classCode,ucCode);
    this->Control.DisplayClassSchedule();
}
void Menu::SeeNumStudentsAtLeastNUCs(){

    std::cout<<"Enter the N "<<endl;
    int n;
    cin>>n;
    int result= this->Control.StudentsInAtLeastNUcs(n);
    std::cout<<"There are "<<result<<" students with at least "<<n<<" UCs"<<endl;

}

//Mudanças Leo

void Menu::SeeStudentsInUc(){
    std::cout<<"Enter the UC code of the UC you want to see Students"<<endl;
    string uccode;
    cin >> uccode;
    this->Control.courseStudents(uccode);
}

void Menu::SeeStudentsInYear(){
    std::cout<<"Enter the year you want students from:"<<endl;
    char year;
    cin >> year;
    this->Control.yearStudents(year);
}

void Menu::SeeStudentsInClass(){
    std::cout<<"Enter the class you want to see students from:";
    string classCode;
    cin>> classCode;
    this->Control.classStudents(classCode);
}

void Menu::SeeUcFromMostStudents() {
    this->Control.UCWithMostStudents();
}
void Menu::AdicionarAlunoATurmaImediatamente() {
    //Testing Request
    //202028717,Rute,L.EIC003,1LEIC04
    //202028717,Rute,L.EIC011,2LEIC11
    //202028717,Rute,L.EIC012,2LEIC11
    //vOU ADICIONAR A RUTE A L.EIC004,1LEIC05
    //std::string type,const std::string& upCodeStudent, const std::string& uCCode, const std::string& classCode
    cout<<"upcode"<<endl;
    string upcode;
    cin>>upcode;
    cout<<"classcode"<<endl;
    string classcode;
    cin>>classcode;
    cout<<"uccode"<<endl;
    string uccode;
    cin>>uccode;
    Request * testrequest= new AddRequest("add",upcode,uccode,classcode);
    this->Control.processRequest(testrequest);
    cout<<"verifica se deu"<<endl;

    this->Control.DisplayStudentSchedule();

}
