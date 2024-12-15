#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
  public:
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
    Node* Head() const { 
      return head; 
      }
    Node* Tail() const { 
      return tail; 
      }
    void AddHead(const T& data);
    void AddTail(const T& data);
    unsigned int NodeCount() const { 
      return count; 
    }
    bool RemoveHead();
    bool RemoveTail();
    bool RemoveAt(unsigned int index);
    unsigned int Remove(const T& val);
    void Clear();
    Node* Find(const T& val) const;
    void PrintForward() const;
    void PrintForwardRecursive(Node* node) const;
    void PrintReverseRecursive(Node* node) const;
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
//removes the head node of the list and updates the head to the next node
template<typename T>
bool LinkedList<T>::RemoveHead() {
    if (head == nullptr) {
    return false;
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) { 
      head->prev = nullptr; // If list becomes empty
    } else {
    tail = nullptr;
    }
    delete temp; 
    count--;
    return true;
}
//removes tail node by iterating through the list to find the node just before the tail
/*template <typename T> did not work since there were problems with RemoveTail() function
bool LinkedList<T>::RemoveTail() {
    if (tail == nullptr) {
      return false;
    }
    if (head == tail) {  //only one node
        delete tail;
        head = nullptr;
        tail = nullptr;
        return true;
    }
    Node* current = head;
    while (current->next != tail) {
        current = current->next;
    }
    current->next = nullptr;
    delete tail;
    tail = current;
    count--;
    return true;
}*/
//edited version of RemoveTail() so that RemoveAt() can function properly
template <typename T>
bool LinkedList<T>::RemoveTail() {
  if (tail == nullptr) {
        return false;
    }
    Node* current = tail; 
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr; //if list is now empty
    }
    delete current;
    count--;
    return true;
}
//remove a node at a specific index
template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
  if (index >= count) {
  return false; //when index are out of bounds
} 
if (index == 0) {
  return RemoveHead();
}
Node* current = head;
for (unsigned int i = 0; i < index; i++) {
    current = current->next;
}
if (current == nullptr) {
  return false;
}
if (current == tail) {
  return RemoveTail();
}
if (current->next) {
    current->next->prev = current->prev;
}
if (current->prev) {
    current->prev->next = current->next;
}
delete current;
count--;
return true;
}
//remove all nodes containing a specific value
template <typename T>
unsigned int LinkedList<T>::Remove(const T& val) {
  unsigned int removeCount = 0;
  Node* current = head;
  Node* prev = nullptr;
  while (current != nullptr) {
    Node* next = current->next; //maintain next pointer before deleting node
    if (current->data == val) {
      if (prev != nullptr) {
        prev->next = next;
      } else {
        head = next;
      }
      if (next != nullptr) {
        next->prev = prev;
      } else {
        tail = prev;
      }
      delete current;
      count--;
      removeCount++;
    } else {
      prev = current;
    }
    current = next;
  }
  return removeCount;
}

//clears all nodes from the list
template<typename T>
void LinkedList<T>::Clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
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
//recursively prints the list starting from a given node
template <typename T>
void LinkedList<T>::PrintForwardRecursive(Node* node) const {
  if (node != nullptr) {
    cout << node->data << " ";
    PrintForwardRecursive(node->next);
  }
}

//recursively prints the list in reverse starting from a given node
template <typename T>
void LinkedList<T>::PrintReverseRecursive(Node* node) const {
  if (node != nullptr) {
    cout << node->data << " ";
    PrintReverseRecursive(node->prev);
  }
}
