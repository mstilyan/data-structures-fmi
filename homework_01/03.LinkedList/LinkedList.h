//
// Created by stiliele on 15.4.2017
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <assert.h>

template <typename T>
class LinkedList {

private:

    struct Node {
        Node* next;
        Node* prev;
        T value;

        Node(Node*, Node*, T);
    };
    Node* head;
    Node* tail;
    size_t count;

public:

    class InputIterator {
    private:
        Node* nodePtr;

    public:
        InputIterator();
        InputIterator(Node* nodePtr);

        T& operator*() const;
        InputIterator operator++(int);
        InputIterator& operator++();
        bool operator==(const InputIterator& other) const;
        bool operator!=(const InputIterator& other) const;

    };
    class ConstIterator {
    private:
        Node* nodePtr;

    public:
        ConstIterator();
        ConstIterator(Node* nodePtr);

        T operator*() const;
        const ConstIterator& operator++();
	    ConstIterator operator++(int);
        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;
    };

    LinkedList();
    LinkedList(std::initializer_list<T> init_l);
    ~LinkedList();
    LinkedList(const LinkedList<T>& other);
    LinkedList(LinkedList<T>&& other);

    LinkedList<T>& operator=(const LinkedList<T>& other);
    LinkedList<T>& operator=(LinkedList<T>&& other);

    InputIterator begin() const;
    InputIterator end() const;

	ConstIterator cbegin() const;
	ConstIterator cend() const;

    bool is_empty() const;
    void push_back(const T& value);
    void push_front(const T& value);

    void pop_front();
    void pop_back();

    void removeAll();

    static LinkedList<T> REVERSE(const LinkedList<T>& other);
    
};



/*LinkedList implementation*/
template<typename T>
LinkedList<T>::Node::Node(Node* next, Node* prev, T value) :
        next(next),
        prev(prev),
        value(value){

}

template<typename T>
void LinkedList<T>::removeAll(){
    Node* temp = nullptr;
    while (head != nullptr){
        temp = head->next;
        delete head;
        head = temp;
    }
    count = 0;
    tail = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList() :
        head(nullptr),
        tail(nullptr),
        count(0){

}

template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> init_l) :
    LinkedList(){
    for (auto el : init_l)
        push_back(el);
}

template<typename T>
LinkedList<T>::~LinkedList() {
    removeAll();
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) :
    LinkedList(){
    if (!other.is_empty()){
        Node* curr = other.head;
        while  (curr != nullptr){
            push_back(curr->value);
            curr = curr->next;
        }
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other)
{
	this->head = other.head;
	other.head = nullptr;
	this->tail = other.tail;
	other.tail = nullptr;
	this->count = other.count;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &other) {
    if (this != &other){
        removeAll();
        Node* curr = other.head;
        while(curr != nullptr){
            push_back(curr->value);
            curr = curr->next;
        }
    }

    return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> &&other) {
    removeAll();
    this->head = other.head;
    other.head = nullptr;
    this->tail = other.tail;
    other.tail = nullptr;
    this->count = other.count;
    other.count = 0;

	return *this;
}

template<typename T>
typename LinkedList<T>::InputIterator LinkedList<T>::begin() const {
    LinkedList<T>::InputIterator begItr(head);
    return begItr;
}

template<typename T>
typename LinkedList<T>::InputIterator LinkedList<T>::end() const {
    LinkedList<T>::InputIterator endItr(nullptr);
    return endItr;
}

template<typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::cbegin() const {
    LinkedList<T>::ConstIterator cBegItr(head);
    return cBegItr;
}

template<typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::cend() const {
    LinkedList<T>::ConstIterator cEndItr;
    return cEndItr;
}

template<typename T>
bool LinkedList<T>::is_empty() const {
    return count == 0;
}

template<typename T>
void LinkedList<T>::push_back(const T& value) {
    Node* node = new Node(nullptr, nullptr, value);
    if (count == 0){
        head = node;
        tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    ++this->count;
}

template<typename T>
void LinkedList<T>::push_front(const T& value) {
    Node* node = new Node(nullptr, nullptr, value);
    if (count == 0) {
        head = node;
        tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
    count++;
}

template<typename T>
void LinkedList<T>::pop_front() {
    assert(head != nullptr);
    Node* front = head;
    head = head->next;
    head->prev = nullptr;
    delete front;
}

template<typename T>
void LinkedList<T>::pop_back() {
    assert(head != nullptr);
    Node* back = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete back;
}

template<typename T>
LinkedList<T> LinkedList<T>::REVERSE(const LinkedList<T> &other) {
    LinkedList<T> rev;
    Node* temp = other.head;
    while(temp != nullptr){
        rev.push_front(temp->value);
        temp = temp->next;
    }

    return rev;
}
/*----------------------------------------------*/



/*LinkedList<T>::ConstIterator implementation*/
template<typename T>
LinkedList<T>::ConstIterator::ConstIterator() :
        nodePtr(nullptr){

}

template<typename T>
LinkedList<T>::ConstIterator::ConstIterator(Node* nodePtr) :
        nodePtr(nodePtr){

}

template<typename T>
T LinkedList<T>::ConstIterator::operator*() const{
    return nodePtr->value;
}

template<typename T>
const typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::operator++(){
    assert(nodePtr != nullptr);
    nodePtr = nodePtr->next;

    return *this;
}

template<typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator++(int){
    assert(nodePtr != nullptr);
    LinkedList<T>::ConstIterator result = *this;
    ++(*this);
    return result;
}

template<typename T>
bool LinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const {
    return this->nodePtr == other.nodePtr;
}

template<typename T>
bool LinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return this->nodePtr != other.nodePtr;
}
/*----------------------------------------------*/



/*LinkedList<T>::InputIterator implementation*/
template<typename T>
LinkedList<T>::InputIterator::InputIterator() :
        nodePtr(nullptr){

}

template<typename T>
LinkedList<T>::InputIterator::InputIterator(Node* nodePtr) :
        nodePtr(nodePtr){

}

template<typename T>
T& LinkedList<T>::InputIterator::operator*() const {
    return nodePtr->value;
}

template<typename T>
typename LinkedList<T>::InputIterator& LinkedList<T>::InputIterator::operator++(){
    assert(nodePtr != nullptr);
    nodePtr = nodePtr->next;

    return *this;
}

template<typename T>
typename LinkedList<T>::InputIterator LinkedList<T>::InputIterator::operator++(int){
    assert(nodePtr != nullptr);
    LinkedList<T>::InputIterator result = *this;
    ++(*this);
    return result;
}

template<typename T>
bool LinkedList<T>::InputIterator::operator==(const InputIterator& other) const {
    return this->nodePtr == other.nodePtr;
}

template<typename T>
bool LinkedList<T>::InputIterator::operator!=(const InputIterator& other) const {
    return this->nodePtr != other.nodePtr;
}
/*----------------------------------------------*/

#endif //LINKED_LIST_H
