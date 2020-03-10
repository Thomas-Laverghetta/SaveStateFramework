#include "SerializationManager.h"

// Initializing singleton
SerializationManager* SerializationManager::_instance = nullptr;

/// File to save states to
void SerializationManager::SetupFile(char* fileName) {
	m_filename = fileName;
}

/// objects will register pointers to serialize and their objects their pointing to
void SerializationManager::RegisterPointer(double Pt_ID, Serializable::PointerObj* ptr) {
	m_pointer_map.emplace(Pt_ID, ptr);
}

// Finds pointer in point_map and removes it
void SerializationManager::RemovePointer(double ptrID) {
	auto iter = m_pointer_map.find(ptrID);

	// testing
	if (iter != m_pointer_map.end())
	{
		// removing map data for serial
		m_pointer_map.erase(iter);
	}
}


/// Registering the objects
void SerializationManager::RegisterSerializable(Serializable* pSerializable) {
	// if map does not have anything
	//assert(m_serial_map.find(pSerializable->GetObjectID()) == m_serial_map.end());

	// placing object's pointer and id in map
	m_serial_map.emplace(pSerializable->GetObjectID(), pSerializable);
}

// Finds object and removes it from map
void SerializationManager::RemoveSerializable(Serializable * pSerializable) {
	auto iter = m_serial_map.find(pSerializable->GetObjectID());

	// testing
	if (iter != m_serial_map.end())
	{
		// removing map data for serial
		m_serial_map.erase(iter);
	}
}


/// Saves reference to New() with associated classIndex
void SerializationManager::classNewRegister(unsigned int classIndex, newSerial newFunctPt){
	// saving reference to New() with associate class Index (unsigned int)
	m_classNewReference.emplace(classIndex, newFunctPt);
}

// Returns the pointer to the object
Serializable* SerializationManager::GetSerializable(unsigned int serializableId) const {
	Serializable* pSerializable{ nullptr };
	auto iter = m_serial_map.find(serializableId);
	if (iter != m_serial_map.end())
	{
		pSerializable = iter->second;
	}
	return pSerializable;
}

// rewrites data on file
void SerializationManager::ClearSave() {
	std::fstream file{ m_filename, std::ios::binary | std::ios::out };
	bool fileBool = false;
	file.write((char*)& fileBool, sizeof(fileBool));
}

/// saving data for all objects (wave one)
void SerializationManager::Save() {
	std::ofstream file{ m_filename, std::ios::binary | std::ios::out };
	bool fileValue = true;
	file.write((char*)& fileValue, sizeof(fileValue));

	unsigned int objID;
	Serializable* tempPtr;
	double ptID;
    for (auto& serializable : m_pointer_map) {
        // class ID is placed first before serialization. this allows for the deserialization
        // easly find the right object. ID is IDcontainer type
        tempPtr = *serializable.second->m_pt;
        if (tempPtr != nullptr) {
            objID = tempPtr->GetObjectID();
        }
        else{
            objID = 0;
        }
        file.write((char *) &objID, sizeof(objID));

        /// Serializing Obj ID Binary
        ptID = serializable.first;
        file.write((char*)&ptID, sizeof(ptID));
    }

    // Stating to stop
    objID = -1;
    ptID = -1;
    file.write((char*)&objID, sizeof(objID));
    file.write((char*)&ptID, sizeof(ptID));


    for (auto& serializable : m_serial_map) {
		// class ID is placed first before serialization. this allows for the deserialization
		// easly find the right object. ID is IDcontainer type
		Serializable* pSerializable = serializable.second;

		/// Serializing Obj ID
		unsigned int temp = serializable.second->GetObjectID();
		file.write((char*)& temp, sizeof(temp));

		// saving object
		pSerializable->OnSave(file);
	}
}

/// loading data from all object (wave two)
bool SerializationManager::Load() {
	std::ifstream file{ m_filename, std::ios::binary | std::ios::in };
	m_pointer_map.clear();

	bool found = file.is_open();
	if (found) {
		bool isValid, theEnd = false;
		file.read((char*)& isValid, sizeof(isValid)); 
		if (isValid) {
			// loading m_load_pointer
		    int objID;
		    double ptID;
		    do{
                file.read((char*)&objID, sizeof(objID));
                file.read((char*)&ptID, sizeof(ptID));
				if (objID != -1 && ptID != -1)
					m_load_pointer_map.emplace(ptID, objID);
				else
					break;
		    }while(true/*objID != INT32_MAX && ptID != (DBL_MAX-1)*/);
            printf("Done with Pointer Map\n");
			
			// temp Serial ID
			unsigned int serializableId;
			unsigned int classIndex;
			while (!file.eof()) {
				/// Deserializing ObjID and finding it in the map
				file.read((char*)& serializableId, sizeof(serializableId));
				if (file.eof())
					break;
				auto iter = m_serial_map.find(serializableId);

				/// Deserializing the objects type
				file.read((char*)& classIndex, sizeof(classIndex));

				/// Determining if it a new dynamic object
				if (iter != m_serial_map.end())	{
					// Running function developer created
					iter->second->OnLoad(file);
				}
				else {
					// using object type to get new instance of object
					auto iter2 = m_classNewReference.find(classIndex);
					Serializable * temp = iter2->second(serializableId);
					temp->OnLoad(file);
				}
			}
			/// Repointing pointers that need to be repointed (wave 3)
			for (auto& point : m_pointer_map) {
				point.second->Reconnect();
			}
		}
		else {
			found = false;
		}
	}
	return found;
}

/// Reconnects objects based on pointer id
Serializable* SerializationManager::Reconnect(double ptID) {
	// Pointer_ID -> object ID to point to
	auto iter = m_load_pointer_map.find(ptID);
    int objID = iter->second;
	
	// objID means no object was assigned at save
	if (objID == 0)
		return nullptr;
	else
		return m_serial_map[objID];
}
