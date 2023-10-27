#include "../include/GUI.hpp"

GUI::GUI (Graph<Song>& songGraph) {
    runMenu (songGraph);
}


void GUI::runMenu (Graph<Song>& songs) {
    std::string optString;
    int option;
    bool flag = true;
    bool enterSwitch;
    while (flag) {
        enterSwitch = true;
        system(CLEAR);
        std::cout << "\t\tSong Graph\n\n\n";
        std::cout << "Choose one of the following options: \n";
        std::cout << "1. Add Song\n2.Delete Song\n3.Link Songs\n4. Unlink Songs\n";
        std::cout << "5. Show Song Connections\n6. Show Song\n7. Write to file\n8. Load from file\n9. Exit\n-> ";
        std::getline (std::cin, optString);
        try {
            option = std::stoi (optString);
        }
        catch (std::invalid_argument) {
            enterSwitch = false;
            std::cerr << "Not a Number! Try Again\n";
            std::cerr << "Press Enter to continue...";
            std::cin.get();
        }
        if (enterSwitch) {
            switch (option) {
                case add_song:
                    addSong (songs);
                break;
                case delete_song:
                    deleteSong(songs);
                break;
                case link_songs:
                    linkSongs(songs);
                break;
                case unlink_songs:
                    unlinkSongs(songs);
                break;
                case show_connections:
                    showConnections(songs);
                break;
                case show_song:
                    showSong(songs);
                break;
                case write_to_file:
                    writeSong(songs);
                break;
                case load_from_file:
                    loadSong(songs);
                break;
                case exit:
                    exitProgram(flag);
                break;
                default:
                    std::cout << "Invalid option, Try Again\n";
                    std::cout << "Press Enter to continue\n";
                    std::cin.get();
                break;
            }
        }
    }
}

void GUI::addSong (Graph<Song>& songGraph) {}
void GUI::linkSongs (Graph<Song>& songGraph) {}
void GUI::unlinkSongs (Graph<Song>& songGraph) {}
void GUI::deleteSong (Graph<Song>& songGraph) {}
void GUI::showConnections (Graph<Song>&songGraph) {}
void GUI::showSong (Graph<Song>&songGraph) {}
void GUI::loadSong (Graph<Song>&songGraph) {}
void GUI::writeSong (Graph<Song>&songGraph) {}
void GUI::exitProgram (bool& notExit) {}