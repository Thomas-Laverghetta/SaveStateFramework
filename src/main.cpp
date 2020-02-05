#include <iostream>
#include "SerializationManager.h"
#include "Serializable.h"
#include "LinkedList.h"
#include "Student.h"

using namespace std;

int main() {
	SerializationManager * SM = SerializationManager::GetInstance();
	SM->SetupFile((char*)"file.txt");
	LinkedList oduRoster;
	//Student thomas("Thomas", "Laverghetta", 4.0, 21, "CMSE!");
	//Student kyle("Kyle", "Tanyag", 4.0, 22, "Eh.");
    //Student BOYYYYY("BOY", "N***A", 4.0, 22, "YEAH BOYY!!");
    Student mark;

    Student kyle;
	Student thomas;
	oduRoster.addStudent(mark);
	oduRoster.addStudent(thomas);
	oduRoster.addStudent(kyle);
	//oduRoster.addStudent(BOYYYYY);
	SM->Load();
	//    cout << oduRoster;
	oduRoster.display(cout);
}

//class Professor: public Serializable{
//private:
//    string f_name;
//    string l_name;
//    float power_level;
//
//public:
//
//    Professor(){
//        f_name = "Jim";
//        l_name = "Leathrum";
//        power_level = 9001;
//    }
//    Professor(string first){
//        f_name = first;
//        l_name = "Testing";
//        power_level = 9001;
//    }
//
//    void OnSave(std::ofstream &file) {
//        file << f_name << endl
//             << l_name << endl
//             << power_level << endl;
//    }
//    void OnLoad(std::ifstream &f) {
//        f   >> f_name
//            >> l_name
//            >> power_level;
//    }
//    void print(){
//        cout << f_name << endl
//             << l_name << endl
//             << power_level << endl << endl;
//    }
//    void SetProfData(string First, string Last){
//        f_name = First;
//        l_name = Last;
//    }
//};

//class Student: public Serializable{
//private:
//    static unsigned int classID;
//    ///Professor* prof;
//    float gpa;
//    string f_name;
//    string l_name;
//    int age;
//    string complaint;
//    unsigned int profNum;
//public:
//    const static unsigned int ClassID;
//    Student():Serializable(ClassID){
//        f_name = "Mark";
//        l_name = "Patton";
//        gpa = 2.8;
//        age = 22;
//        complaint = "I_CAN_DO_IT!";
//        //prof = nullptr;
//    }
//    void SetStudentData(string First, string Last){
//        f_name = First;
//        l_name = Last;
//    }
//    void PrintStudentData(){
//        cout << f_name << endl
//             << l_name << endl
//             << gpa    << endl
//             << age    << endl
//             << complaint << endl << endl;
//
//             //prof->print();
//    }
//    std::string GetName(){
//        return f_name;
//    }
//    Student& operator=(const Student s){
//        f_name = s.f_name;
//    }
//
//
//    /// Developer Required Implementation Functions
//    void OnSave(std::ofstream &file){
//        file << f_name << endl
//             << l_name << endl
//             << gpa    << endl
//             << age    << endl
//             << complaint
//             << endl;
//    }
//
//    void OnLoad(std::ifstream &file){
//        file >> f_name
//             >> l_name
//             >> gpa
//             >> age
//             >> complaint;
//    }
////    void RePoint(){
////    }
//
//    Serializable* clone(){new Student;}
//};
//
//int main() {
//    new SerializationManager();
//
//    return 0;
//}
