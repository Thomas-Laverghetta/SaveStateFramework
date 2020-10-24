#include "SaveStateManager.h"
#include <algorithm>

// Initializing Static Variables
vector<SaveState*> SaveStateManager::_SaveStateList = vector<SaveState*>();
map<unsigned int, SaveState*> SaveStateManager::_classMap = map<unsigned int, SaveState*>();
string SaveStateManager::_loadFile = "";
string SaveStateManager::_saveFile = "";

void SaveStateManager::Init(string saveFile, string loadFile)
{
	_saveFile = saveFile;
	_loadFile = loadFile;
}

void SaveStateManager::Register(SaveState* ss)
{
	_SaveStateList.push_back(ss);
}

void SaveStateManager::Unregister(SaveState* ss)
{
	// removing ss from vector
	_SaveStateList.erase(std::remove(_SaveStateList.begin(), _SaveStateList.end(), ss), _SaveStateList.end());
}

void SaveStateManager::SaveAll()
{
	// Creating binary file
	ofstream file{ _saveFile, std::ios::binary | std::ios::out };
	for (auto& ss : _SaveStateList) {
		// saving object id
		unsigned int id = ss->GetSaveStateId();
		file.write((char*)&id, sizeof(id));
		
		// saving class type
		id = ss->GetSaveStateClassType();
		file.write((char*)&id, sizeof(id));

		// saving object
		ss->Save(file);
	}
}

unsigned int FindId(vector<SaveState*>& ss, unsigned int id) {
	unsigned int r = ss.size() - 1;
	unsigned int l = 0;
	while (l <= r) {
		int m = l + (r - l) / 2;

		// Check if x is present at mid 
		if (ss[m]->GetSaveStateId() == id)
			return m;

		// If x greater, ignore left half 
		if (ss[m]->GetSaveStateId() < id)
			l = m + 1;

		// If x is smaller, ignore right half 
		else
			r = m - 1;
	}

	// if we reach here, then element was 
	// not present 
	return -1;
}
void SaveStateManager::LoadAll()
{
	ifstream file{ _loadFile, std::ios::binary | std::ios::in };
	if (!file.is_open()) {
		printf("ERROR: No Load File %s", _loadFile.c_str()); fflush(stdout);
		exit(0);
	}

	while (!file.eof()) {
		unsigned int objId;
		file.read((char*)&objId, sizeof(objId));

		unsigned int classId;
		file.read((char*)&classId, sizeof(classId));

		unsigned int index = FindId(_SaveStateList, objId);
		
		// if init object exist then load to it
		if (index != -1) {
			_SaveStateList[index]->Load(file);
		}

		// create dynamic state object
		else {
			_SaveStateList.push_back(_classMap.find(classId)->second->New(objId));
		}
	}
}

void SaveStateManager::RegisterClass(unsigned int classId, SaveState* obj)
{
	_classMap[classId] = obj;
}

std::vector<SaveState*> SaveStateManager::GetSaveStateList()
{
	return _SaveStateList;
}
