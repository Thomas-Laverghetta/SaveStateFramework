#pragma once
#include "SaveState.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

class SaveStateManager
{
public:
	/* Initializes save state manager.*/
	static void Init(string saveFile, string loadFile);

	/* Registers SaveState with manager.*/
	static void Register(SaveState* ss);

	/* Remove object from save list.*/
	static void Unregister(SaveState* ss);

	/* Saves all objects to file.*/
	static void SaveAll();

	/* Loads all objects from file.*/
	static void LoadAll();

	/* Registers Class for class mapping.
	All SaveState Classes must create static */
	static void RegisterClass(unsigned int classId, SaveState* obj);

	/* Gets the save-state list.*/
	static vector<SaveState*> GetSaveStateList();
private:
	static vector<SaveState*> _SaveStateList;
	static map<unsigned int, SaveState*> _classMap;
	static string _loadFile;
	static string _saveFile;
};

