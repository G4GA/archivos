#include "../include/GUI.hpp"


GUI::GUI (BinaryTree<Song>& songTree) {
    runMenu (songTree);
}

void GUI::runMenu (BinaryTree<Song>& songTree) {
    bool flag = true;
    std::string option;
    int opt;
    
    while (flag) {
        system(CLEAR);
        std::cout << "Welcome to the song tree handler\nSelect one of the following options\n";

        std::cout << "1. Add Song\n2. Delete Song\n3. Search song\n4. Show Songs\n5. Load songs from file\n6. Write  songs to file\n7. Exit Program\n-> ";
        std::getline(std::cin,option);
        try {
            opt = std::stoi(option);
            system(CLEAR);
            switch (opt) {
                case Options::add_song:
                    addSong(songTree);
                    break;

                case Options::delete_song:
                    deleteSong(songTree);
                    break;

                case Options::search_song:
                    searchSong(songTree);
                    break;

                case Options::show_songs:
                    showSong(songTree);
                    break;
                case Options::load_songs:
                    loadSong(songTree);
                    break;
                case Options::write_songs:
                    writeSong(songTree);
                    break;
                case Options::exit_program:
                    exitProgram(flag);
                    break;
                default:
                    std::cout << "Incorrect option! Try again.\n";
                    std::cout << "Press Enter to continue\n";
                    std::cin.get();
                    break;
            }
        }
        catch (std::invalid_argument) {
            std::cout << "\nThat is not a number! Try again.";
            std::cout << "Press Enter to continue\n";       
            std::cin.get();
        }
    }
    songTree.~BinaryTree();
}

void GUI::addSong (BinaryTree<Song>& songTree) {
    Song auxSong;
    std::string buffer;
    std::vector<std::string> length;
    
    std::cout << "What is the name of the song?: ";
    std::getline(std::cin,buffer);
    auxSong.setName(buffer);

    std::cout << "What is the name of the artist?: ";
    std::getline (std::cin, buffer);
    auxSong.setArtist(buffer);

    std::cout << "Enter song duration in minutes and seconds (MM:SS): ";
    std::getline(std::cin,buffer);
    
    length = splitString(buffer,':');
    auxSong.setLength(stoi(length[0]),stoi(length[1]));

    songTree.insertData(auxSong);

    std::cout << "Done! Song details: [" << auxSong << "]\nPress enter to continue.";
    std::cin.get();
}

void GUI::deleteSong (BinaryTree<Song>& songTree) {
    std::string name;
    Song deleteSong;
    std::cout << "Enter the name of the song: ";
    std::getline(std::cin,name);

    deleteSong.setName (name);
    
    songTree.deleteData(deleteSong);

    std::cout << "Done!\t";
    std::cout << "Press enter to continue\n";
    std::cin.get();
}

void GUI::searchSong (BinaryTree<Song>& songTree) {
    std::string name;
    Song searchSong;
    std::cout << "Enter the name of the song: ";
    std::getline(std::cin,name);

    searchSong.setName (name);

    std::cout << std::format ("Song Details: [{}]\n",songTree.findData(searchSong) == nullptr ? "Song not found" : 
                                                     std::format ("{}",songTree.findData(searchSong) -> getDataPtr() -> toString ()));
    std::cout << "Press enter to continue\n";
    std::cin.get();
}

void GUI::showSong (BinaryTree<Song>& songTree) {
    std::string option;
    int opt;
    std::cout << "How do you want to show the Songs: \n";
    std::cout << "1. Pre Order\n2. In order\n3.Post Order\n->";
    std::getline(std::cin,option);
    try {
        opt = std::stoi(option);
    }
    catch (std::invalid_argument){
        system(CLEAR);
        std::cout << "That is not a number!\t Press enter to continue...";
        std::cin.get ();
        return;
    }
    system(CLEAR);
    switch (opt) {
        case 1:
            songTree.parsePreOrder();
        break;
        case 2:
            songTree.parseInOrder ();
        break;
        case 3:
            songTree.parsePostOrder ();
        break;
        default:
            std::cout << "Invalid option";
        break;
    }
    std::cout << "\nPress enter to continue...";
    std::cin.get();
}

void GUI::loadSong (BinaryTree<Song>& songTree) {
    std::string filepath;
    std::cout << "Enter the complete filepath: ";
    std::getline (std::cin,filepath);
    songTree.loadFromFile(filepath);
}

void GUI::writeSong (BinaryTree<Song>& songTree) {
    std::string filepath;
    std::cout << "Enter the complete filepath: ";
    std::getline (std::cin,filepath);
    songTree.writeToFile(filepath);
}


std::vector<std::string> GUI::splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(input);
    std::string token;

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void GUI::exitProgram (bool& flag) {
    std::string answer;
    int ans;
    std::cout << "Are you sure?\n1. Yes\n->";\
    std::getline(std::cin,answer);
    try {
        ans = stoi(answer);
        if (ans == YES_ANSWER) {
            flag = false;
        }
    }
    catch (std::invalid_argument) {
        std::cout << "\nThat is not a number! Try again.";
        std::cout << "Press Enter to continue\n";       
        std::cin.get();
    }
}