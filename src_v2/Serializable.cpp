//
// Created by tomlaverghettamsve on 10/3/19.
//

#include "Serializable.h"
#include "SerializationManager.h"
// Initialize static member of class Serializable
unsigned int Serializable::m_id = 1;
unsigned int Serializable::m_globalClassIndex = 0;

unsigned int Serializable::PointerObj::m_numPtr = 1;

/// removing serializable object from manager
Serializable::~Serializable(){
    // Getting Singleton
    SerializationManager* pSerializationManager = SerializationManager::GetInstance();

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
    m_objID=m_id;

    // Registers serializable object
    SerializationManager::GetInstance()->RegisterSerializable(this);

    // static ID that iterates every new object
    m_id++;
}

Serializable::Serializable(unsigned int objId){
    // SerialID is unique ID
    m_objID=objId;

    // Registers serializable object
    SerializationManager::GetInstance()->RegisterSerializable(this);


    // incase the global id is smaller than the loaded object id
    if(objId >= m_id)
        m_id = ++objId;
}

//----------------------POINTEROBJ--------------------------

Serializable::PointerObj::PointerObj(Serializable **pointer, Serializable * currentObj){
    // pointer reference
    m_pt = pointer;
    
    // creating object ID
    ///DBL_MIN
    m_PtID = currentObj->GetObjectID() + 0.0001*m_numPtr;

    // number of pointer objects created for object
    m_numPtr++;

    // register pointer with pointer_map
    SerializationManager::GetInstance()->RegisterPointer(m_PtID,this);
}

Serializable::PointerObj::~PointerObj(){
    // Getting Singleton
    SerializationManager* pSerializationManager = SerializationManager::GetInstance();

    // Testing if not null
    if (pSerializationManager)
    {
        // registoring with serial mamager
        pSerializationManager->RemovePointer(m_PtID);
    }

    m_pt = nullptr;
}

// calls serialization manager's reconnect function which as access
// to pointer_map
void Serializable::PointerObj::Reconnect() {
	*m_pt = SerializationManager::GetInstance()->Reconnect(m_PtID);
}

// Used onLoad
void Serializable::PointerObj::Reregister() {
    // Registers pointer ID and itself
    SerializationManager::GetInstance()->RegisterPointer(m_PtID,this);
}
