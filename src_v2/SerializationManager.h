//
// Created by tomlaverghettamsve on 10/3/19.
//

#ifndef TESTER_SERIALIZATIONMANAGER_H
#define TESTER_SERIALIZATIONMANAGER_H

#include <cassert>     /* assert */
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <unordered_map>
#include "Serializable.h"

/// Created Sources

/* Summary
    SerializationManager is a Singleton class responsible  for tracking
    every object instantiated and needs to be serialized.
*/
class SerializationManager
{
private:
    // Singleton
    SerializationManager()= default;
    static SerializationManager * _instance;

    /// The file to save data to (can be anytype)
    char * m_filename{(char*) "Save.txt"}; // default file name and type
    
    /// Pointer and Serialization Variables
    // holds pointer ID and corrisponding object ID to point to
    std::unordered_map<double, Serializable::PointerObj*> m_pointer_map;

    // used to store pointers of Serializable objects and unique ID
    std::unordered_map<unsigned int, Serializable*> m_serial_map;

    // load
    std::unordered_map<double, unsigned int> m_load_pointer_map;

    // saves reference to all class New() (newSerial)
    std::unordered_map<unsigned int,newSerial> m_classNewReference;
public:
    // Singleton get instance function
    static SerializationManager * GetInstance(){
        if(_instance == nullptr)
            _instance = new SerializationManager();
        return _instance;
    }
    
    /// File to save states to
	void SetupFile(char* fileName);

    /// objects will register pointers to serialize and their objects their pointing to
	void RegisterPointer(double Pt_ID, Serializable::PointerObj* ptr);

    // Finds pointer in point_map and removes it
	void RemovePointer(double ptrID);
 
    /// Registering the objects
	void RegisterSerializable(Serializable* pSerializable);

    // Finds object and removes it from map
	void RemoveSerializable(Serializable* pSerializable);

    // Returns the pointer to the object
	Serializable* GetSerializable(unsigned int serializableId) const;

    // rewrites data on file
	void ClearSave();

    /// saving data for all objects (wave one)
	void Save();

    /// loading data from all object (wave two)
	bool Load();

    /// Reconnect pointer to object based on pointer ID
	Serializable* Reconnect(double pt);

    // register New() based on class ID
    void classNewRegister(unsigned int classIndex, newSerial newFunctPt);
};
#endif //TESTER_SERIALIZATIONMANAGER_H
