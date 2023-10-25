#include "../include/gui.hpp"


GUI::GUI () {}

void GUI::run (List<Song>& list) {
    menu (list);
}

void GUI::menu (List<Song>& songList) {
    
    bool flag = true;
    std::string option;
    int opt;
    
    while (flag) {
        system(CLEAR);
        std::cout << "Welcome to the {} list handler \nSelect one of the following options\n";

        std::cout << "1. Add Song\n2. Delete Song\n3. Search song\n4. Show Songs\n5. Load songs from file\n6. Write  songs to file\n7. Exit Program\n-> ";
        std::getline(std::cin,option);
        try {
            opt = std::stoi(option);
            system(CLEAR);
            switch (opt) {
                case Options::add_song:
                    addSong(songList);
                    break;

                case Options::delete_song:
                    deleteSong(songList);
                    break;

                case Options::search_song:
                    searchSong(songList);
                    break;\

                case Options::show_songs:
                    showSong(songList);
                    break;
                case Options::load_songs:
                    loadSong(songList);
                    break;
                case Options::write_songs:
                    writeSong(songList);
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
    songList.~List();
}

void GUI::addSong (List<Song>& list) {
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

    list.push(auxSong);

    std::cout << "Done! Song details: [" << auxSong << "]\nPress enter to continue.";
    std::cin.get();
}

void GUI::deleteSong (List<Song>& list) {
    std::string name;
    Song deletedSong;
    List<Song>::Node *iterator = list.getFirstPos();
    std::cout << "Enter the name of the song: ";
    std::getline(std::cin,name);

    while (iterator != nullptr) {
        if (iterator -> getData().getName() == name){
            deletedSong = iterator->getData();
            list.deleteData(iterator);
            std::cout << "Done!";
            break;
        }
        iterator = iterator -> getNextPtr();
    }
    std::cout << "Press enter to continue\n";
    std::cin.get();
}

void GUI::searchSong (List<Song>& list) {
    List<Song>::Node *iterator = list.getFirstPos();
    std::string name;
    std::cout << "Enter the name of the song: ";
    std::getline(std::cin,name);
    while (iterator != nullptr) {
        if (iterator -> getData().getName() == name) {
            std::cout << "Song details: [" << iterator->getData() << "]\n";
        }
    }
    std::cout << "Press enter to continue\n";
    std::cin.get();
}

void GUI::showSong (List<Song>& list) {
    List<Song>::Node *iterator = list.getFirstPos();

    while (iterator != nullptr) {
        std::cout << iterator -> getData() << "\n";
        iterator = iterator ->  getNextPtr();
    }

    std::cout << "\n\nPress enter to continue\n";
    std::cin.get();
}

void GUI::loadSong (List<Song>& list) {
    std::string fileName;
    Song bufferSong;
    std::cout << "Enter the name of the file: ";
    std::getline(std::cin,fileName);

    std::fstream file ("file01.txt",std::ios::in);

    if (file.is_open()) {
        list.clearList();
        while(file >> bufferSong) {
            list.push(bufferSong);
        }
        file.close();
        std::cout << "Done!\n";
    }
    else {
        std::cout << "Could not open file\n";
    }
    std::cout << "\n\nPress enter to continue\n";
    std::cin.get();
}

void GUI::writeSong (List<Song>& list) {
    std::string fileName;
    List<Song>::Node *iterator = list.getFirstPos();
    
    std::cout << "Enter the name of the file: ";
    std::getline(std::cin,fileName);

    std::fstream file ("file01.txt",std::ios::out);
    
    
    if (file.is_open()) {
        while (iterator != nullptr) {
            file << iterator -> getData();
            iterator = iterator -> getNextPtr();
        }
            file.close();
            std::cout << "Done!\n";
    }
    else {
        std::cout << "Could not open file\n";
    }

    std::cout << "\n\nPress enter to continue\n";
    std::cin.get();
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

void GUI::stop (List<Song>&) {}

std::vector<std::string> GUI::splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(input);
    std::string token;

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}