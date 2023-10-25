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
                EdgeNode (EdgeNode*);
                EdgeNode (Vertex<T>*, const int&);
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