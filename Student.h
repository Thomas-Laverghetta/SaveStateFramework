//
// Created by tomlaverghettamsve on 11/14/19.
//
#pragma once
#ifndef TESTER_STUDENT_H
#define TESTER_STUDENT_H

#include <string>
#include <iostream>
#include "Serializable.h"
#include <stdio.h>
#include <string>
using namespace std;

/* Students are objects that contain
 * general information about a student.
 * This includes their first and last name,
 * GPA, age, and their senior quote.
 */

class Student {

private:
    char f_name;
    char l_name;
    float gpa;
    int age;
    char quote;
    //unsigned int classID{1};
public:
    
	/**
     * Constructor
     */
	Student();

    /**
     * Create a student with information
     */
    Student(char first, char last, float gpa, int age, char quote);

    /**
     * Destructor. Prints that student has left ODU
     */
    ~Student();


    /**
     * Sets student's first and last name
     */
    void setStudentName(char First, char Last);

    /**
     * Prints all student data
     */
    void printStudentData();

    /**
     * Gets a student's first name
     */
    //string getFullName() const;

    void OnSave(std::ofstream& file){
        /// Implement ClassID here
        //file.write((char* )&classID,sizeof(classID));
        file.write((char* )&f_name, sizeof(f_name));
        file.write((char* )&l_name, sizeof(l_name));
        file.write((char* )&gpa, sizeof(gpa));
        file.write((char* )&age, sizeof(age));
        file.write((char* )&quote, sizeof(quote));

//        file << classID << std::endl << f_name << std::endl <<
//            l_name << std::endl << gpa << endl << age << endl <<
//            quote << endl << endl;

    }
    void OnLoad(std::ifstream& file){
        file.read((char* )&f_name, sizeof(f_name));
        file.read((char* )&l_name, sizeof(l_name));
        file.read((char* )&gpa, sizeof(gpa));
        file.read((char* )&age, sizeof(age));
        file.read((char* )&quote, sizeof(quote));
        //file >> f_name >> l_name >> gpa >> age >> quote;
    }
};

ostream& operator<<(ostream& outs, const Student& prt);

#endif // !STUDENT_H
