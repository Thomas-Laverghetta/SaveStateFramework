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
// Object's charaterstics
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

    // the object's charateristics (Static or Dynamic)
    ObjectChar m_char {Static};
public:
    // constructor and destructor
    explicit Serializable();
    explicit Serializable(ObjectChar t); // for dynamic variables
    ~Serializable();

    // Get the ID for object
    unsigned int GetObjectID() const { return m_objID; }

    // setting object ID
    void SetObjectID(const int& objID){
        m_objID = objID;
    }

	// return number of objects declared in simulation
	unsigned int NumberOfObjects() const { return m_id; }

    // get object char
    ObjectChar GetObjectChar(){
        return m_char;
    }

    // Setting the char variable
    void SetObjectChar(const ObjectChar& t){
        m_char = t;
    }

    // pure virtual functions for serialization and deserialization
    virtual void OnSave(std::ofstream& file) = 0;
    virtual void OnLoad(std::ifstream& file) = 0;

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
        explicit PointerObj(Serializable**, Serializable*);

        // removing object from pointer_map
        ~PointerObj();

        // Setting the Pointer ID
        void setPtID(double ID) { m_PtID = ID;}

        // Reregisters pointer with pointer_map
        void Reregister();

        // reconnecting pointer with corrisponding data
		void Reconnect();

        // determines if a object has been saved
        bool SavedQuestion();

        // determines if a object has been loaded
        bool LoadedQuestion();

        // Determining if the dynamic object is for ptr
        bool ObjectIdEqualPtrId(int& objectID);
    };
};

#endif //TESTER_SERIALIZABLE_H