#pragma once
#include <iostream>
#include <format>
#include <fstream>
#include "../include/song.hpp"
#include "../include/binarytree.hpp"

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

class GUI {
    public:
        GUI (BinaryTree<Song>& songTree);
        void runMenu (BinaryTree<Song>& songTree);
    private:
        void addSong (BinaryTree<Song>& songTree);
        void deleteSong (BinaryTree<Song>& songTree);
        void searchSong (BinaryTree<Song>&songTree);
        void showSong (BinaryTree<Song>&songTree);
        void loadSong (BinaryTree<Song>&songTree);
        void writeSong (BinaryTree<Song>&songTree);
        void exitProgram (bool& notExit); 
        std::vector<std::string> splitString (const std::string& input, char delimiter);

    enum Options{
        add_song = 1,
        delete_song,
        search_song,
        show_songs,
        load_songs,
        write_songs,
        exit_program,
    };
    const int YES_ANSWER = 1;
};