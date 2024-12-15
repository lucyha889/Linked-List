#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
  public:
    //node structure representing each element in linked list
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
    void AddHead(const T& data);
    void AddTail(const T& data);
    Node* Find(const T& val) const;
    void InsertBefore(Node* node, const T& val);
    void InsertAfter(Node* node, const T& val);
    void InsertAt(const T& val, int index);
    void PrintForward() const;
    //equality operator
    bool operator==(const LinkedList<T>& other) const;
    unsigned int NodeCount() const { 
      return count; 
    }
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
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
    Node* current = new Node(data);
    current->next = head;
    if (head != nullptr) {
        head->prev = current;
    } else {
        tail = current; //if list was empty, new node is also the tail
    }
    head = current;
    count++;
}
//adds new node to tail of the list
template <typename T>
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
//finds the first node with the given value
template <typename T>
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
//inserts a new element before a given node
template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& val) {
  if (node == nullptr) {
  return;
  }
  Node* newNode = new Node(val);
  newNode->next = node;
  newNode->prev = node->prev;
  
  if (node->prev != nullptr) {
    node->prev->next = newNode;
  } else {
    head = newNode;
  }
  node->prev = newNode;
  count++;
}
//inserts a new element after a given node
template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& val) {
  if (node == nullptr) {
    return;
  }
  Node* newNode = new Node(val);
    newNode->prev = node;
    newNode->next = node->next;
  if (node->next != nullptr) {
    node->next->prev = newNode;
  } else {
    tail = newNode;
  }
  node->next = newNode;
  count++;
}
//inserts a new element at a specific index
template <typename T>
void LinkedList<T>::InsertAt(const T& val, int index) {
  if (index < 0 || index > count) {
    return;
  }
  if (index == 0) {
        AddHead(val);
        return;
    } else if (index == count) {
      AddTail(val);
      return;
    }
    Node* current = head;
    for (unsigned int i = 0; i < index; ++i) {
      current = current->next;
    }
    InsertBefore(current, val);
}
//equality operator to check if two linked lists are identical
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& other) const {
  if (count != other.count) {
    return false;
  }
  Node* currentOne = head;
  Node* currentTwo = other.head;
  while (currentOne != nullptr) {
    if (currentOne->data != currentTwo->data) {
      return false;
    }
    currentOne = currentOne->next;
    currentTwo = currentTwo->next;
  }
  return true;
}
//display elements of list from head to tail
template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}