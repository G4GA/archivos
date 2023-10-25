#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "vertex.hpp"
#include "list.hpp"

template <class T>
class Graph {
    public:
        void Graph ();
        void addVertex();
        void connect (Vertex<T>*,Vertex<T>*);
        Vertex<T>* searchByName ();
        Vertex<T>* searchByData ();
    private:
        List<Vertex<T>> vertex; 
};