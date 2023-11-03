#include "Menu.h"
#include "ControlUnit.h"
#include "Request.h"

//Initializes the main menu and display the options
void Menu::createMenu() {
    this->Control = ControlUnit();
    string fileoption;
    string filename;
    while (true) {

        std::cout << "Hello, welcome to the Schedule Management System.\n";
        std::cout << "Would you like to use the Original Version or the Updated Version of the Student DB\n";
        std::cout << "1) Original Version\n2) Updated Version\n";
        cin >> fileoption;

        if (fileoption == "1") {
            filename = "../data/students_classes.csv";
            break;
        } else if (fileoption == "2") {
            filename = "../data/students_classes_updated.csv";
            break;
        } else {
            cout << "Invalid option, choose again.\n";
        }
    }
    this->Control.LoadCSV(filename);
    while (true) {
        std::cout << "Select an option:\n";
        std::cout << "1) Listing menu\n";
        std::cout << "2) Request menu\n";
        std::cout << "3) Leave the program\n";
        string option;
        std::cin >> option;
        if (option == "1") {
            Menu::listingMenu();
        } else if (option == "2") {
            Menu::requestMenu();
        } else if (option == "3") {
            this->Control.WritetoInvalidRequests();
            this->Control.saveChanges();
            this->Control.clearMemory();
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }
}

void Menu::listingMenu() {
    string option;
    while (true) {
        cout << "Choose the type of listing you want to see.\n";
        cout << "1) See Schedules\n";
        cout << "2) See Number of Students in N UCs\n";
        cout << "3) See Students\n";
        cout << "4) See all UCs\n";
        cout << "5) Go back\n";
        cin >> option;
        if (option == "1") {
            Menu::scheduleMenu();
        } else if (option == "2") {
            Menu::SeeNumStudentsInNUCs();
        } else if (option == "3") {
            Menu::studentMenu();
        } else if (option == "4") {
            Menu::SeeUcFromMostStudents();
        } else if (option == "5")
            break;
        else {
            cout << "Invalid option.\n";
        }
    }
}


void Menu::SeeNumStudentsInNUCs() {
    string option;
    while (true) {
        cout << "Choose the type of listing you want to see.\n";
        cout << "1) See in at least N UCs\n";
        cout << "2) See in exact N UCs\n";
        cout << "3) See in more than N UCs\n";
        cout << "4) Go back\n";
        cin >> option;
        if (option == "1") {
            Menu::SeeNumStudentsAtLeastNUCs();
        } else if (option == "2") {
            Menu::SeeNumStudentsInExactNUCs();
        } else if (option == "3") {
            Menu::SeeNumStudentsAtMostNUCs();
        } else if (option == "4") {
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }

}

void Menu::requestMenu() {
    string option;
    while (true) {
        cout << "Choose the desired operation\n";
        cout << "1) Create request\n";
        cout << "2) Remove last pending request\n";
        cout << "3) Process pending requests\n";
        cout << "4) Undo last request\n";
        cout << "5) Go back\n";
        cin >> option;
        if (option == "1") {
            Menu::createRequest();
        } else if (option == "2") {
            this->Control.removeLastPendingRequest();
        } else if (option == "3") {
            this->Control.processAllRequests();
        } else if (option == "4") {
            int amount;
            cout << "How many request do you want to undo?\n";
            cin >> amount;
            this->Control.undoRequest(amount);
        } else if (option == "5") {
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }
}

void Menu::scheduleMenu() {
    string option;
    while (true) {
        cout << "What do you want to see?\n";
        cout << "1) Student Schedule\n";
        cout << "2) Class Schedule\n";
        cout << "3) Go back\n";
        cin >> option;
        if (option == "1") {
            Menu::SeeStudentSchedule();
        } else if (option == "2") {
            Menu::SeeClassSchedule();
        } else if (option == "3") {
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }
}

void Menu::studentMenu() {
    string option;
    function<bool(Student, Student)> func;
    while (true) {
        cout << "Choose the type of student listing you want to see.\n";
        cout << "1) See all Students in an UC\n";
        cout << "2) See all Students in a Year\n";
        cout << "3) See all Students in a Class\n";
        cout << "4) Go back\n";
        cin >> option;
        if (option == "1") {
            func = Menu::optionStudentMenu();
            Menu::SeeStudentsInUc(func);
        } else if (option == "2") {
            func = Menu::optionStudentMenu();
            Menu::SeeStudentsInYear(func);
        } else if (option == "3") {
            func = Menu::optionStudentMenu();
            Menu::SeeStudentsInClass(func);
        } else if (option == "4") { break; }
        else {
            cout << "Invalid option.\n";
        }
    }
}

function<bool(Student, Student)> Menu::optionStudentMenu() {
    string option;
    while (true) {
        cout << "What's the order you want to see students in?\n";
        cout << "1) UP code ascending\n";
        cout << "2) UP code descending\n";
        cout << "3) Alphabetical ascending\n";
        cout << "4) Alphabetical descending\n";
        cin >> option;
        if (option == "1") {
            return [](Student a, Student b) { return a.getStudentID() < b.getStudentID(); };
        } else if (option == "2") {
            return [](Student a, Student b) { return a.getStudentID() > b.getStudentID(); };
        } else if (option == "3") {
            return [](Student a, Student b) { return a.getName() < b.getName(); };
        } else if (option == "4") {
            return [](Student a, Student b) { return a.getName() > b.getName(); };
        } else {
            cout << "Invalid option." << endl;
        }
    }
}


void Menu::SeeStudentSchedule() {
    this->Control.DisplayStudentSchedule();
}

void Menu::SeeClassSchedule() {
    this->Control.DisplayClassSchedule();
}

void Menu::SeeNumStudentsAtLeastNUCs() {
    std::cout << "Enter the N \n";
    int n;
    cin >> n;
    int result = this->Control.StudentsInAtLeastNUcs(n);
    std::cout << "There are " << result << " students with at least " << n << " UCs\n";
}

void Menu::SeeNumStudentsAtMostNUCs() {
    std::cout << "Enter the N \n";
    int n;
    cin >> n;
    int result = this->Control.StudentsInAtMostNUcs(n);
    std::cout << "There are " << result << " students with at least " << n << " UCs\n";
}

void Menu::SeeNumStudentsInExactNUCs() {
    std::cout << "Enter the N \n";
    int n;
    cin >> n;
    int result = this->Control.StudentsInExactNUcs(n);
    std::cout << "There are " << result << " students with at least " << n << " UCs\n";
}

void Menu::SeeStudentsInUc(function<bool(Student, Student)> func) {
    std::cout << "Enter the UC code of the UC you want to see Students\n";
    string courseCode;
    cin >> courseCode;
    this->Control.courseStudents(courseCode, func);
}

void Menu::SeeStudentsInYear(function<bool(Student, Student)> func) {
    std::cout << "Enter the year you want students from:\n";
    char year;
    cin >> year;
    this->Control.yearStudents(year, func);
}

void Menu::SeeStudentsInClass(function<bool(Student, Student)> func) {
    std::cout << "Enter the class you want to see students from:\n";
    string classCode;
    cin >> classCode;
    this->Control.classStudents(classCode, func);
}

void Menu::SeeUcFromMostStudents() {
    this->Control.UCWithMostStudents();
}


void Menu::createRequest() {
    string option;
    while (true) {
        cout << "What type of request do you want to do?\n";
        cout << "1) Add a Class\n";
        cout << "2) Remove a Class\n";
        cout << "3) Switch Classes\n";
        cout << "4) Go back\n";

        std::cin >> option;

        if (option == "1") {
            this->Control.createAdd();
        } else if (option == "2") {
            this->Control.createRemove();
        } else if (option == "3") {
            this->Control.createSwitch();
        } else if (option == "4") {
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }
}
