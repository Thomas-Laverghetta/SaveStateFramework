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
/// Gives the object the ability to save
class Serializable
{
private:
    // Used to save the current ID number, changes every instance
    static unsigned int m_id;
	// Used for current object ID
    unsigned int m_objID {0};

    // to save current class index
    static unsigned int m_globalClassIndex;

public:
    // constructor and destructor
    explicit Serializable();
    Serializable(unsigned int objId);
    ~Serializable();

    // Get the ID for object
    unsigned int GetObjectID() const { return m_objID; }

	// return number of objects declared in simulation
	unsigned int NumberOfObjects() const { return m_id; }

    // update index
    static unsigned int GlobalClassIndex(){ return m_globalClassIndex++;}
    
    // pure virtual functions for serialization and deserialization
    virtual void OnSave(std::ofstream& file) = 0;
    virtual void OnLoad(std::ifstream& file) = 0;
    
    /* inheriting classes must:
    static Serializable * New(unsigned int objId);
    static void Initialization(); <-registers class id and New() with serialization manager
    static unsigned int classIndex(); <-calls GlobalClassIndex to get current index only at initialization
    */

    /*
        I will save reference to object that pointer is pointing to
        (m_pt) and save the objectID of the current obj it is corrilated
        with. 
    */
    class PointerObj{
    public:
        // pointer reference to the object that pointer is pointing at
        Serializable** m_pt { nullptr };

        // Pointer ID used for pointer_map
        double m_PtID;

        // Number of Pointers used on the object
        static unsigned int m_numPtr;

        // Registering pointer with Serialization manager so it can be saved
        explicit PointerObj(Serializable** pointer, Serializable* currentObj);

        // removing object from pointer_map
        ~PointerObj();

        // Setting the Pointer ID
        void setPtID(double ID) { m_PtID = ID;}

        // Reregisters pointer with pointer_map
        void Reregister();

        // reconnecting pointer with corrisponding data
		void Reconnect();
    };
};

typedef Serializable* (*newSerial)(unsigned int);

#endif //TESTER_SERIALIZABLE_H