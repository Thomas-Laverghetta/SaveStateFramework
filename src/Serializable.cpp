//
// Created by tomlaverghettamsve on 10/3/19.
//

#include "Serializable.h"
#include "SerializationManager.h"
// Initialize static member of class Serializable
unsigned int Serializable::m_id = 1;
int Serializable::m_Dyn_id = -1;

unsigned int Serializable::PointerObj::m_numPtr = 0;

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

// Dynamic objects (usually)
Serializable::Serializable(ObjectChar t){
    m_char = t;
	if (m_char == Dynamic)
		m_objID = m_Dyn_id--;
	else
		m_objID = m_id++;
}

//----------------------POINTEROBJ--------------------------

Serializable::PointerObj::PointerObj(Serializable **pt, Serializable * currentNode){
    // pointer reference
    m_pt = pt;
    
    // creating object ID
    m_PtID = currentNode->GetObjectID() + DBL_MIN*m_numPtr;

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
	m_pt = SerializationManager::GetInstance()->Reconnect(m_PtID);
}

// Used onLoad
void Serializable::PointerObj::Reregister() {
    // Registers pointer ID and itself
    SerializationManager::GetInstance()->RegisterPointer(m_PtID,this);
}

bool Serializable::PointerObj::SavedQuestion(){
    SerializationManager::GetInstance()->SavedQuestion(m_PtID);
}

bool Serializable::PointerObj::LoadedQuestion(){
    SerializationManager::GetInstance()->LoadedQuestion(m_PtID);
}

// Determining if the dynamic object is for ptr
bool Serializable::PointerObj::ObjectIdEqualPtrId(int& objectID){
    SerializationManager::GetInstance()->ObjectIdEqualPtrId(objectID);
}

