#pragma once
#include <iostream>
using namespace std;

//template def for doubly linked list
template<typename T>
class LinkedList {
public: 
//node structure representing each element in linked list
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };
//private class for pointers to head and tail and number of nodes in the list
private:
    Node* head;
    Node* tail;
    unsigned int count;
public:
    //default constructor with head and tail set to null and count set to 0
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    //destructor
    ~LinkedList();
    //ways to add info to the container
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    //a way to get some info about the container
    unsigned int NodeCount() const { 
      return count; 
    }
    //ways to see the data in the container
    void PrintForward() const;
    void PrintReverse() const;
    //getter for head and tail pointers
    Node* getHead() const { 
    return head; 
      }
    Node* getTail() const { 
    return tail; 
      }
};
//deletes all nodes in the linked list to free memory
template<typename T>
LinkedList<T>::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
//adds new node to the head of the list
template<typename T>
void LinkedList<T>::AddHead(const T& data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    if (head != nullptr) {
        head->prev = newNode;
    } else {
        tail = newNode; //if list was empty, new node is also the tail
    }
    head = newNode;
    count++;
}
//adds new node to the tail of the list
template<typename T>
void LinkedList<T>::AddTail(const T& data) {
    if (head == nullptr) {
        AddHead(data);
        return;
    }
    Node* newNode = new Node(data);
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
    count++;
}
//adds multiple nodes at the head of the list
template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
    for (int i = count - 1; i >= 0; --i) {
        AddHead(data[i]);
    }
}
//adds multiple nodes at the tail of the list
template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    for (unsigned int i = 0; i < count; ++i) {
        AddTail(data[i]);
    }
}
//display elements of list from head to tail
template<typename T>
void LinkedList<T>::PrintForward() const {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
//display elments of list from tail to head
template<typename T>
void LinkedList<T>::PrintReverse() const {
    Node* current = tail;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}