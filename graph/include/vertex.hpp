#pragma once
#include <iostream>
#include <string>
#include <format>

template <class T>
class Vertex {
    public:
        class EdgeNode {
            public:
                //Constructors
                EdgeNode ();
                EdgeNode (const EdgeNode&);
                EdgeNode (Vertex<T>*, const size_t&, EdgeNode*);
                //Getters and setters
                //Setters
                void setNxtNode (EdgeNode*);
                void setVertex (Vertex<T>*);
                void setWeight (const size_t&);
                //Getters
                EdgeNode* getNxtNode () const;
                Vertex<T>* getVertex () const;
                size_t getWeight () const;
            private:
                EdgeNode* nxtNode;
                Vertex<T>* vertex;
                size_t weight;
        };
    private:

};
//EdgeNode method implementations

//Constructor
template <class T>
Vertex<T>::EdgeNode::EdgeNode (): nxtNode(nullptr), vertex(nullptr), weight(0)  {}

template <class T>
Vertex<T>::EdgeNode::EdgeNode (const EdgeNode& node): nxtNode(node.nxtNode), vertex(node.vertex), weight(node.weight) {} 

template <class T>
Vertex<T>::EdgeNode::EdgeNode (Vertex<T>* vertex, const size_t& weight, EdgeNode* node): nxtNode(node), vertex(vertex), weight(weight) {}
//Getters and setters
//Setters
template <class T>
void Vertex<T>::EdgeNode::setNxtNode (EdgeNode* nxtNode) {
    this -> nxtNode = nxtNode;
}

template <class T>
void Vertex<T>::EdgeNode::setVertex(Vertex<T>* vertex) {
    this -> vertex = vertex;
}

template <class T>
void Vertex<T>::EdgeNode::setWeight (const size_t& weight) {
    this -> weight = weight;
}
//Getters
template <class T>
typename Vertex<T>::EdgeNode* Vertex <T>::EdgeNode::getNxtNode () const {
    return nxtNode;
}

template <class T>
Vertex<T>* Vertex<T>::EdgeNode::getVertex () const {
    return vertex;
}

template <class T>
size_t Vertex<T>::EdgeNode::getWeight () const {
    return weight;
}