#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <fstream>
#include <iostream>
#include <string>

template <class T>
class BinaryTree {
    private:
        class Node {
            private:
                T* dataPtr;
                Node* leftPtr;
                Node* rightPtr;
            public:
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
                //Node constructors and destructor
                Node ();
                Node (const T&);
                ~Node ();
                //Setters
                void setDataPtr (T*);
                void setData (const T&);
                void setLeftPtr (Node*&);
                void setRightPtr (Node*&);
                //Getters
                T* getDataPtr () const;
                T getData () const;
                Node*& getLeftPtr ();
                Node*& getRightPtr ();
        };
    public:
        typedef Node* Position; 
    private:
        Position root;

        void copyAll (const BinaryTree<T>&);//pending
        void deleteAll (Position&);

        void insertData (Position&, const T&);

        Position& findDataPosition (Position&, const T&);

        Position& getLowest (Position&);
        Position& getHighest (Position&);

        void parsePreOrder (Position& );
        void parseInOrder (Position& );
        void parsePostOrder (Position& );

        void writeToFile (Position&,std::fstream&);

    public:
        class Exception : std::exception {
            private:
                std::string msg;
            public:
                explicit Exception (const char* message) : msg (message) {}

                explicit Exception (const std::string& message) : msg (message) {}

                virtual ~Exception () throw () {}

                virtual const char* what () const throw () {
                    return msg.c_str();
                }
        };
    //Constructors
    BinaryTree ();
    BinaryTree (const BinaryTree&);
    //Destructor
    ~BinaryTree ();
    //Getter
    //Tree Operations
    bool isEmpty () const;
    void insertData (const T&);
    void deleteData (const T&);
    void deleteData (Position& ,const T&);
    T retrieveData (Position& ) const;

    Position& findData (const T&);

    Position& getLowest ();
    Position& getHighest ();

    bool isLeaf (Position& ) const;

    int getHeight ();
    int getHeight (Position&);

    void parsePreOrder ();
    void parseInOrder ();
    void parsePostOrder ();

    void writeToFile (const std::string&);
    void loadFromFile (const std::string&);


    void deleteAll ();//pending

    BinaryTree& operator = (const BinaryTree&);
};
//Node Implementations
//Constructor
template <class T>
BinaryTree<T>::Node::Node () : dataPtr (nullptr), leftPtr (nullptr), rightPtr (nullptr) {}
//Parameterized constructor
template <class T>
BinaryTree<T>::Node::Node (const T& inputData) : dataPtr (new T (inputData)), leftPtr (nullptr), rightPtr (nullptr) {
    if (dataPtr == nullptr){
        throw Exception ("Insufficient Memory, Node Constructor");
    }
} 
//Destructor
template <class T>
BinaryTree<T>::Node::~Node (){
    delete dataPtr;
}
//Node getters and setters
//Setters
template <class T>
void BinaryTree<T>::Node::setData (const T& inputData) {
    if (dataPtr == nullptr){
        if ((dataPtr = new T (inputData)) == nullptr){
            throw Exception ("Insufficient Memory, BinaryTree<T>::Node::setData");
        }
    }
    else {
        *dataPtr = inputData;
    }
}

template <class T>
void BinaryTree<T>::Node::setDataPtr (T* inputNode) {
    dataPtr = inputNode;
}

template <class T>
void BinaryTree<T>::Node::setLeftPtr (Node*& inputNode) {
    leftPtr = inputNode;
}

template <class T>
void BinaryTree<T>::Node::setRightPtr (Node*& inputNode) {
    rightPtr = inputNode;
}
//Getters
template <class T>
T BinaryTree<T>::Node::getData () const {
    if (dataPtr == nullptr){
        throw Exception ("Non-Existen Data, BinaryTree<T>::Node::getData");
    }
    return *dataPtr;
}

template <class T>
T* BinaryTree<T>::Node::getDataPtr () const{
    return dataPtr;
}

