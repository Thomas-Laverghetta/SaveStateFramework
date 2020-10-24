#pragma once
#include <fstream>
#include <string>

// Save State Class
class SaveState {
public:
	/* Constuctor for SaveState objects.*/
	SaveState(unsigned int classId);

	/* Constuctor for SaveState when loading dynamic object.*/
	SaveState(unsigned int classId, unsigned int id);

	/* Serialize state-save child object to save-file.*/
	virtual void Save(std::ofstream& saveFile) = 0;

	/* Deserialize state-save child object from load-file.*/
	virtual void Load(std::ifstream& loadFile) = 0;

	/* Repoints SaveState objects to points using state object array.*/
	virtual void Repoint(const std::vector<SaveState*>& SaveStateList) = 0;

	/* Gets State Save Object ID.*/
	unsigned int GetSaveStateId() { return _id; }

	/* Gets State Save Object class ID.*/
	unsigned int GetSaveStateClassType() { return _classId; }

	/* Creates a new state-save object with id specified.*/
	// virtual SaveState* NewSaveObj(unsigned int id) = 0;

	/* Unregisters with save state manager.*/
	~SaveState();
private:
	// State Save Identifier
	unsigned int _id;
	unsigned int _classId;
	static unsigned int _nextId;
};

// Function pointer to static New Function that each class must create
typedef SaveState* (*NewFunctor)(unsigned int);

///// Functions for SaveStateManager accessors

/* Registers class with Save-State Manager*/
void SaveStateClassRegister(unsigned int classId, NewFunctor newFunctor);

/* Loads system states from load binary file*/
void SaveStateLoad(std::string loadFile);

/* Loads system states from load binary file*/
void SaveStateSave(std::string saveFile);