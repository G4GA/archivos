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
        class EdgeList {
            public:
                //Constructors
                EdgeList ();
                //Destructor
                ~EdgeList ();
                //Methods for the list
                bool isEmpty () const;

                void insertData (EdgeNode*, Vertex<T>*,const size_t&);
                //Push method
                void push (Vertex<T>*,const size_t&);
                void deleteData (EdgeNode*);

                EdgeNode* getFirstPos () const;
                EdgeNode* getLastPos () const;
                EdgeNode* getNextPos (EdgeNode*) const;

                EdgeNode* findByName (const std::string&) const;
                //Vertex<T> retrieve (EdgeNode*) const;

                void clearList ();
            private:
                EdgeNode *header;

                bool isValidPos (EdgeNode*);
        };
        //Constructors
        Vertex ();
        Vertex (const std::string&, const T&);
        ~Vertex ();
        //Getters and setters
        void setNextVtx (Vertex<T>*);
        void setName (const std::string&);
        void setData (const T& data);
        //Getters
        Vertex<T>* getNextVtx () const;
        std::string getName () const;
        T getData () const;
        void addConnection (Vertex<T>*,const size_t& weight);
        void deleteConnection (EdgeNode*);
        EdgeNode* findConnection (Vertex<T>*);
    private:
    //Attributes
    Vertex<T>* nextVtx;
    std::string name;
    EdgeList edges;
    T* data;
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
//EdgeNode class method definitions

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
//Edgelist class method definitions

template <class T>
Vertex<T>::EdgeList::EdgeList (): header(nullptr) {}

template<class T>
Vertex<T>::EdgeList::~EdgeList () {
    clearList();
}

template <class T>
bool Vertex<T>::EdgeList::isEmpty () const {
    return header == nullptr;

}

template <class T>
bool Vertex<T>::EdgeList::isValidPos (EdgeNode* edgeNode) {
    EdgeNode* aux = header;
    while (aux != nullptr) {
        if (aux == edgeNode) return true;
        aux = aux -> getNxtNode ();
    }
    return false;
}


template <class T>
void Vertex<T>::EdgeList::insertData (EdgeNode* edgeNode, Vertex<T>* vertex, const size_t& weight) {
    if (edgeNode != nullptr and !isValidPos(edgeNode)) throw Exception ("Invalid position in Vertex<T>::EdgeList::insertData");

    EdgeNode* newNode = new EdgeNode (vertex,weight);

    if (newNode == nullptr) throw Exception("Not enough memory available in Vertex<T>::EdgeList::insertData");

    if (edgeNode == nullptr) {
        newNode -> setNxtNode(header);
        header = newNode;
    }
    else {
        newNode -> setNxtNode(edgeNode -> getNxtNode());
        edgeNode -> setNxtNode(newNode);
    }
}
//Push method
template <class T>
void Vertex<T>::EdgeList::push (Vertex<T>* vertex,const size_t& weight) {
    if (findByName(vertex -> getName()) == nullptr) {
        insertData(nullptr,vertex,weight);
    }
}

template <class T>
void Vertex<T>::EdgeList::deleteData (EdgeNode* delEdge) {
    if (!isValidPos(delEdge)) throw Exception ("Invalid position in Vertex<T>::EdgeList::deleteData");

    if (delEdge == header) {
        header = delEdge -> getNxtNode();
    }
    else {
        EdgeNode* aux = header;
        while (aux -> getNxtNode() != delEdge) {
            aux = aux -> getNxtNode();
        }
        aux -> setNxtNode(delEdge -> getNxtNode());
    }

    delete delEdge;
}

template <class T>
typename Vertex<T>::EdgeNode* Vertex<T>::EdgeList::getFirstPos () const {
    return header;
}

template <class T>
typename Vertex<T>::EdgeNode* Vertex<T>::EdgeList::getLastPos () const {
    EdgeNode *aux = header;

    while (aux -> getNxtNode() != nullptr) {
        aux = aux -> getNxtNode();
    }

    return aux;
}

template <class T>
typename Vertex<T>::EdgeNode* Vertex<T>::EdgeList::getNextPos (EdgeNode* edgeNode) const {
    return edgeNode -> getNxtNode();
}

//Pending
template <class T>
typename Vertex<T>::EdgeNode* Vertex<T>::EdgeList::findByName (const std::string& name) const {
    EdgeNode* returnNode = header;
    while (returnNode != nullptr) {
        if (returnNode -> getVertex() -> getName() == name){
            return returnNode;
        }
        returnNode = returnNode -> getNxtNode();
    }
    return returnNode;
}

template <class T>
void Vertex<T>::EdgeList::clearList () {
    while (!isEmpty()) {
        deleteData (header);
    }
}

//Vertex class methods
//Constructors
template <class T>
Vertex<T>::Vertex (): nextVtx (nullptr), data(nullptr), edges() {}

template <class T>
Vertex<T>::Vertex (const std::string& name, const T& data): name(name), data (new T(data)), edges() {
    if (this -> data == nullptr) {
        throw Exception ("Not enough memory available in Vertex<T>::Vertex");
    }
}
//Destructor
template <class T>
Vertex<T>::~Vertex () {
    delete data;
    edges.clearList();
}
//Getters and setters
//Setters
template <class T>
void Vertex<T>::setData (const T&  data) {
    this -> data = new T(data);
    if (this -> data == nullptr) {
        throw Exception ("Not enough memory available in Vertex<T>::setData");
    }
}

template <class T>
void Vertex<T>::setName (const std::string& name) {
    this -> name = name;
}

template <class T>
void Vertex<T>::setNextVtx (Vertex<T>* nextVtx) {
    this -> nextVtx = nextVtx;
}
//Gettters
template <class T>
Vertex<T>* Vertex<T>::getNextVtx () const{
    return nextVtx;
}

template <class T>
std::string Vertex<T>::getName () const {
    return name;
}

template  <class T>
T Vertex<T>::getData () const{
    return *data;
}

template <class T>
void Vertex<T>::addConnection (Vertex<T>* vertex,const size_t& weight) {
    edges.push(vertex,weight);
}

template <class T>
void Vertex<T>::deleteConnection(EdgeNode* edge) {
    edges.deleteData(edge);
}

template <class T>
typename Vertex<T>::EdgeNode* Vertex<T>::findConnection (Vertex<T>* vertex) {
    return edges.findByName(vertex -> getName());
}