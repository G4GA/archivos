#pragma once
#include <exception>
#include <functional>
#include <string>
#include <iostream>
#include <conio.h>


template <class T>
class List {
    public:
        class Node {
            public:
                // Constructors
                Node ();
                Node (const T&);
                Node (const T*&);
                Node (const T&,Node*);
                Node (const T*&,Node*);
                //Destructor
                ~Node ();
                //Getters
                Node* getNextPtr() const;
                T getData() const;
                T* getDataPtr() const;
                //Setters
                void setNextPtr(Node*);
                void setData (const T&);
                void setDataPtr(const T*&);
                //Exception handler
                class Exception : public std::exception{
                    private:
                        std::string msg;
                    public:
                        explicit Exception (const char* message) : msg (message) {}
                        explicit Exception (const std::string& message) : msg(message) {}

                        virtual ~Exception () throw () {}

                        virtual const char* what () const throw (){
                            return msg.c_str ();
                        }
                };
            private:
                T* dataPtr;
                Node* nextPtr;
        };
        class Exception : public std::exception{
            private:
                std::string msg;
            public:
                explicit Exception (const char* message) : msg (message) {}
                explicit Exception (const std::string& message) : msg(message) {}

                virtual ~Exception () throw () {}

                virtual const char* what () const throw (){
                    return msg.c_str ();
                }
        };
    private:
        Node* header;

        bool isValidPos (Node* ) const;
    public:
        //Constructors
        List ();
        List (const List<T>& ); // 
        //Destructor
        ~List ();
        //List operations
        bool isEmpty () const;

        void insertData (Node*, const T&);
        //Push method
        void push (const T&);
        void deleteData (Node*);

        Node* getFirstPos () const;
        Node* getLastPos () const;
        Node* getNextPos (Node*) const;

        Node* findData (const T&) const;
        T retrieve (Node*) const;

        void clearList ();
};
//Implementations
//List
//Constructor
template <class T>
List<T>::List () : header(nullptr) {}

template <class  T>
List<T>::~List () {
    clearList();
}
//Methods
template <class T>
bool List<T>::isEmpty () const {
    return (this -> header == nullptr);
}

template <class T>
bool List<T>::isValidPos (List<T>::Node* nodePtr) const {
    List<T>::Node *aux = header; 

    while (aux != nullptr) {
        if (nodePtr == aux) {
            return true;
        }
        else {
            aux = aux -> getNextPtr ();
        }
    }
    return false;
}

template <class T>
void List<T>::insertData (Node* nodePtr, const T& data) {
    if (nodePtr != nullptr and !isValidPos(nodePtr)) {
        throw Exception("Invalid position, List<T>::insertData");
    }

    List<T>::Node *newNode = new Node(data);

    if (newNode == nullptr){
        Exception ("Memory not available, List<T>::insertData");
    }

    if (nodePtr == nullptr) {
        newNode -> setNextPtr(header);
        header = newNode;
    }
    else {
        newNode  -> setNextPtr(nodePtr -> getNextPtr());
        nodePtr -> setNextPtr(newNode);
    }
}

template <class T>
void List<T>::push (const T& data) {
    insertData(nullptr,data);
}

template <class T>
void List<T>::deleteData(Node* nodeToDelete) {
    if (!isValidPos(nodeToDelete)) {
        throw Exception("Invalid Position, List<T>::deleteData");
    }

    if (nodeToDelete == header) {
        header = nodeToDelete->getNextPtr();
    } else {
        Node* prevNode = header;
        while (prevNode->getNextPtr() != nodeToDelete) {
            prevNode = prevNode->getNextPtr();
        }
        prevNode->setNextPtr(nodeToDelete->getNextPtr());
    }

    delete nodeToDelete;
}

template <class T>
typename List<T>::Node* List<T>::getFirstPos () const {
    return header;
}

template <class T>
typename List<T>::Node* List<T>::getLastPos () const {
    List<T>::Node *aux = header;
    if (isEmpty()) {
        return nullptr;
    }
    else {
        while (aux -> getNextPtr() != nullptr) {
            aux = aux -> getNextPtr();
        }
        return aux;
    }
}

template <class T>
typename List<T>::Node* List<T>::getNextPos (Node* nodePtr) const {
    if (!isValidPos(nodePtr)) {
        throw Exception ("Invalid Position, List<T>::Node* List<T>::getNextPos");
    }
    
    return nodePtr -> getNextPtr();
}

template <class T>
typename List<T>::Node* List<T>::findData (const T& dataInput) const {
    List<T>::Node* aux = header;
    while (aux != nullptr) {
        if (aux -> getData() == dataInput) {
            return aux;
        }
        aux = aux -> getNextPtr ();
    }
    return aux;
}

template <class T>
T List<T>::retrieve (Node* nodePtr) const {
    if (!isValidPos (nodePtr)) {
        throw Exception ("Invalid Position, List<T>::retrieve");
    }
    return nodePtr -> getData();
}

template <class T>
void List<T>::clearList () {
    while (!isEmpty()) {
        deleteData(header);
    }
}
//Node
//Constructor
template <class T>
List<T>::Node::Node () : dataPtr(nullptr), nextPtr(nullptr) {}


template <class T>
List<T>::Node::Node (const T& data) : dataPtr(new T(data)), nextPtr(nullptr) {
    if (dataPtr == nullptr) {
        throw Exception("Insuficcient Memory, List<T>::Node::Node");
    }
}

template <class T>
List<T>::Node::Node (const T*& dataPtr) : dataPtr(dataPtr) {}


template <class T>
List<T>::Node::Node (const T& data,Node* nextPtr) : dataPtr (new T(data)), nextPtr(nextPtr) {
    if (dataPtr == nullptr){
        throw Exception("Insuficcient Memory, List<T>::Node::Node");
    } 
}

template <class T>
List<T>::Node::Node (const T*& dataPtr,Node* nextPtr) : dataPtr(dataPtr), nextPtr(nextPtr) {}
//Destructor
template <class T>
List<T>::Node::~Node () {
    delete dataPtr;
}
//Getters
template <class T>
typename List<T>::Node* List<T>::Node::getNextPtr() const {
    return this -> nextPtr;
}

template <class T>
T List<T>::Node::getData() const {
    return *dataPtr;
}

template <class T>
T* List<T>::Node::getDataPtr() const {
    return dataPtr;
}
//Setters
template <class T>
void List<T>::Node::setNextPtr(Node* nextPtr) {
    this -> nextPtr = nextPtr;
}

template <class T>
void List<T>::Node::setData (const T& data) {
    if (dataPtr == nullptr){
        if (dataPtr = new T(data) == nullptr) {
            throw Exception("Insufficient Memory, List<T>::Node::setData");
        }
    }
    else {
        *dataPtr = data;
    }
    
}

template <class T>
void List<T>::Node::setDataPtr(const T*& dataPtr) {
    if (this -> dataPtr == nullptr) {
        this -> dataPtr == dataPtr;
    }
    else {
        delete this -> dataPtr;
        this -> dataPtr = dataPtr;
    }
}