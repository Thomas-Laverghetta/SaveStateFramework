#include "SaveState.h"
#include "SaveStateManager.h"

// initializing static variable next id
unsigned int SaveState::_nextId = 0;

SaveState::SaveState(unsigned int classId) : _id(_nextId++), _classId(classId) 
{
	// Register with SaveStateManager
}

SaveState::SaveState(unsigned int classId, unsigned int id) : _id(id), _classId(classId)
{}
