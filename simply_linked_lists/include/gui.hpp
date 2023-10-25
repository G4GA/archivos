#pragma once

#include <iostream>
#include <string>
#include "list.hpp"
#include <vector>
#include <format>
#include <fstream>
#include "song.hpp"

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

class GUI {
    public:
        //Constructor
        GUI ();
        void run (List<Song>&);
    private:
        void stop (List<Song>&);
        void menu (List<Song>&);

        void addSong (List<Song>&);
        void deleteSong (List<Song>&);
        void searchSong (List<Song>&);
        void showSong (List<Song>&);
        void loadSong (List<Song>&);
        void writeSong (List<Song>&);
        void exitProgram (bool&);
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