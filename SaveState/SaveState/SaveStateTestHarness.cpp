#include "SaveStateTestHarness.h"
using namespace std;

string file = "testSave.bin";

class MyClass : public SaveState {
public:
	MyClass() { x = 0; }
	MyClass(unsigned int id) : SaveState{ id } {}

	~MyClass() {}

	void Save(ofstream& saveFile) {
		saveFile.write((char*)&x, sizeof(x));
	}

	void Load(ifstream& loadFile) {
		loadFile.read((char*)&x, sizeof(x));
	}

	void Repoint(const std::vector<SaveState*>& SaveStateList) {}

	static SaveState* New(unsigned int id) { return new MyClass(id); }

	unsigned int GetClassId() { return classId; }

	static unsigned int classId;
	int x;
};
unsigned int MyClass::classId = 0;

void Test1() {
	SaveStateClassRegister(MyClass::classId, MyClass::New);

	MyClass test;
	test.x = 55;
	SaveStateSave(file);

	test.x = 13;

	SaveStateLoad(file);

	printf("X = %i\n", test.x); fflush(stdout);
}


class PointerClass : SaveState {
public:
	PointerClass(MyClass* pt) { _pt = pt; _ptID = _pt->GetSaveStateId(); }
	PointerClass(unsigned int id) : SaveState{ id } {}

	~PointerClass() {}

	void Save(ofstream& saveFile) {
		saveFile.write((char*)&_ptID, sizeof(_ptID));
	}

	void Load(ifstream& loadFile) {
		loadFile.read((char*)&_ptID, sizeof(_ptID));
	}

	void Repoint(const std::vector<SaveState*>& SaveStateList) {
		for (auto& ss : SaveStateList) {
			if (ss->GetSaveStateId() == _ptID) {
				_pt = (MyClass*)ss;
				break;
			}
		}
	}

	static SaveState* New(unsigned int id) { return new PointerClass(id); }

	unsigned int GetClassId() { return classId; }

	static unsigned int classId;

	int _ptID;
	MyClass* _pt;
};
unsigned int PointerClass::classId = 1;

void Test2() {
	SaveStateClassRegister(MyClass::classId, MyClass::New);
	SaveStateClassRegister(PointerClass::classId, PointerClass::New);

	MyClass test;
	test.x = 55;

	PointerClass testPt(&test);
	SaveStateSave(file);

	test.x = 13;
	testPt._pt = nullptr;
	testPt._ptID = -1;

	SaveStateLoad(file);

	printf("X = %i , pt X = %i\n", test.x, testPt._pt->x); fflush(stdout);
}