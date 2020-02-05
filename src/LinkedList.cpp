//
// Created by tomlaverghettamsve on 11/14/19.
//

#include "LinkedList.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
LinkedList::Node::Node() {
    data = Student();
    this->next.m_pt = nullptr;
    ///CloneRegistration();
}

//------------------------------------------------------------------------------
LinkedList::Node::Node(Student s) {
    data = s;
    this->next.m_pt = nullptr;
    //CloneRegistration();
}

//------------------------------------------------------------------------------
LinkedList::LinkedList() {
    this->head.m_pt = nullptr;
    this->tail.m_pt = nullptr;
    this->capacity = 10;
    this->occupied = 0;
    //CloneRegistration();
}

//------------------------------------------------------------------------------
LinkedList::LinkedList(int n) {
    this->head.m_pt = nullptr;
    this->tail.m_pt = nullptr;
    this->capacity = n;
    this->occupied = 0;
    //CloneRegistration();
}

//------------------------------------------------------------------------------
LinkedList::LinkedList(const LinkedList& src) {
    this->head.m_pt = nullptr;
    this->tail.m_pt = nullptr;
    this->capacity = src.capacity;
    this->occupied = 0;

    Node* srcIt;
    srcIt = src.head.m_pt;

    while (srcIt != nullptr) {
        this->addStudent(srcIt->data);
        srcIt = srcIt->next.m_pt;
    }
    //CloneRegistration();
}

//------------------------------------------------------------------------------
LinkedList::~LinkedList() {
    // declare 2 Node ptrs
    Node* current = nullptr;
    Node* to_delete = nullptr;

    // set current ptr to head ptr
    current = this->head.m_pt;

    // while loop to delete each itemStack in inventory
    while (current != nullptr) {
        // sets to_delete to current
        to_delete = current;

        // moves current to next Node
        current = current->next.m_pt;

        // deletes to_delete Node
        delete to_delete;

        // sets to_delete Node to nullptr
        to_delete = nullptr;

        //std::cerr << "Deleted ItemStack" << "\n";
    }

    //std::cerr << "Deleted Inventory" << "\n";

    // sets all private members to null
    this->head.m_pt = nullptr;
    this->tail.m_pt = nullptr;
    this->capacity = 0;
    this->occupied = 0;
}

bool LinkedList::isFull() const {
    return (occupied == capacity);
}

void LinkedList::addStudent(Student student) {
    Node * new_node;

    new_node = new Node(student);

    if (this->occupied == 0) {
        this->head = new_node; this->head.m_pt = new_node;
        this->tail = new_node; this->tail.m_pt = new_node;
    }

    else {
        if (!isFull()) {
            (this->tail.m_pt)->next = new_node;(this->tail.m_pt)->next.m_pt = new_node;
            this->tail = new_node;this->tail.m_pt = new_node;
        }

        else {
            cout << "Cannot add another student.\n";
        }
    }

    this->occupied++;
    ///new_node = nullptr;
}

//------------------------------------------------------------------------------
void LinkedList::display(ostream& outs) const {
    outs << "Roster includes " << occupied << " of " << capacity << " students\n";

    Node* it = head.m_pt;
    while (it != nullptr) {
        outs << it->data << endl;

        it = it->next.m_pt;
    }
}

//------------------------------------------------------------------------------
LinkedList& LinkedList::operator=(LinkedList rhs) {
    swap(*this, rhs);
    return *this;
}

//------------------------------------------------------------------------------
void swap(LinkedList& lhs, LinkedList& rhs) {
    swap(lhs.head, rhs.head);
    swap(lhs.tail, rhs.tail);
    swap(lhs.capacity, rhs.capacity);
    swap(lhs.occupied, rhs.occupied);
}
