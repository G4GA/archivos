#pragma once
#include <iostream>
#include <format>
#include <fstream>
#include <string>
#include "../include/song.hpp"
#include "../include/graph.hpp"

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

class GUI {
    public:
        GUI (Graph<Song>& songGraph);
        void runMenu (Graph<Song>& songGraph);
    private:
        void addSong (Graph<Song>& songGraph);
        void linkSongs (Graph<Song>& songGraph);
        void unlinkSongs (Graph<Song>& songGraph);
        void deleteSong (Graph<Song>& songGraph);
        void showConnections (Graph<Song>&songGraph);
        void showSong (Graph<Song>&songGraph);
        void loadSong (Graph<Song>&songGraph);
        void writeSong (Graph<Song>&songGraph);
        void exitProgram (bool& notExit);
        // std::vector<std::string> splitString (const std::string& input, char delimiter);

    enum Options{
        add_song = 1,
        delete_song,
        link_songs,
        unlink_songs,
        show_connections,
        show_song,
        write_to_file,
        load_from_file,
        exit,
    };
    const int YES_ANSWER = 1;
};