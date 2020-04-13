#include <iostream>
#include "menu.h"
#include "database.h"


int main(){
    menu mainMenu("Main");
    menu    signUp = mainMenu.subMenu("Sign up", 1);
    menu    signIn = mainMenu.subMenu("Sign in", 2);
    menu        friendMenu = signIn.subMenu("Friends", 21);
    menu            addFriends = friendMenu.subMenu("Add friends", 211);
    menu            deleteFriends = friendMenu.subMenu("Delete friends", 212);
    menu            myFriends = friendMenu.subMenu("My friends", 213);
    menu            previousMenuFriend = friendMenu.subMenu("Previous menu", 214);
    menu        feedMenu = signIn.subMenu("Feed",22);
    menu            allFeed = feedMenu.subMenu("All Feed",221);
    menu            post = feedMenu.subMenu("Post",222);
    menu            myPosting = feedMenu.subMenu("My posting",223);
    menu            previousMenuFeed = feedMenu.subMenu("Previous Menu",224);
    menu        signOut = signIn.subMenu("Sign out",23);
    menu        deleteAccount = signIn.subMenu("Delete my account",24);
    menu    loadCommand = mainMenu.subMenu("Load Command",3);
    menu    exitProgram = mainMenu.subMenu("Exit Program",4);

    Database mainDatabase;
    menuStack directory;
    directory.push(&mainMenu);

    while(!directory.isEmpty()){
        menu *current = directory.top();
        std::cout<< "==================================" <<std::endl;
        std::cout << "          **  " <<current->name << "  **  "<< std::endl;
        std::cout<< "==================================" <<std::endl;
        int i = 0;
        if(current->getmenuID()==2 && mainDatabase.currentStatus()) mainDatabase.printUser();
        for (int idx = 0; idx < 4; idx++){
            std::cout << idx+1 << ". " << current->children.at(idx)->name << std::endl;
        }
        std::string input;
        std::cout << "\n* Select Menu: ";
        std::cin >> input;
        std::cin.clear();

        int item = std::stoi(input);
        if(item == -1) directory.pop();
        else function_handler(mainDatabase, directory, current->children.at(item-1));
        std::cout <<std::endl;
    }
}