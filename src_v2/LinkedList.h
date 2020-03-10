//
// Created by tomlaverghettamsve on 11/14/19.
//

#ifndef TESTER_LINKEDLIST_H
#define TESTER_LINKEDLIST_H
#include "Student.h"
#include "Serializable.h"
#include "SerializationManager.h"

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
		PointerObj serial_next{(Serializable**)&next, this};

        // constructor
		Node();
		explicit Node(Student s);
        Node(unsigned int objId);

        // save call
		void OnSave(std::ofstream& file) {
            file.write((char*)&m_classId, sizeof(m_classId));
            printf("class ID %i\n", m_classId);
			data.OnSave(file);
		}

		void OnLoad(std::ifstream& file)
		{
			data.OnLoad(file);
			serial_next.Reregister();
        }

        /// Required functions
        static Serializable * New(unsigned int objId);
        static void Initialization(); 
        static unsigned int m_classId;
	};
	Node * head;
    PointerObj serial_head{(Serializable **)&head, this};
    static unsigned int m_classId;
public:
	Node * tail;
    PointerObj serial_tail{ (Serializable**)&tail, this};

    int capacity;
    int occupied;

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

    LinkedList(const unsigned int& ObjId);
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
        file.write((char*)&m_classId, sizeof(m_classId));
        printf("class ID %i\n", m_classId);
        file.write((char *)&capacity, sizeof(capacity));
        file.write((char *)&occupied, sizeof(occupied));
    }
    void OnLoad(std::ifstream& file){
        file.read((char *)&capacity, sizeof(capacity));
        file.read((char *)&occupied, sizeof(occupied));
        serial_head.Reregister();
        serial_tail.Reregister();
    }

    /// Required functions
    static Serializable* New(unsigned int objId);
    static void Initialization();
};

/**
 * Overload output operator
 */
inline ostream& operator<<(ostream& outs, const LinkedList& prt) {
    prt.display(outs);
    return outs;
}

#endif // !LINKED_LIST_H
