#pragma once
#include <iostream>
#include <string>
#include "list.hpp"

template <class T>
class Vertex {
    public:
        class Edge {
        public:
                //Constructors
                Edge ();
                Edge (Vertex<T>*vertex, const int& weight);
                Edge (const Edge&);
                //Getters and setters
                //Setters
                void setVertex (Vertex<T>* vertex);
                void setWeight (const int& weight);
                //Getters
                Vertex<T>* getVertex () const;
                int getWeight () const;
            private:
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
                Vertex<T>* vertex;
                int* weight;
        };
    private:
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
        T* data;
        std::string name;
        List<Edge> edges;
    public:
        //Constructors
        Vertex ();
        Vertex (const T& data, const std::string& name);
        Vertex (const T& data, const std::string& name);
        //Getters and setters
        //Setters
        void setData (const T& data);
        void setName (const std::string& name);
        void addEdge (const Edge& edge);
        void deleteConnection(typename List<Edge>::Node*);
        //Getters
        T getData () const;
        std::string getName () const;
};
//Constructors
template <class T>
Vertex<T>::Vertex (): data(nullptr), nxtVertex(nullptr), edges() {}

template <class T>
Vertex<T>::Vertex (const T& data, const std::string& name): data(new T(data)),
                                                            name(name), 
                                                            nxtVertex(nullptr),
                                                            edges() {
    if ((this -> data = new T(data)) == nullptr) {
        throw Exception("Not enough memory available in Vertex<T>::setData");
    }
}

template <class T>
Vertex<T>::Vertex (const T& data, const std::string& name, Vertex<T>* nxtVertex): data(data), 
                                                                                                name(name),
                                                                                                nxtVertex(nxtVertex), 
                                                                                                edges() {}
//Getters and setters
//Setters
template <class T>
void Vertex<T>::setData (const T& data){
    if ((this -> data = new T(data)) == nullptr) {
        throw Exception("Not enough memory available in Vertex<T>::setData");
    }
}
template<class T>
void Vertex<T>::setName (const std::string& name) {
    this -> name = name;
}
template <class T>
void Vertex<T>::setNxtVertex (Vertex<T>* nxtVertex) {
    this -> nxtVertex = nxtVertex;
}
//Getters
template <class T>
T Vertex<T>::getData () const {
    return *data;
}
template <class T>
std::string Vertex<T>::getName () const {
    return name;
}
//Edge list operation wrappers
template <class T>
void Vertex<T>::addEdge (const Edge& edge) {
    edges.push(edge);
}

template <class T>
void Vertex<T>::deleteConnection (typename List<Edge>::Node* vertex) {
    edges.deleteData(vertex);
}
//Edge Implementations
//Constructor
template <class T>
Vertex<T>::Edge::Edge (): vertex(nullptr), weight(new int(0)) {
    if (weight == nullptr) throw Exception("Nou enough memory in (Vertex<T>::Edge::Edge)");
}

template <class T>
Vertex<T>::Edge::Edge (const Edge& edge): vertex(edge.vertex), weight(edge.weight) {}

template <class T>
Vertex<T>::Edge::Edge (Vertex<T>*vertex, const int& weight):vertex(vertex), weight(new int(weight)) {
    if (this -> weight == nullptr) {
        throw Exception ("Not enough memory available in (Vertex<T>::Edge::Edge)");
    }
}

//Getters and setters
//Setters

template <class T>
void Vertex<T>::Edge::setVertex (Vertex<T>* vertex ) {
    this -> vertex = vertex;
}

template <class T>
void Vertex<T>::Edge::setWeight (const int &weight) {
    if ((this -> weight = new int(weight)) == nullptr) {
        throw Exception ("Not enough memory avilable in (Vertex<T>::Edge::setWeight)");
    }
}

template <class T>
Vertex<T>* Vertex<T>::Edge::getVertex () const {
    return vertex;
}

template <class T>
int Vertex<T>::Edge::getWeight() const {
    return *weight;
}
