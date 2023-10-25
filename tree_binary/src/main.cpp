#include <iostream>
#include <random>
#include <format>
#include "../include/song.hpp"
#include "../include/binarytree.hpp"
#include "../include/GUI.hpp"

int main () {
    BinaryTree<Song> myTree;
    GUI gui (myTree);
    return 0;
}