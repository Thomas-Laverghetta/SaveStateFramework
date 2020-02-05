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


/*Serializable::PointerObj& Serializable::PointerObj::operator=(Serializable* s) {
	if (m_pt == nullptr) {
		// Registering with pointer map
		SerializationManager::GetInstance()->RegisterPointer(m_PtID, ((Serializable*)s)->GetObjectID(), this);
	}
	else {
		// remove the previous pointer data
		SerializationManager::GetInstance()->RemovePointer(m_PtID);
		SerializationManager::GetInstance()->RegisterPointer(m_PtID, ((Serializable*)s)->GetObjectID(), this);
	}

	// setting
	m_pt = s;


	return *this;
}*/

void Serializable::PointerObj::Reconnect() {
	m_pt = SerializationManager::GetInstance()->Reconnect(m_PtID);
}

Serializable::PointerObj::PointerObj(Serializable *pt){
    // Initializing variables
    m_pt = pt;
    m_PtID = pt->m_objID + DBL_MIN*m_numPtr;
    m_numPtr++;
    SerializationManager::GetInstance()->RegisterPointer(m_PtID,this);
}

// void Serializable::CloneRegistration() {
//     // Register Clone Function
//     SerializationManager::GetSingleton().AddClassClone(this, ClassID());
// }
