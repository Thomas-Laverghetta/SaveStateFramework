#include "SerializationManager.h"

SerializationManager* SerializationManager::_instance = nullptr;


/// File to save states to
void SerializationManager::SetupFile(char* fileName) {
	m_filename = fileName;
}

/// objects will register pointers to serialize and their objects their pointing to
void SerializationManager::RegisterPointer(double Pt_ID, unsigned int Obj_ID, Serializable::PointerObj<Serializable>* ptr) {
	m_pointer_map.emplace(Pt_ID, Obj_ID);
	m_reconnect.push_back(ptr);
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
	assert(m_serial_map.find(pSerializable->GetObjectID()) == m_serial_map.end());

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
	//std::ofstream file{m_filename};
	bool fileValue = true;
	//file << fileValue << std::endl << std::endl;
	file.write((char*)& fileValue, sizeof(fileValue));
	ObjectChar t = Static;

	for (auto& serializable : m_serial_map) {
		file.write((char*)& t, sizeof(t));

		// class ID is placed first before serialization. this allows for the deserialization
		// easly find the right object. ID is IDcontainer type
		Serializable* pSerializable = serializable.second;

		/// Serializing Obj ID Binary
		unsigned int temp = serializable.second->GetObjectID();
		file.write((char*)& temp, sizeof(temp));

		//file << temp << std::endl;
		/// Serializing Obj
		pSerializable->OnSave(file);
	}
}

/// loading data from all object (wave two)
bool SerializationManager::Load() {
	std::ifstream file{ m_filename, std::ios::binary | std::ios::in };
	////std::ifstream file{m_filename};
	bool found = file.is_open();
	if (found) {
		bool isValid;
		file.read((char*)& isValid, sizeof(isValid));
		///file >> isValid;
		if (isValid) {

			// temp Serial ID
			unsigned int serializableId;

			// temp for finding the type of class
			ObjectChar type;

			while (!file.eof()) {
				file.read((char*)& type, sizeof(type));
				if (type != Static) {
					printf("ERROR at Load!! \a\n");
					break;
				}

				/// Deserializing to get Obj ID
				file.read((char*)& serializableId, sizeof(serializableId));
				//file >> serializableId;

				// Map from ID
				auto iter = m_serial_map.find(serializableId);

				/// Determining if it a new dynamic object
				if (iter != m_serial_map.end())
				{
					// Running function developer created
					iter->second->OnLoad(file);
				}
			}
			/// Repointing pointers that need to be repointed (wave 3)
			for (auto& serializable : m_reconnect) {
				serializable->Reconnect();
			}
		}
		else {
			found = false;
		}
	}
	return found;
}

/// Good reference for Repointing pointers
// given pointer
Serializable* SerializationManager::Reconnect(double pt) {
	// Pointer_ID -> object ID to point to
	auto iter = m_pointer_map.find(pt);

	// the object pointer (*serializable)
	return m_serial_map[iter->second];
}