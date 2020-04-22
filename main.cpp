#include <iostream>
#include "headers/menu.h"
#include "headers/database.h"


int main() {

//Defind menu tree with custom stack
    menu mainMenu("Main");
    menu signUp = mainMenu.subMenu("Sign up", 1);
    menu signIn = mainMenu.subMenu("Sign in", 2);
    menu friendMenu = signIn.subMenu("Friends", 21);
    menu addFriends = friendMenu.subMenu("Add friends", 211);
    menu deleteFriends = friendMenu.subMenu("Delete friends", 212);
    menu myFriends = friendMenu.subMenu("My friends", 213);
    menu previousMenuFriend = friendMenu.subMenu("Previous menu", 214);
    menu feedMenu = signIn.subMenu("Feed", 22);
    menu allFeed = feedMenu.subMenu("All Feed", 221);
    menu post = feedMenu.subMenu("Post", 222);
    menu myPosting = feedMenu.subMenu("My posting", 223);
    menu previousMenuFeed = feedMenu.subMenu("Previous Menu", 224);
    menu signOut = signIn.subMenu("Sign out", 23);
    menu deleteAccount = signIn.subMenu("Delete my account", 24);
    menu loadCommand = mainMenu.subMenu("Load Command", 3);
    menu exitProgram = mainMenu.subMenu("Exit Program", 4);

    Database mainDatabase;
    menuStack directory;
    //init tree by pushing root node
    directory.push(&mainMenu);
    int item=-2;
    //if tree popped all directory stop operation
    while (!directory.isEmpty()) {
        //current location
        menu *current = directory.top();
        //if command mode running and ifstream reached eof end command mode
        if (mainDatabase.getModeStatus() && mainDatabase.filebuf.eof())
            finishCommandMode(mainDatabase);
        std::cout << "==================================" << std::endl;
        std::cout << "          **  " << current->getName() << "  **  " << std::endl;
        std::cout << "==================================" << std::endl;
        if (mainDatabase.currentStatus() && current->getmenuID() == 2) mainDatabase.printUser();

        //print submenu
        for (int idx = 0; idx < 4; idx++) {
            std::cout << idx + 1 << ". " << current->getChild(idx)->getName() << std::endl;
        }

        std::string input;
        std::cout << "\n* Select Menu: ";
        std::getline(mainDatabase.getModeStatus() ? mainDatabase.filebuf : std::cin, input);

        //log input
        if (!mainDatabase.getModeStatus())
            mainDatabase.addLog(input);
        //try-catch stoi for potential invalid input;
        try {
            item = std::stoi(input);
        } catch (std::invalid_argument &e) {
            std::cout << "Invalid" << std::endl;
            continue;
        }

        //if integer format if invalid
        if (!(item == -1 || (item <= 4 && item >= 1))) {
            std::cout << "Invalid" << std::endl;
            continue;
        }

        if (item == -1) {
            std::cout << "Returning previous menu" << std::endl;
            directory.pop();
            continue;
        }

        //pass to function handler
        function_handler(mainDatabase, directory, current->getChild(item - 1));
        std::cout << std::endl;
    }
}