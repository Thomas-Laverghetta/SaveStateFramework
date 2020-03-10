#include <iostream>
#include "SerializationManager.h"
#include "Serializable.h"
#include "LinkedList.h"
#include "Student.h"

using namespace std;
void Initialization() {
	LinkedList::Initialization();
}
int main() {
	SerializationManager * SM = SerializationManager::GetInstance();
	SM->SetupFile((char*)"file.txt");
	Initialization();
	LinkedList oduRoster;
 //   Student mark;
 //   Student kyle;
	//Student thomas;
	//oduRoster.addStudent(mark);
 //   oduRoster.addStudent(thomas);
 //   oduRoster.addStudent(kyle);

	SM->Load();
	//    cout << oduRoster;
	oduRoster.display(cout);
}