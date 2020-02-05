//
// Created by tomlaverghettamsve on 10/3/19.
//

#include "Serializable.h"
#include "SerializationManager.h"
// Initialize static member of class Serializable
unsigned int Serializable::m_id = 1;
int Serializable::m_Dyn_id = -1;

template <class T>
unsigned int Serializable::PointerObj<T>::m_numPtr = 0;

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

template <class T>
Serializable::PointerObj<T>& Serializable::PointerObj<T>::operator=(T* s) {
	if (m_pt == nullptr) {
		// Registering with pointer map
		SerializationManager::GetInstance()->RegisterPointer(m_PtID, ((Serializable*)s)->GetObjectID(), (Serializable::PointerObj<Serializable>*)this);
	}
	else {
		// remove the previous pointer data
		SerializationManager::GetInstance()->RemovePointer(m_PtID);
		SerializationManager::GetInstance()->RegisterPointer(m_PtID, ((Serializable*)s)->GetObjectID(), (Serializable::PointerObj<Serializable>*)this);
	}

	// setting
	m_pt = s;


	return *this;
}

template <class T>
void Serializable::PointerObj<T>::Reconnect() {
	m_pt = SerializationManager::GetInstance()->Reconnect(m_PtID);
}

// void Serializable::CloneRegistration() {
//     // Register Clone Function
//     SerializationManager::GetSingleton().AddClassClone(this, ClassID());
// }
