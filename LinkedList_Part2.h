#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class LinkedList {
  public:
    //define node structure for representing each element in linked list again
    struct Node {
      T data;
      Node* next;
      Node* prev;
      Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };
  private:
    Node* head;
    Node* tail;
    unsigned int count;
  public:
    //default constructor with head and tail set to null and count set to 0
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    //destructor
    ~LinkedList();
    //copy constructor
    LinkedList(const LinkedList& other);
    //copy assignment operator
    LinkedList& operator = (const LinkedList& other);
    void AddHead(const T& data);
    void AddTail(const T& data);
    T& operator[](unsigned int index);
    //getting heads and tails nodes
    Node* Head() const { 
      return head; 
      }
    Node* Tail() const { 
      return tail; 
      }
    //find all nodes based on a value
    Node* Find(const T& val) const;
    //find nodes that implement other members of the Big Three
    void FindAll(vector<Node*>& outsideNode, const T& val) const;
    
    unsigned int NodeCount() const { 
      return count; 
      }

    Node* GetNode(unsigned int index) const;

    void PrintForward() const;
    void PrintReverse() const;
};
//deletes all nodes in the linked list to free memory
template <typename T>
LinkedList<T>::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
//adds new node at head of the list
template<typename T>
void LinkedList<T>::AddHead(const T& data) {
    Node* current = new Node(data);
    current->next = head;
    if (head != nullptr) {
        head->prev = current;
    } else {
        tail = current; // If list was empty, new node is also the tail
    }
    head = current;
    count++;
}
//adds new node to tail of the list
template<typename T>
void LinkedList<T>::AddTail(const T& data) {
    if (head == nullptr) {
        AddHead(data);
        return;
    }
    Node* current = new Node(data);
    current->prev = tail;
    tail->next = current;
    tail = current;
    count++;
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
//display elements of list from tail to head
template<typename T>
void LinkedList<T>::PrintReverse() const {
    Node* current = tail;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), count(0) {
  Node* current = other.head;
  while (current != nullptr) {
    AddTail(current-> data);
    current = current->next;
  }
}
//assignment operator 
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
  if (this != &other) {
    Node* current = head;
    while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;

        Node* otherCurrent = other.head;
        while (otherCurrent != nullptr) {
            AddTail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
      }
    }
    return *this;
}
//GetNode must have throw out an error when out of range like operator[]
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
  if (index >= count) {
    throw out_of_range("Index out of range");
  }
    Node* current = head;
    for (unsigned int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& val) const {
  Node* current = head;
  while (current != nullptr) {
    if (current->data == val) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}
template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outsideNode, const T& val) const {
  Node*current = head;
  while (current != nullptr) {
    if (current->data == val) {
      outsideNode.push_back(current);
    }
    current = current->next;
  }
}
//operator[] function to test error when out of range
template<typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    Node* node = GetNode(index);
    if (node == nullptr) {
        throw out_of_range("Index out of range");
    }
    return node->data;
}