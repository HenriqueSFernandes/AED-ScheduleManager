//
// Created by nowayjose on 20/10/2023.
//

#include <climits>
#include <functional>
#include "Menu.h"
#include "ControlUnit.h"
#include "Request.h" //depois retirado acho eu so para teste

//Initializes the main menu and display the options
void Menu::createMenu() {
    this->Control = ControlUnit();

    bool run = true;
    int InputOption;
    int fileoption;
    string filename;
    while (run) {

        std::cout << "Hello, welcome to the Schedule Management System.\n";
        std::cout << "Would you like to use the Original Version or the Updated Version of the Student DB\n";
        std::cout << "1) Original Version\n2) Updated Version\n";
        cin >> fileoption;

        switch (fileoption) {
            case 1:
                run = false;
                filename = "../data/students_classes.csv";
                break;
            case 2:
                run = false;
                filename = "../data/students_classes_updated.csv";
                break;
            default:
                cout << "Invalid option, choose again.\n";
                break;
        }
    }

    run = true;
    this->Control.Start(filename);
    this->Control.CheckIfThereAreConflicts();
    while (run) {
        std::cout << "Select an option:\n";
        std::cout << "1) Listing menu\n";
        std::cout << "2) Request menu\n";
        std::cout << "3) Leave the program\n";
        int option;
        std::cin >> option;
        switch (option) {
            case 1:
                Menu::listingMenu();
                break;
            case 2:
                Menu::requestMenu();
                break;
            case 3:
                run = false;
                // TODO acrescentar função para dar update do file;
                break;
            case 5:
                this->Control.testvalidadd1();
                break;
            default:
                cout << "Invalid option.\n";
                break;
        }

    }


}

void Menu::listingMenu() {
    int option;
    while (true) {
        cout << "Choose the type of listing you want to see.\n";
        cout << "1) See Schedules\n";
        cout << "2) See Number of Students registered in at least N UCs\n";
        cout << "3) See Students\n";
        cout << "4) See all UCs\n";
        cin >> option;
        switch (option) {
            case 1:
                Menu::scheduleMenu();
                break;
            case 2:
                Menu::SeeNumStudentsAtLeastNUCs();
                break;
            case 3:
                Menu::studentMenu();
                break;
            case 4:
                Menu::SeeUcFromMostStudents();
                break;

            default:
                cout << "Invalid option.\n";
                continue;
        }
        break;

    }

}

void Menu::requestMenu() {
    int option;
    while (true){
        cout << "Choose the desired operation\n";
        cout << "1) Create request\n";
        cout << "2) Remove last pending request (WIP)\n";
        cout << "3) Process pending requests\n";
        cout << "4) Undo last request (WIP)\n";
        cin >> option;
        switch (option){
            case 1:
                Menu::createRequest();
                break;
            case 2:
                break;
            case 3:
                this->Control.processAllRequests();
                break;
            case 4:
                break;
            default:
                cout << "Invalid option.\n";
                continue;
        }
        break;
    }
}

void Menu::scheduleMenu() {
    int option;
    while (true) {
        cout << "What do you want to see?\n";
        cout << "1) Student Schedule\n";
        cout << "2) Class Schedule\n";
        cin >> option;
        switch (option) {
            case 1:
                Menu::SeeStudentSchedule();
                break;
            case 2:
                Menu::SeeClassSchedule();
                break;
            default:
                cout << "Invalid option.\n";
                continue;
        }
        break;
    }
}

void Menu::studentMenu() {
    int option;
    while (true) {
        cout << "Choose the type of student listing you want to see.\n";
        cout << "1) See all Students in an UC\n";
        cout << "2) See all Students in a Year\n";
        cout << "3) See all Students in a Class\n";

        cin >> option;
        switch (option) {
            case 1:
                Menu::SeeStudentsInUc();
                break;
            case 2:
                Menu::SeeStudentsInYear();
                break;
            case 3:
                Menu::SeeStudentsInClass();
                break;
            default:
                cout << "Invalid option.\n";
                continue;
        }
        break;

    }

}

