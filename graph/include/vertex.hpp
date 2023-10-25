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
                EdgeNode (Vertex<T>*, const int&, EdgeNode*);
                //Getters and setters
                //Setters
                void setNxtNode (EdgeNode*);
                void setVertex (Vertex<T>*);
                void setWeight (const int&);
                //Getters
                EdgeNode* getNxtNode () const;
                Vertex<T>* getVertex () const;
                int getWeight () const;
            private:
                EdgeNode* nxtNode;
                Vertex<T>* vertex;
                int weight;
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
Vertex<T>::EdgeNode::EdgeNode (Vertex<T>* vertex, const int& weight, EdgeNode* node): nxtNode(node), vertex(vertex), weight(weight) {}