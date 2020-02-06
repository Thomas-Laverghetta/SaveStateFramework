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
	static int m_Dyn_id;

    // Used for current object ID
    unsigned int m_objID {0};

    ObjectChar m_char {Static};
public:
    explicit Serializable();
    explicit Serializable(ObjectChar t);
    ~Serializable();

    // Get the ID for object
    unsigned int GetObjectID() const { return m_objID; }

    void SetObjectID(const int& objID){
        m_objID = objID;
    }
	// return number of objects declared in simulation
	unsigned int NumberOfObjects() const { return m_id; }

    // get object char
    ObjectChar GetObjectChar(){
        return m_char;
    }
    void SetObjectChar(const ObjectChar& t){
        m_char = t;
    }

    // pure virtual functions for serialization and deserialization
    virtual void OnSave(std::ofstream& file) = 0;
    virtual void OnLoad(std::ifstream& file) = 0;

	// Get clone function
    //virtual Serializable* clone() = 0;

    struct PointerObj{
        /// pointer pointing to other objects
        Serializable** m_pt { nullptr };

        /// Pointer Object ID
        double m_PtID;

        /// Number of Pointers used on the object
        static unsigned int m_numPtr;

        /// Registering with parent class
        explicit PointerObj(Serializable**, Serializable*);
        /// Registering an object
		//PointerObj& operator=(Serializable* s);

/*
        PointerObj&operator=(const PointerObj& p){
            m_PtID = p.m_PtID;
            m_pt = p.m_pt;
            return *this;
        }
*/

        void setPtID(double ID) { m_PtID = ID;}

        void Reregister();

		void Reconnect();
    };
};

#endif //TESTER_SERIALIZABLE_H