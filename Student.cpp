//
// Created by tomlaverghettamsve on 11/14/19.
//

#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
Student::Student() {
    f_name = "Mark";
    l_name = "Patton";
    gpa = 2.8;
    age = 22;
    quote = "I_CAN_DO_IT!";
}

//------------------------------------------------------------------------------
Student::Student(string first, string last, float x, int y, string z) {
    f_name = first;
    l_name = last;
    gpa = x;
    age = y;
    quote = z;
}

//------------------------------------------------------------------------------
Student::~Student() {
    //cout << f_name << " " << l_name
    //	<< " has left ODU." << endl;
}

//------------------------------------------------------------------------------
void Student::setStudentName(string First, string Last) {
    f_name = First;
    l_name = Last;
}

//------------------------------------------------------------------------------
void Student::printStudentData() {
    cout << f_name << endl
         << l_name << endl
         << gpa << endl
         << age << endl
         << quote << endl << endl;
}

//------------------------------------------------------------------------------
string Student::getFullName() const {
    return f_name + " " + l_name;
}

//------------------------------------------------------------------------------
ostream& operator<<(ostream& outs, const Student& prt) {
    outs << prt.getFullName();
    return outs;
}