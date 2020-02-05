//
// Created by tomlaverghettamsve on 10/3/19.
//

#ifndef TESTER_SERIALIZABLE_H
#define TESTER_SERIALIZABLE_H

#include <fstream>
#include <vector>
#include <unordered_map>
#include <float.h>

/* Summary:
    Will be inherited by every object that needs to be serialized.
    This class will communicate between serial manager and objects
    that need to be serialized.
    Every object will have its own unique ID that serializable will
    use to reference the class.
*/
enum ObjectChar {Static, Dynamic};
/// Gives the object the ability to save
class Serializable
{
private:
    // Used to save the current ID number, changes every instance
    static unsigned int m_id;

    // Used for current object ID
    unsigned int m_objID;

    ObjectChar m_char {Static};
public:
    explicit Serializable();
    explicit Serializable(ObjectChar t);
    ~Serializable();

    // Get the ID for object
    unsigned int GetObjectID() const { return m_objID; }

	// return number of objects declared in simulation
	unsigned int NumberOfObjects() const { return m_id; }

    // get object char
    ObjectChar GetObjectChar(){
        return m_char;
    }

    // pure virtual functions for serialization and deserialization
    virtual void OnSave(std::ofstream& file) = 0;
    virtual void OnLoad(std::ifstream& file) = 0;

	// Get clone function
    //virtual Serializable* clone() = 0;
    
    template <class T>
    class PointerObj{
        public:
        /// pointer pointing to other objects
        T* m_pt;

        /// Pointer Object ID
        double m_PtID;

        /// Number of Pointers used on the object
        static unsigned int m_numPtr;

        /// Registering with parent class
        PointerObj(){
            // Initializing variables
            m_pt = nullptr;
            m_PtID = m_objID + DBL_MIN*m_numPtr;
            m_numPtr++;
        }

        /// Registering an object
        PointerObj& operator=(T * s){
            if (m_pt = nullptr){
                // Registering with pointer map
                SerializationManager::GetInstance()->RegisterPointer(m_PtID, (Serializable*)s->GetObjectID(), this);
            }
            else {
                // remove the previous pointer data
                SerializationManager::GetInstance()->RemovePointer(m_PtID);
                SerializationManager::GetInstance()->RegisterPointer(m_PtID, (Serializable*)s->GetObjectID(), this);
            }
            
            // setting
            m_pt = s;
    
            
            return *this;
        }

        PointerObj&operator=(const PointerObj& p){
            m_PtID = p.m_PtID;
            m_pt = p.m_pt;
            return *this;
        }

        void setPtID(double ID) { m_PtID = ID;}

        void Reconnect(){
            m_pt = SerializationManager::GetInstance()->Reconnect(m_PtID);
        }
    };
};

template <class T>
unsigned int Serializable::PointerObj<T>::m_numPtr = 0;
#endif //TESTER_SERIALIZABLE_H
