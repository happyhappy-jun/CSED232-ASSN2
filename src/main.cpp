#include <iostream>
#include <fstream>
#include "headers/menu.h"
#include "headers/database.h"


int main() {
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
    directory.push(&mainMenu);
    int item;
    while (!directory.isEmpty()) {
        menu *current = directory.top();
        if(mainDatabase.getModeStatus() && mainDatabase.filebuf.eof())
            finishCommandMode(mainDatabase);
        std::cout << "==================================" << std::endl;
        std::cout << "          **  " << current->getName() << "  **  " << std::endl;
        std::cout << "==================================" << std::endl;
        if (current->getmenuID() == 2 && mainDatabase.currentStatus()) mainDatabase.printUser();
        for (int idx = 0; idx < 4; idx++) {
            std::cout << idx + 1 << ". " << current->getChild(idx)->getName() << std::endl;
        }

        std::string input;

        std::cout << "\n* Select Menu: ";
        std::getline(mainDatabase.getModeStatus() ? mainDatabase.filebuf : std::cin, input);
        mainDatabase.addLog(input);
        std::cout <<input <<std::endl;
        item = std::stoi(input);
        if(!(item>=1 && item <=4)) continue;
        if (item == -1) directory.pop();
        else function_handler(mainDatabase, directory, current->getChild(item - 1));
        std::cout << std::endl;
    }
}