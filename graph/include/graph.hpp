#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "vertex.hpp"

template <class T>
class Graph {
    public:
        Graph ();
        ~Graph ();
        //Operations
        bool isEmpty () const;

        Vertex<T>* getFirstVtx () const;
        Vertex<T>* getLastVtx () const;
        Vertex<T>* getNextVtx (Vertex<T>*) const;

        void push ();
        void deleteVtx (Vertex<T>*);

        void linkVtx (Vertex<T>*,Vertex<T>*,const size_t& weight);
        void linkVtx (Vertex<T>*,const size_t& weight);
        void unlinkVtx (Vertex<T>*,Vertex<T>*);
        void clear ();
    private:
        void insertVtx (Vertex<T>*,const std::string&,const T&);
        bool isValidPos(Vertex<T>*) const;
        Vertex<T>* header;
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
};
//Method definitions
template <class T>
Graph<T>::Graph (): header(nullptr) {}

template <class T>
Graph<T>::~Graph () {
    clear ();
}

template <class T>
bool Graph<T>::isEmpty () const {
    return header == nullptr;
}

template <class T>
Vertex<T>* Graph<T>::getFirstVtx () const {
    return header;
}

template <class T>
Vertex<T>* Graph<T>::getLastVtx () const {
    Vertex<T>* returnVtx = header;
    while (returnVtx -> getNextVtx() != nullptr) {
        returnVtx = returnVtx -> getNextVtx();
    }
    return returnVtx;
}

template <class T>
Vertex<T>* Graph<T>::getNextVtx(Vertex<T>* vertex) const {
    return vertex -> getNextVtx();
}

template <class T>
bool Graph<T>::isValidPos (Vertex<T>* vertex) const {
    Vertex<T>* aux = header;
    while (aux != nullptr) {
        if (aux == vertex) {
            return true;
        }
        aux = aux -> getNextVtx();
    }
    return false;
}

template <class T>
void Graph<T>::insertVtx (Vertex<T>* nodePos, const std::string& name, const T& data) {
    if (nodePos != nullptr and !isValidPos(nodePos)) {
        throw Exception("Invalid position in Graph<T>::insertVtx");
    }
    Vertex<T>* newVertex = new Vertex<T>(name,data);
    if (newVertex == nullptr) {
        throw Exception ("Not enough memory available in Graph<T>::insertVtx");
    }
    if (nodePos == nullptr) {
        newVertex -> setNextVtx(header);
        header = newVertex;
    } else {
        newVertex -> setNextVtx(nodePos -> getNextVtx());
        nodePos -> setNextVtx(newVertex);
    }
}

template <class T>
void Graph<T>::deleteVtx (Vertex<T>* vtx) {
    if (!isValidPos(vtx)) {
        throw Exception("Invalid position in Graph<T>::deleteVtx");
    }
    if (vtx == header) {
        header = vtx -> getNextVtx();
    }
    else {
        Vertex<T>* aux = header;
        while (aux -> getNextVtx() != vtx) {
            aux = aux -> getNextVtx();
        }
        aux -> setNextVtx(vtx -> getNextVtx());
    }
    Vertex<T> *aux2 = header;
    while (aux2 != nullptr) {
        unlinkVtx(aux2,vtx);
        aux2 = aux2 -> getNextVtx();
    }
    delete vtx;
}

template <class T>
void Graph<T>::unlinkVtx (Vertex<T> *vertex1, Vertex<T> *vertex2) {
    if (isValidPos(vertex1) and isValidPos(vertex2)){
        vertex1 -> deleteConnection(vertex1 ->findConnection(vertex2));
        vertex2 -> deleteConnection(vertex2 ->findConnection(vertex1));
    }
}

template <class T>
void Graph<T>::linkVtx (Vertex<T>* vertex, const size_t& weight) {
    vertex -> addConnection(vertex,weight);
}

template <class T>
void Graph<T>::linkVtx (Vertex<T> *vertex1, Vertex<T> *vertex2,const size_t& weight) {
    if (isValidPos(vertex1) and isValidPos(vertex2)) {
        vertex1 -> addConnection(vertex2,weight);
        vertex2 -> addConnection(vertex1,weight);
    }
}

template <class T>
void Graph<T>::clear () {
    while (header -> getNextVtx() != nullptr) {
        unlinkVtx(header,header -> getNextVtx());
    }
    delete header;
    header = nullptr;
}