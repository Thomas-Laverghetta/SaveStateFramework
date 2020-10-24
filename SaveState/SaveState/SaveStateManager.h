#pragma once
#include "SaveState.h"
#include <vector>
#include <map>

class SaveStateManager
{
public:
	/* Registers SaveState with manager.*/
	void Register(SaveState* ss);

	/* Remove object from save list.*/
	void UnRegister(SaveState* ss);

	/* Saves all objects to file.*/
	void SaveAll();

	/* Loads all objects from file.*/
	void LoadAll();
private:
	std::vector<SaveState*> _SaveStateList;
	std::map<unsigned int, SaveState*> _classMap;
};

