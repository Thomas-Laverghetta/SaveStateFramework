#include "SaveState.h"
#include "SaveStateManager.h"

using namespace std;

// initializing static variable next id
unsigned int SaveState::_nextId = 0;

SaveState::SaveState(unsigned int classId) : _id(_nextId++), _classId(classId) 
{
	// Register with SaveStateManager
	SaveStateManager::Register(this);
}

SaveState::SaveState(unsigned int classId, unsigned int id) : _id(id), _classId(classId)
{}

SaveState::~SaveState()
{
	// removing this object from serializable objects
	SaveStateManager::Unregister(this);
}

void SaveStateClassRegister(unsigned int classId, SaveState* obj)
{
	SaveStateManager::RegisterClass(classId, obj);
}
