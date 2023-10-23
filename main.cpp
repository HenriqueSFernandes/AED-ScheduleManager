#include <iostream>
#include "src/lessontime.h"
#include "src/lesson.h"

#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include "src/Menu.h"

using namespace std;



int main() {
    /*
    map<string, course> courses;

    ifstream classes;
    classes.open("../data/classes.csv");
    if (!classes.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    string line;
    getline(classes, line); //ignore first line
    while (getline(classes, line)) {
        vector<string> elements;
        string word;
        istringstream ss(line);
        while (getline(ss, word, ',')) {
            elements.push_back(word);
        }
        string ucCode = elements[1];
        if (courses.find(ucCode) == courses.end()) {


            courses.insert({ucCode, course(elements[0], elements[1], elements[2], stod(elements[3]), stod(elements[4]),
                                           elements[5])});
        } else {
            courses[ucCode].addClass(elements[0], elements[2], stod(elements[3]), stod(elements[4]), elements[5]);
        }

    }
    classes.close();

    course uc1 = courses["L.EIC003"];
    cout << uc1 << endl;*/
    Menu myMenu= Menu();
    myMenu.createMenu();
}

