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
        std::cout << "1. Add Song\n2. Delete Song\n3. Link Songs\n4. Unlink Songs\n";
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
            system(CLEAR);
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
                    writeGraph(songs);
                break;
                case load_from_file:
                    loadGraph(songs);
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

void GUI::addSong (Graph<Song>& songGraph) {
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

    std::cout << "Enter the name of the Node: ";
    std::getline(std::cin, buffer);
    
    songGraph.push(buffer,auxSong);

    std::cout << "Done! Song details: [" << auxSong << "] " << " Node name: [" << buffer << "]\nPress enter to continue.";
    std::cin.get();
}

void GUI::linkSongs (Graph<Song>& songGraph) {
    std::string buffer;
    size_t weight;
    Vertex<Song> *i = songGraph.getFirstVtx(),
                 *connectVtx = nullptr,
                 *availableVtx = nullptr;

    std::cout << "Nodes: \n";
    printGraph(songGraph);
    
    std::cout << "Enter the name of the node you want to link: ";
    std::getline (std::cin, buffer);

    while (i != nullptr and buffer != i -> getName()) {
        i = i -> getNextVtx();
    }

    connectVtx = i;
    i = songGraph.getFirstVtx();

    if (connectVtx == nullptr) {
        std::cout << "Invalid name. Press Enter to continue...";
        std::getchar();
        return;
    }

    system(CLEAR);
    std::cout << "Available Nodes: \n";
    printAvailableNodes(songGraph,connectVtx);

    std::cout << "Enter the name of the node you want to link: ";
    std::getline (std::cin, buffer);
    
    while (i != nullptr and buffer != i -> getName()) {
        i = i -> getNextVtx();
    }

    availableVtx = i;
    i = songGraph.getFirstVtx();

    if (availableVtx == nullptr) {
        std::cout << "Invalid name. Press Enter to continue...";
        std::getchar();
        return;
    }

    if (connectVtx->findConnection(availableVtx) != nullptr) {
        std::cout << "Already connected. Press Enter to continue...";
        std::getchar();
        return;
    }

    std::cout << "Enter the weight of the connection: ";
    std::getline(std::cin, buffer);

    try {
        weight = std::stoi(buffer);
    }
    catch (std::invalid_argument) {
        std::cout << "Not a number. Press Enter to continue...";
        std::getchar();
        return;
    }
    
    if (connectVtx == availableVtx) {
        songGraph.linkVtx(connectVtx,weight);
    }
    else {
        songGraph.linkVtx(connectVtx,availableVtx,weight);
    }
    system(CLEAR);
    std::cout << "Done! \n\nPress Enter to continue...";
    getchar();
}

void GUI::unlinkSongs (Graph<Song>& songGraph) {
    std::string buffer;
    Vertex<Song> *i = songGraph.getFirstVtx(),
                 *fstNode,
                 *scndNode;

    Vertex<Song>::EdgeNode *i_edge;

    std::cout << "Nodes: \n";
    printGraph(songGraph);
    std::cout << "Enter the name of the first node: ";
    std::getline(std::cin,buffer);

    while (i != nullptr and buffer != i -> getName()) {
        i = i -> getNextVtx();
    }

    fstNode = i;
    i = songGraph.getFirstVtx();

    if (fstNode == nullptr) {
        std::cout << "Invalid name. Press Enter to continue...";
        std::getchar();
        return;
    }
    
    std::cout << "Connected Nodes: \n";
    printConnections(fstNode);

    std::cout << "Enter the name of the second node: ";
    std::getline(std::cin,buffer);

    i_edge = fstNode->getfirstConnection();
    while (i_edge != nullptr and i_edge -> getVertex() -> getName() != buffer) {
        i_edge = i_edge -> getNxtNode();
    }

    if (i_edge == nullptr) {
        std::cout << "Not Connected. Press Enter to continue...";
        std::getchar();
        return;
    }

    scndNode = i_edge -> getVertex();

    if (scndNode == fstNode) {
        songGraph.unlinkVtx(fstNode);
    }
    else {
        songGraph.unlinkVtx(scndNode,fstNode);
    }
    system(CLEAR);
    std::cout << "Done! \n\nPress Enter to continue...";
    getchar();
}
void GUI::deleteSong (Graph<Song>& songGraph) {
    std::string buffer;
    Vertex<Song> *i = songGraph.getFirstVtx();

    std::cout << "Nodes:\n";
    printGraph(songGraph);

    std::cout << "Enter the name of the node you want deleted: ";
    std::getline(std::cin,buffer);

    while (i != nullptr and buffer != i -> getName()) {
        i -> getNextVtx();
    }

    if (i == nullptr) {
        std::cout << "Invalid name. Press Enter to continue...";
        std::getchar();
        return;
    }

    songGraph.deleteVtx(i);

    system(CLEAR);
    std::cout << "Done! \n\nPress Enter to continue...";
    getchar();
}
void GUI::showConnections (Graph<Song>&songGraph) {
    std::string buffer;
    Vertex<Song> *i = songGraph.getFirstVtx();

    std::cout << "Nodes: \n";
    printGraph(songGraph);

    std::cout << "Enter the name of the Node: ";
    std::getline (std::cin, buffer);

    while (i != nullptr and buffer != i -> getName()) {
        i = i -> getNextVtx();
    }

    if (i == nullptr) {
        std::cout << "Invalid Name. Press Enter to continue...";
        getchar();
        return;
    }
    system(CLEAR);
    std::cout << std::format("Node [{}] connections: \n",i -> getName());
    printConnections(i);
    std::cout << "\nPress Enter to continue...";
    getchar();
}
void GUI::showSong (Graph<Song>&songGraph) {
    std::string buffer;
    Vertex<Song> *i = songGraph.getFirstVtx();

    std::cout << "Enter the name of the song: ";
    std::getline(std::cin, buffer);

    while (i != nullptr and i -> getData().getName() != buffer) {
        i = i -> getNextVtx();
    }

    if (i == nullptr) {
        std::cout << "Song Not found\n";
    }
    else {
        std::cout << std::format ("Song Data: [{}]\n", i -> getData().toString()); 
    }
    std::cout << "Press Enter to continue...";
    getchar();

}
void GUI::loadGraph (Graph<Song>&songGraph) {
    songGraph.loadFile("file01.txt");
}
void GUI::writeGraph (Graph<Song>&songGraph) {
    songGraph.writeFile("file01.txt");
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

std::vector<std::string> GUI::splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(input);
    std::string token;

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void GUI::printGraph (const Graph<Song>& songGraph) {
    Vertex<Song> *i = songGraph.getFirstVtx();
    while (i != nullptr) {
        std::cout << std::format ("Name: [{}]\tData: [{}]\n",i -> getName(), i -> getData().toString());
        i = i -> getNextVtx();
    }
}

void GUI::printAvailableNodes (const Graph<Song>& graph, Vertex<Song>* node) {
    Vertex<Song> *i = graph.getFirstVtx();

    while (i != nullptr) {
        if (node->findConnection(i) == nullptr) {
            std::cout << std::format ("Name: [{}]\tData: [{}]\n",i -> getName(), i -> getData().toString());
        }
        i = i -> getNextVtx();
    }
}

void GUI::printConnections (Vertex<Song>* node) {
    Vertex<Song>::EdgeNode *i = node -> getfirstConnection();
    while (i != nullptr) {
        std::cout << std::format ("Name: [{}]\tData: [{}]\n", i -> getVertex() -> getName(),i -> getVertex() -> getData().toString());
        i = i -> getNxtNode();
    }
}