//teu se calhar so aquele da contagem de alunos em n cadeiras
//eu so vou fazer o meu set com resultado ter ordens diferentes, pois dps o cout fica sempre por ordem do set res
//Fu ver e vector tipon faço com vector na mesma a pesquisar por ordens dif?????
// ou mudo para set
//a notaçao dessa funcao e um quites estranha
/*function<bool(Student,Student)> Menu::optionStudentMenu(){
    int option;
    while(true){
        cout<<"What's the order you want to see students in?"<<endl;
        cout<<"1) UP code ascending"<<endl;
        cout<<"2) UP code descending"<<endl;
        cout<<"3) Alphabetical ascending"<<endl;
        cout<<"4) Alphabetical descending"<<endl;
        cin>>option;
        switch (option){
            case 1:
                return [](Student a, Student b){return a.getStudentID()<b.getStudentID();};
                break;
            case 2:
                return [](Student a, Student b){return a.getStudentID()>b.getStudentID();};
                break;
            case 3:
                return [](Student a, Student b){return a.getName()<b.getName();};
                break;
            case 4:
                return [](Student a, Student b){return a.getName()>b.getName();};
                break;
            default:
                cout<<"Invalid option."<<endl;
                continue;
        }
        break;
 }
*/

void Menu::SeeStudentSchedule() {
    this->Control.DisplayStudentSchedule();
}

void Menu::SeeClassSchedule() {

    //std::cout<<"Enter the Uc Code"<<endl;
    //string ucCode;
    //cin>>ucCode;
    //this->Control.DisplayClassSchedule(classCode,ucCode);
    this->Control.DisplayClassSchedule();
}

void Menu::SeeNumStudentsAtLeastNUCs() {

    std::cout << "Enter the N \n";
    int n;
    cin >> n;
    int result = this->Control.StudentsInAtLeastNUcs(n);
    std::cout << "There are " << result << " students with at least " << n << " UCs\n";

}


void Menu::SeeStudentsInUc() {
    std::cout << "Enter the UC code of the UC you want to see Students\n";
    string uccode;
    cin >> uccode;
    this->Control.courseStudents(uccode);
}

void Menu::SeeStudentsInYear() {
    std::cout << "Enter the year you want students from:\n";
    char year;
    cin >> year;
    this->Control.yearStudents(year);
}

void Menu::SeeStudentsInClass() {
    std::cout << "Enter the class you want to see students from:\n";
    string classCode;
    cin >> classCode;
    this->Control.classStudents(classCode);
}

void Menu::SeeUcFromMostStudents() {
    this->Control.UCWithMostStudents();
}


void Menu::createRequest() {
    int requesttype;
    while (true) {
        cout << "What type of request do you want to do?\n";
        cout << "1) Add a Class\n";
        cout << "2) Remove a Class\n";
        cout << "3) Switch Classes\n";

        std::cin >> requesttype;


        switch (requesttype) {
            case 1:
                this->Control.createAdd();
                break;
            case 2:
                this->Control.createRemove();
                break;
            case 3:
                this->Control.createSwitch();
                break;
            default:
                cout << "Invalid option.\n";
                continue;
        }
        break;
    }

}


//funções de teste, inutilizadas por enquanto (supostamente)
void Menu::AdicionarAlunoATurmaImediatamente() {
    cout << "upcode\n";
    string upcode;
    cin >> upcode;
    cout << "classcode\n";
    string classcode;
    cin >> classcode;
    cout << "uccode\n";
    string uccode;
    cin >> uccode;
    Request *testrequest = new AddRequest("add", upcode, uccode, classcode);
    this->Control.processRequest(testrequest);
    cout << "verifica se deu\n";


    this->Control.DisplayStudentSchedule();
    Menu::AdicionarAlunoATurmaImediatamente();
}

void Menu::RemoverAlunoATurmaImediatamente() {
    cout << "upcode\n";
    string upcode;
    cin >> upcode;
    cout << "classcode\n";
    string classcode;
    cin >> classcode;
    cout << "uccode\n";
    string uccode;
    cin >> uccode;
    Request *testrequest = new RemoveRequest("remove", upcode, uccode, classcode);
    this->Control.processRequest(testrequest);
    cout << "verifica se deu\n";


    this->Control.DisplayStudentSchedule();
    Menu::RemoverAlunoATurmaImediatamente();
}


void Menu::TrocarTurmaInstantaneamente() {
    cout << "upcode\n";
    string upcode;
    cin >> upcode;
    cout << "classcode1\n";
    string classcode1;
    cin >> classcode1;
    cout << "uccode1\n";
    string uccode1;
    cin >> uccode1;
    cout << "classcode2\n";
    string classcode2;
    cin >> classcode2;
    cout << "uccode2\n";
    string uccode2;
    cin >> uccode2;
    Request *testrequest = new SwitchRequest("switch", upcode, uccode1, uccode2, classcode1, classcode2);
    this->Control.processRequest(testrequest);
    cout << "verifica se deu\n";


    this->Control.DisplayStudentSchedule();
    Menu::TrocarTurmaInstantaneamente();
}
