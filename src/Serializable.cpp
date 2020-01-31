//
// Created by tomlaverghettamsve on 10/3/19.
//

#include "Serializable.h"
#include "SerializationManager.h"
// Initialize static member of class Serializable
unsigned int Serializable::m_id = 1;

/// removing serializable object from manager
Serializable::~Serializable(){
    // Getting Singleton
    SerializationManager* pSerializationManager = SerializationManager::GetSingletonPtr();

    // Testing if not null
    if (pSerializationManager)
    {
        // registoring with serial mamager
        pSerializationManager->RemoveSerializable(this);
    }
}

/// registering object along with assigning unique ID number
Serializable::Serializable(){
    // SerialID is unique ID
    objID=m_id;

    // Registers serializable object
    SerializationManager::GetSingleton().RegisterSerializable(this);

    // static ID that iterates every new object
    m_id++;
}

void Serializable::CloneRegistration() {
    // Register Clone Function
    SerializationManager::GetSingleton().AddClassClone(this, ClassID());
}