template <class T>
typename BinaryTree<T>::Node*& BinaryTree<T>::Node::getLeftPtr (){
    return leftPtr;
}

template <class T>
typename BinaryTree<T>::Node*& BinaryTree<T>::Node::getRightPtr (){
    return rightPtr;
}
//Binary Tree Implementations
//Constructors and destructor
template <class T>
BinaryTree<T>::BinaryTree () : root(nullptr) {}

template <class T>
BinaryTree<T>::BinaryTree (const BinaryTree& inputTree) : root(nullptr) {
    copyAll (inputTree);
}
//Destructor
template <class T>
BinaryTree<T>::~BinaryTree (){
    deleteAll();
}

//Private BinaryTree Method Implementations
template <class T>
void BinaryTree<T>::copyAll (const BinaryTree<T>& inputTree) {
    //Pending
}

template <class T>
void BinaryTree<T>::insertData (Position& rootPosition, const T& inputData) {
    if (rootPosition == nullptr){
        try {
            if ((rootPosition = new Node (inputData)) == nullptr){
                throw Exception ("Insufficient Memory, BinaryTree<T>::insertData");     
            }
        }
        catch (typename Node::Exception nodeException){
            throw Exception(nodeException.what());
        }
    }
    else{
        if (inputData < (rootPosition -> getData())){
            insertData (rootPosition->getLeftPtr(),inputData);
        }
        else{
            insertData (rootPosition->getRightPtr(),inputData);
        }
    }
}

template <class T>
typename BinaryTree<T>::Position& BinaryTree<T>::findDataPosition (Position& newRoot, const T& inputData) {
    if (newRoot == nullptr or inputData == newRoot -> getData ()){
        return newRoot;
    }
    if (inputData < newRoot -> getData ()){
        return findDataPosition(newRoot->getLeftPtr(),inputData);
    }
    return findDataPosition(newRoot->getRightPtr(),inputData);
}

template <class T>
typename BinaryTree<T>::Position& BinaryTree<T>::getLowest (Position& newRoot) {
    if (newRoot == nullptr or newRoot -> getLeftPtr () == nullptr){
        return newRoot;
    }
    else {
        return getLowest (newRoot -> getLeftPtr());
    }
}

template <class T>
typename BinaryTree<T>::Position& BinaryTree<T>::getHighest (Position& newRoot){
    if (newRoot == nullptr or newRoot -> getRightPtr () == nullptr){
        return newRoot;
    }
    else {
        return getHighest (newRoot -> getRightPtr());
    }
}

template <class T>
void BinaryTree<T>::parsePreOrder (Position& newRoot) {
    if (newRoot !=  nullptr){
    std::cout << newRoot -> getData() << ", \n";
    parsePreOrder(newRoot -> getLeftPtr());
    parsePreOrder(newRoot -> getRightPtr());
    }
}

template <class T>
void BinaryTree<T>::parseInOrder (Position& newRoot){
    if (newRoot !=  nullptr){
    parseInOrder(newRoot -> getLeftPtr());
    std::cout << newRoot -> getData() << ", \n";
    parseInOrder(newRoot -> getRightPtr());
    }
}

template <class T>
void BinaryTree<T>::parsePostOrder (Position& newRoot){
    if (newRoot !=  nullptr){
    parsePostOrder(newRoot -> getLeftPtr());
    parsePostOrder(newRoot -> getRightPtr());
    std::cout << newRoot -> getData() << ", \n";
    }
}

//Public and interface method implementations
template <class T>
bool BinaryTree<T>::isEmpty () const {
    return root == nullptr;
}

template <class T>
void BinaryTree<T>::insertData (const T& inputData){
    insertData (root,inputData);
}
template <class T>
void BinaryTree<T>::deleteData (const T& data) {
    deleteData(root,data);
}

