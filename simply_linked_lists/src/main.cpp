#include <iostream>
#include <string>
#include <format>
#include "../include/list.hpp"
#include "../include/gui.hpp"
#include "../include/song.hpp"

int main() {
    List<Song> songList = List<Song>();
    GUI myGUI = GUI();

    myGUI.run(songList);
    return 0;
}