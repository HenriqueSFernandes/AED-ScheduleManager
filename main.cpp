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

template <class T>
void printVector(vector<T> v){
    for (auto i : v){
        cout << i << " ";
    }
    cout << endl;
}

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
        string ucCode=elements[1];
        if(courses.find(ucCode) == courses.end()){


            courses.insert({ucCode , course(elements[0], elements[1], elements[2], stod(elements[3]), stod(elements[4]), elements[5])});
        }else{
            courses[ucCode].addClass(elements[0], elements[2], stod(elements[3]), stod(elements[4]), elements[5]);
        }

    }
    classes.close();

    studentGroup class1 = courses["L.EIC003"].getClasses()["1LEIC11"];
    cout << class1 << endl;

}

