#include <iostream>
#include "src/time.h"
#include "src/lesson.h"
#include "src/course.h"
#include <sstream>
#include <fstream>
#include <map>
#include <string>


using namespace std;
using namespace Time;



int main() {

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
        string codUc=elements[1];
        if(courses.find(codUc)==courses.end()){


            courses.insert({codUc ,course(elements[0],elements[1],elements[2],stod(elements[3]),stod(elements[4]),elements[5])});
        }else{
            courses[codUc].addClass(elements[0],elements[2],stod(elements[3]),stod(elements[4]),elements[5]);
        }

    }
    classes.close();

    lesson lesson1("Friday", 10.5, 12.5, "TP");
    cout << lesson1 << endl;

}

