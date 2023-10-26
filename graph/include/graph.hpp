#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "vertex.hpp"
#include "list.hpp"

template <class T>
class Graph {
    public:
        Graph ();
        ~Graph ();
        //Operations
        bool isEmpty ();

        Vertex<T>* getFirstVtx ();
        Vertex<T>* getLastVtx ();
        Vertex<T>* getNextVtx ();

        void push ();
        void delete (Vertex<T>*);

        void linkVtx (Vertex<T>*,Vertex<T>*);
        void unlinkVtx (Vertex<T>*,Vertex<T>*);
    private:
        void insertVtx ();
        bool isValidPos();
        Vertex<T>* header;
};