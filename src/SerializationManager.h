//
// Created by tomlaverghettamsve on 10/3/19.
//

#ifndef TESTER_SERIALIZATIONMANAGER_H
#define TESTER_SERIALIZATIONMANAGER_H

#include <map>
#include <cassert>     /* assert */
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

/// Created Sources
#include "Serializable.h"

/* Summary
    SerializationManager is a Singleton class responsible  for tracking
    every object instantiated and needs to be serialized.
*/

class SerializationManager
{
private:
    // Singleton
    SerializationManager();
    static SerializationManager * _instance;

    /// The file to save data to (can be anytype)
    char * m_filename{(char*) "Save.txt"}; // default file name and type
    
    /// Pointer and Serialization Variables
    // holds pointer ID and corrisponding object ID to point to
    std::map<double, unsigned int> m_pointer_map;

    // used to store pointers of Serializable objects and unique ID
    std::map<unsigned int, Serializable*> m_serial_map;

    // Reference to PointerObj
    std::vector<Serializable::PointerObj<Serializable>*> m_reconnect;
public:
    // Singleton get instance function
    static SerializationManager * GetInstance(){
        if(_instance == nullptr)
            _instance = new SerializationManager;
        return _instance;
    }
    
    /// File to save states to
    void SetupFile(char * fileName){
        m_filename = fileName;
    }

    /// objects will register pointers to serialize and their objects their pointing to
    void RegisterPointer(double Pt_ID, unsigned int Obj_ID, Serializable::PointerObj<Serializable> * ptr){
        m_pointer_map.emplace(Pt_ID,Obj_ID);
        m_reconnect.push_back(ptr);
    }

    // Finds pointer in point_map and removes it
    void RemovePointer(double ptrID){
        auto iter = m_pointer_map.find(ptrID);

        // testing
        if (iter != m_pointer_map.end())
        {
            // removing map data for serial
            m_pointer_map.erase(iter);
        }
    }


    /// Registering the objects
    void RegisterSerializable(Serializable* pSerializable) {
        // if map does not have anything
        assert(m_serial_map.find(pSerializable->GetObjectID()) == m_serial_map.end());

        // placing object's pointer and id in map
        m_serial_map.emplace(pSerializable->GetObjectID(), pSerializable);
    }

    // Finds object and removes it from map
    void RemoveSerializable(Serializable* pSerializable){
        auto iter = m_serial_map.find(pSerializable->GetObjectID());

        // testing
        if (iter != m_serial_map.end())
        {
            // removing map data for serial
            m_serial_map.erase(iter);
        }
    }

    // Returns the pointer to the object
    Serializable* GetSerializable(unsigned int serializableId) const{
        Serializable* pSerializable{ nullptr };
        auto iter = m_serial_map.find(serializableId);
        if (iter != m_serial_map.end())
        {
            pSerializable = iter->second;
        }
        return pSerializable;
    }

    // rewrites data on file
    void ClearSave(){
        std::fstream file{ m_filename, std::ios::binary | std::ios::out};
        bool fileBool = false;
        file.write((char *)&fileBool, sizeof(fileBool));
    }

    /// saving data for all objects (wave one)
    void Save(){
        std::ofstream file{ m_filename, std::ios::binary | std::ios::out};
        //std::ofstream file{m_filename};
        bool fileValue = true;
        //file << fileValue << std::endl << std::endl;
        file.write((char *)&fileValue, sizeof(fileValue));
        ObjectChar t = Static;

        for (auto& serializable : m_serial_map){
            file.write((char*)&t, sizeof(t));

            // class ID is placed first before serialization. this allows for the deserialization
            // easly find the right object. ID is IDcontainer type
            Serializable* pSerializable = serializable.second;
            
            /// Serializing Obj ID Binary
            unsigned int temp = serializable.second->GetObjectID();
            file.write((char*)&temp, sizeof(temp));
            
            //file << temp << std::endl;
            /// Serializing Obj
            pSerializable->OnSave(file);
        }
    }

    /// loading data from all object (wave two)
    bool Load(){
        std::ifstream file{ m_filename, std::ios::binary | std::ios::in };
        ////std::ifstream file{m_filename};
        bool found = file.is_open();
        if (found) {
            bool isValid;
            file.read((char *)&isValid, sizeof(isValid));
            ///file >> isValid;
            if (isValid) {

                // temp Serial ID
                unsigned int serializableId;

                // temp for finding the type of class
                ObjectChar type;

                while (!file.eof()) {
                    file.read((char*)&type, sizeof(type));
                    if (type != Static){
                        printf("ERROR at Load!! \a\n");
                        break;
                    }

                    /// Deserializing to get Obj ID
                    file.read((char*)&serializableId, sizeof(serializableId));
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
                for (auto& serializable : m_reconnect){
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
    Serializable * Reconnect(double pt){
        // Pointer_ID -> object ID to point to
        auto iter = m_pointer_map.find(pt);

        // the object pointer (*serializable)
        return m_serial_map[iter->second];
    }

};

SerializationManager * SerializationManager::_instance = nullptr;

#endif //TESTER_SERIALIZATIONMANAGER_H
