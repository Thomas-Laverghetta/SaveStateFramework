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
		PointerObj serial_next{next};

		// Class ID
		//unsigned int ClassID() override { static unsigned int k = counter::GetSingleton().GetCounter(); return k; }
		/**
		 * Default Constructor
		 */
		Node();

		/**
		 * Clone Constructor
		 */
		
		// Serializable* clone() { return new Node(Dynamic); }

		/**
		 * Historical Data Constructor
		 */
		explicit Node(Student s);

		void OnSave(std::ofstream& file) {
			data.OnSave(file);
			file << serial_next.m_PtID << std::endl;
		}

		void OnLoad(std::ifstream& file)
		{
			data.OnLoad(file);
			file >> serial_next.m_PtID;
		}
	};
	Node * head;
    PointerObj serial_head{ head};
public:
	Node * tail;
    PointerObj serial_tail{ tail};

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
//        file.write((char *)&capacity, sizeof(capacity));
//        file.write((char *)&occupied, sizeof(occupied));
        file << capacity << endl << occupied << endl << endl;
    }
    void OnLoad(std::ifstream& file){
//        while (it != nullptr){
//            file.read((char *)&(*it),sizeof(*it));
//            it->OnLoad(file);
//            it = it->next;
//        }
//        file.read((char *)&capacity, sizeof(capacity));
//        file.read((char *)&occupied, sizeof(occupied));
        file >> capacity >> occupied;
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
