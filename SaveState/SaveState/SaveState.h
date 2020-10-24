#pragma once
#include <fstream>
class SaveState {
public:
	SaveState(unsigned int classId);
	SaveState(unsigned int classId,unsigned int id);

	/* Serialize state-save child object to save-file.*/
	virtual void Save(std::ifstream& saveFile) = 0;

	/* Deserialize state-save child object from load-file.*/
	virtual void Load(std::ofstream& loadFile) = 0;

	/* Repoints SaveState objects to points using state object array (index == object id).*/
	virtual void Repoint(SaveState* stateObjArr) = 0;

	/* Gets State Save Object ID.*/
	unsigned int GetSaveStateId() { return _id; }

	/* Creates a new state-save object with id specified.*/
	virtual SaveState* New(unsigned int id) = 0;
private:
	// State Save Identifier
	unsigned int _id;
	unsigned int _classId;
	static unsigned int _nextId;

};

