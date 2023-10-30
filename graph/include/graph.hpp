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
        Vertex<T>* getByName (const std::string&) const;

        void push (const std::string&,const T&);
        void deleteVtx (Vertex<T>*);

        void linkVtx (Vertex<T>*,Vertex<T>*,const size_t& weight);
        void linkVtx (Vertex<T>*,const size_t& weight);
        void unlinkVtx (Vertex<T>*,Vertex<T>*);
        void unlinkVtx (Vertex<T>*);
        void clear ();
        void insertVtx (Vertex<T>*,const std::string&,const T&);
        int writeFile(const std::string&);
        int loadFile (const std::string&);
    private:
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
Vertex<T>* Graph<T>::getByName (const std::string& name) const {
    Vertex<T> *i = getFirstVtx();
    while (i != nullptr and name != i -> getName()) {
        i = i -> getNextVtx();
    }
    return i;
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
void Graph<T>::push (const std::string& name,const T& data) {
    insertVtx(nullptr,name,data);
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
void Graph<T>::unlinkVtx (Vertex<T> *vertex1) {
    if (isValidPos(vertex1)){
        vertex1 -> deleteConnection(vertex1 ->findConnection(vertex1));
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

template <class T>
int Graph<T>::writeFile(const std::string& path) {
    int returnCode = 0;
    Vertex<T> *i = getFirstVtx(),
              *j;
    typename Vertex<T>::EdgeNode *aux;
    std::fstream file (path, std::ios::out);
    if (file.is_open()) {
        while (i != nullptr) {
            file << *i;
            i = i -> getNextVtx();
        }
        i = getFirstVtx();
        while (i != nullptr) {
            j = i;
            while (j != nullptr) {
                if (j -> findConnection(i) != nullptr) {
                    aux = j -> findConnection(i);
                    file << i -> getName() << '|' << j -> getName() << '|' << aux -> getWeight() << "*";
                }
                j = j -> getNextVtx();
            }
            i = i -> getNextVtx();
        }
    }
    else {
        returnCode = -1;
    }
    file.close();
    return returnCode;
}

template <class T>
int Graph<T>::loadFile (const std::string& path) {
    std::string buffer_str,
                node1_str,
                node2_str,
                weight_str,edge_str;
    Vertex<T> buffer_vtx,*vtx2,*vtx1;
    Song data;
    int returnCode = 0;
    std::string::size_type pos = 0;
    std::fstream file (path, std::ios::in);
    
    if (file.is_open ()){
        
            while (getline(file,buffer_str,'\n')) {
                std::istringstream strm(buffer_str);
                try {
                strm >> buffer_vtx;
                strm.clear();
                data = buffer_vtx.getData();
                push(buffer_vtx.getName(),data);
                }
                catch (std::invalid_argument) {
                        break;
                    }   
                }
        std::string field_del("|"),object_del("*");
        std::string token;
        while ((pos = buffer_str.find(object_del)) != std::string::npos) {
            token = buffer_str.substr(0,pos+1);
            buffer_str.erase(0,pos + 1);
            
            pos = token.find(field_del,0);
            node1_str = token.substr(0,pos);
            token.erase(0,pos+1);
            
            pos = token.find(field_del,0);
            node2_str = token.substr(0,pos);
            token.erase(0,pos+1);

            pos = token.find(object_del,0);
            weight_str = token.substr(0,pos);
            token.erase(0,pos+1);
            linkVtx(getByName(node1_str),getByName(node2_str),std::stoi(weight_str));
        }
    }
    else {
        returnCode = -1;
    }
    file.close();
    return returnCode;
}