template <class T>
void BinaryTree<T>::deleteData (Position& newRoot, const T& data) {
    if (newRoot == nullptr) {
        return;
    }
    if (data < newRoot->getData()) {
        deleteData(newRoot->getLeftPtr(), data);
    } else if (data > newRoot->getData()) {
        deleteData(newRoot->getRightPtr(), data);
    } else {
        if (isLeaf (newRoot)) {
            Node* temp = newRoot;
            newRoot = nullptr;
            delete temp;
        }
        // Case 1: Node with only one child
        else if (newRoot->getLeftPtr() == nullptr) {
            Node* temp = newRoot;
            newRoot = newRoot ->getRightPtr();
            delete temp;
        } else if (newRoot->getRightPtr() == nullptr) {
            Node* temp = newRoot;
            newRoot = newRoot -> getRightPtr();
            delete temp;
        }
        else {
        // Case 2: Node with two children
            Node* temp = getLowest(newRoot->getRightPtr());
            newRoot->setData(temp->getData());
            deleteData(newRoot->getRightPtr(), temp->getData());
        }
    }
}

template <class T>
T BinaryTree<T>::retrieveData (Position& inputPosition) const{
    return inputPosition -> getData ();
}

template<class T>
typename BinaryTree<T>::Position& BinaryTree<T>::findData (const T& inputData) {
    return findDataPosition (root,inputData);
}

template <class T>
typename BinaryTree<T>::Position& BinaryTree<T>::getLowest () {
    return getLowest (root);
}

template <class T>
typename BinaryTree<T>::Position& BinaryTree<T>::getHighest () {
    return getHighest (root);
}

template <class T>
bool BinaryTree<T>::isLeaf (Position& inputPosition) const{
    return inputPosition != nullptr and inputPosition -> getLeftPtr() == inputPosition -> getRightPtr (); 
}

template <class T>
int BinaryTree<T>::getHeight (){
    return getHeight (root);
}

template <class T>
int BinaryTree<T>::getHeight (Position& newRoot){
    if (newRoot == nullptr){
        return 0;
    }

    int leftHeight (getHeight(newRoot ->getLeftPtr()));
    int rightHeight (getHeight(newRoot ->getRightPtr()));

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
/*
Convertion to a to string function type pending
*/
template <class T>
void BinaryTree<T>::parsePreOrder () {
    parsePreOrder (root);
}

template <class T>
void BinaryTree<T>::parseInOrder (){
    parseInOrder(root);
}

template <class T>
void BinaryTree<T>::parsePostOrder (){
    parsePostOrder(root);
}

template <class T>
void BinaryTree<T>::deleteAll (){
    deleteAll(root);
}

template <class T>
void BinaryTree<T>::deleteAll (Position& root) {
    if (root == nullptr) {
        return;
    }
    deleteAll(root -> getLeftPtr());
    deleteAll(root -> getRightPtr());
    deleteData(root -> getData());
}  

template<class T>
BinaryTree<T>& BinaryTree<T>::operator = (const BinaryTree& tree){
    copyall(tree);
    return *this;
}

template <class T>
void BinaryTree<T>::writeToFile (Position& newRoot, std::fstream& file){
    if (!(newRoot == nullptr)) {
        file << newRoot -> getData();
        writeToFile(newRoot -> getLeftPtr(),file);
        writeToFile(newRoot -> getRightPtr(),file);
    }
}

template <class T>
void BinaryTree<T>::writeToFile (const std::string& filepath){
    std::fstream file ("file01.txt",std::ios::out);
    if (file.is_open ()) {
        writeToFile(root,file);
        file.close ();
        std::cout << "Done!\t";
    }
    else {
        std::cout << "Could not open the file\n";
    }
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

template <class T>
void BinaryTree<T>::loadFromFile (const std::string& filePath) {
    Song bufferSong;
    std::fstream file ("file01.txt",std::ios::in);
    if (file.is_open ()) {
        deleteAll();
        while(file >> bufferSong) {
            insertData(bufferSong);
        }
        file.close();
        std::cout << "Done!\n";
    }
    else {
        std::cout << "Could not open the file\n";
    }
    std::cout << "Press Enter to continue...";
    std::cin.get();
}


#endif
