//
// Created by tomlaverghettamsve on 11/14/19.
//

#ifndef TESTER_LINKEDLIST_H
#define TESTER_LINKEDLIST_H
#include "Student.h"
#include "Serializable.h"

// Gives each class a unique ID
	/// Used for cloning
//class counter : public Singleton<counter> {
//private:
//	unsigned int count;
//public:
//	counter() { count = 0; }
//	unsigned int GetCounter() {
//		return count++;
//	}
//};

/* Linked List comprise of a list of objects
 * that have data in them and pointers pointing
 * to another object
 */
class LinkedList: public Serializable {
private:
	class Node : public Serializable {
	public:
		// Data
		Student data;
		Node * next;

        // serialize node
		PointerObj serial_next{reinterpret_cast<Serializable **>(&next), this};

        // constructor
		Node();
		explicit Node(Student s);

        // save call
		void OnSave(std::ofstream& file) {
		    ObjectChar oc = GetObjectChar();
            file.write((char *)&oc, sizeof(oc));
            int objID = GetObjectID();
            file.write((char *)&objID, sizeof(objID));
			data.OnSave(file);

            if (next != nullptr && next->GetObjectChar() == Dynamic){
                // determining the object has been saved
                if(!serial_next.SavedQuestion()){
                    next->OnSave(file);
                }
            }
		}

		void OnLoad(std::ifstream& file)
		{
			data.OnLoad(file);
			
			serial_next.Reregister();
            
            // determining if an dynamic object needed to be deserialied
            ObjectChar type;
            file.read((char*)& type, sizeof(type));
            if (type == Dynamic){
                // object id from the next object
                int objectID;
                file.read((char*)&objectID, sizeof(objectID));
                if(serial_next.ObjectIdEqualPtrId(objectID)){
                    // dynamic object creation
                    next = new Node();
                    next->OnLoad(file);
                }
            }
            else{
                next = nullptr;
            }
        }
	};
	Node * head;
    PointerObj serial_head{reinterpret_cast<Serializable **>(&head), this};;
public:
	Node * tail;
    PointerObj serial_tail{reinterpret_cast<Serializable **>(&tail), this};;

    int capacity;
    int occupied;

	// ClassID
	//unsigned int ClassID() override { static unsigned int k = counter::GetSingleton().GetCounter(); return k; }

	/**
	* Clone Shit
	*/
	//LinkedList(ObjectChar dynamic) : Serializable{ dynamic } {
	//	this->head.m_pt = nullptr;
	//	this->tail.m_pt = nullptr;
	//	this->capacity = 10;
	//	this->occupied = 0;
 //       //CloneRegistration();
	//}
	//Serializable* clone() { return new LinkedList(Dynamic); }

    /**
     * Default Constructor
     */
    LinkedList();

    /**
     * Constructor with defined capacity
     */
    LinkedList(int n);

    /**
     * Copy Constructor
     */
    LinkedList(const LinkedList& src);

    /**
     * Destructor
     */
    ~LinkedList();

    /**
     * Is the Linked List full?
     */
    bool isFull() const;

    /**
     * Add Student to the list
     */
    void addStudent(Student student);

    /**
     * Outputs linked list
     */
    void display(ostream& outs) const;

    /**
     * Assignment Operator
     */
    LinkedList& operator=(LinkedList rhs);

    /**
     * Swap function
     */
    friend void swap(LinkedList& lhs, LinkedList& rhs);

    void OnSave(std::ofstream& file){

//        while (it != nullptr){
//            it->OnSave(file);
//            file.write((char *)&(*it), sizeof(*it));
//            it = it->next;
//        }
        int objID = GetObjectID();
        ObjectChar t = GetObjectChar();

        file.write((char*)&t, sizeof(t));
        file.write((char*)&objID, sizeof(objID));

        file.write((char *)&capacity, sizeof(capacity));
        file.write((char *)&occupied, sizeof(occupied));

        if (head != nullptr && head->GetObjectChar() == Dynamic){
            // determining the object has been saved
            if(!serial_head.SavedQuestion()){
                    head->OnSave(file);
            }
        }
        if (tail != nullptr && tail->GetObjectChar() == Dynamic){
            // determining the object has been saved
            if(!serial_tail.SavedQuestion()){
                    tail->OnSave(file);
            }
        }
    }
    void OnLoad(std::ifstream& file){
//        while (it != nullptr){
//            file.read((char *)&(*it),sizeof(*it));
//            it->OnLoad(file);
//            it = it->next;
//        }
        file.read((char *)&capacity, sizeof(capacity));
        file.read((char *)&occupied, sizeof(occupied));
        serial_head.Reregister();
        serial_tail.Reregister();

        // determining if an dynamic object needed to be deserialied
        ObjectChar type;
        file.read((char*)& type, sizeof(type));
        if (type == Dynamic){
            // object id from the next object
            int objectID;
            file.read((char*)&objectID, sizeof(objectID));
            if(serial_head.ObjectIdEqualPtrId(objectID)){
                // dynamic object creation
                head = new Node();
                head->OnLoad(file);
            }
            if(serial_tail.ObjectIdEqualPtrId(objectID)){
                // dynamic object creation
                tail = new Node();
                tail->OnLoad(file);
            }
        }
        else{
            head = nullptr;
            tail = nullptr;
        }
    }
};

/**
 * Overload output operator
 */
inline ostream& operator<<(ostream& outs, const LinkedList& prt) {
    prt.display(outs);
    return outs;
}

#endif // !LINKED_LIST_H
