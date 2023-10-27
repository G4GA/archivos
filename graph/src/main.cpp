#include <iostream>
#include <random>
#include <format>
#include "../include/song.hpp"
#include "../include/vertex.hpp"
#include "../include/graph.hpp"
#include "../include/GUI.hpp"

int main () {
    Graph<Song> mySongs;
    GUI myGui (mySongs);
    return 0;
}
