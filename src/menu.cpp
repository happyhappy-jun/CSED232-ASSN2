#include <string>
#include <fstream>
#include <iostream>
#include "headers/list.h"
#include "headers/menu.h"
#include "headers/database.h"

int function_handler(Database &mainDatabase, menuStack &s, menu *menuItem) {
    int id = menuItem->getmenuID();
    if (menuItem->has_children()) {
        s.push(menuItem);
        //return 0;
    }
    if (id == 224 or id == 214) {
        s.pop();
        return 0;
    }
    if (id == 1) {
        add_member(mainDatabase, sign_in(mainDatabase));
        return 0;
    }
    if (id == 2) {
        if (!mainDatabase.currentStatus()) {
            if (log_in(mainDatabase)) {
                std::cout << "Success Logging in!" << std::endl;
                menuItem->changeName("My page");
            } else {
                std::cout << "Invalid Account" << std::endl;
                std::cout << "Returning previous menu" << std::endl;
                s.pop();
            }
        } else {
            menuItem->changeName("Sign in");
        }
        return 0;
    }
    if (id == 23) {
        sign_out(mainDatabase);
        s.top()->changeName("Sign in");
        s.pop();
        return 0;
    }
    if (id == 211) {
        addFriendWrapper(mainDatabase);
        return 0;
    }
    if (id == 212) {
        removeFriendWrapper(mainDatabase);
        return 0;
    }
    if (id == 213) {
        if (mainDatabase.refcurrentID().getFriendList().begin() == nullptr)
            std::cout << "Oops, You don't have friends... Try hard!" << std::endl;
        else
            print_db(mainDatabase.refcurrentID().getFriendList());
    }

    if (id == 221)
        printFriendPostWrapper(mainDatabase);
    if (id == 222)
        addPostWrapper(mainDatabase);
    if (id == 223)
        printMyPostWrapper(mainDatabase);
    if (id == 24) {
        removeAccountWrapper(mainDatabase);
        sign_out(mainDatabase);
        s.top()->changeName("Sign in");
        s.pop();
    }
    if (id == 3) {
        loadCommandWrapper(mainDatabase);
        return 0;
    }
    if (id == 4) {
        exitProgram(mainDatabase);
        s.pop();
        return 0;
    }

    return 0;
}

void addFriendWrapper(Database &db) {
    bool modeStatus = db.getModeStatus();
    std::cout << "Input friend name: ";
    std::string friendID;
    std::getline(modeStatus ? db.filebuf : std::cin, friendID);
    db.addLog(friendID);
    if (isExist(db.getMemberDB(), friendID) && !isFriend(db.refcurrentID().getFriendList(), friendID))
        addFriend(db.refcurrentID(), db.getMemberDB(), friendID);
    else
        std::cout << "Invalid Friend!" << std::endl;
}

void removeFriendWrapper(Database &db) {
    bool modeStatus = db.getModeStatus();
    std::cout << "Input friend name: ";
    std::string friendName;
    std::getline(modeStatus ? db.filebuf : std::cin, friendName);
    db.addLog(friendName);
    if (isExist(db.getMemberDB(), friendName) && isFriend(db.refcurrentID().getFriendList(), friendName))
        removeFriend(db.refcurrentID(), db.getMemberDB(), friendName);
    else
        std::cout << "Invalid Friend!" << std::endl;
}


void addPostWrapper(Database &db) {
    bool modeStatus = db.getModeStatus();
    std::cout << "Write Post! \nPost: ";
    std::string content;
    //(modeStatus ? db.filebuf : std::cin).ignore();
    std::getline(modeStatus ? db.filebuf : std::cin, content);
    db.addLog(content);
    if (content.length() != 0)
        db.refPostDB().push_back(Post(db.refcurrentID(), content));
}

void printFriendPostWrapper(Database &db) {
    bool printed = db.printFriendPost();
    if (printed)
        writeCommentWrapper(db);
    else
        std::cout << "Nothing to Print" << std::endl;

}

void printMyPostWrapper(Database &db) {
    bool modeStatus = db.getModeStatus();
    bool printed = db.printMyPost();
    if (printed) {
        int idx = 0;
        int cnt = -1;
        std::string s, content;
        //Select index of Post
        std::cout << "Select Number: ";
        std::string line;
        std::getline(modeStatus ? db.filebuf : std::cin, line);
        db.addLog(line);
        if (line.length())
            idx = std::stoi(line);
        if (idx == -1)
            return;
        //Get selected post
        Node<Post> *current = db.refPostDB().begin();
        while (current != nullptr) {
            if (db.getCurrentUser().getID() == current->content().getOwner().getID()) {
                cnt++;
            }
            if (cnt == idx) break;
            current = current->next;
        }
        if (current != nullptr) {
            //print post and comment
            current->content().printPost();
            current->content().printComment();
            std::cout << "Enter -1 to exit: " << std::endl;
//            std::string line2;
            int i;
            (modeStatus ? db.filebuf : std::cin) >> i;
            (modeStatus ? db.filebuf : std::cin).ignore();
            db.addLog(std::to_string(i));
            if (i == -1) return;
        }

    } else {
        std::cout << "Nothing to Print" << std::endl;
    }
}


void writeCommentWrapper(Database &db) {
    bool modeStatus = db.getModeStatus();
    int idx = 0;
    int cnt = -1;
    std::string s, content;
    //Select index of Post
    std::cout << "Select Number: ";
    modeStatus ? db.filebuf : std::cin >> idx;
    if (idx == -1)
        return;
    //Get selected post
    Node<Post> *current = db.refPostDB().begin();
    while (current != nullptr) {
        if (isFriend(db.refcurrentID().getFriendList(), current->content().getOwner().getID())) {
            cnt++;
        }
        if (cnt == idx) break;
        current = current->next;
    }
    //print post and comment
    if (current != nullptr) {
        current->content().printPost();
        current->content().printComment();
        likePost(current->ref_content(), db.refcurrentID(), db);
        std::cout << "Reply: " << std::endl;
        (modeStatus ? db.filebuf : std::cin).ignore();
        std::getline(modeStatus ? db.filebuf : std::cin, content);
        db.addLog(content);
        if (content.length() != 0)
            current->ref_content().writeComment(db.refcurrentID(), content);
    } else {
        std::cout << "Nothing to Print" << std::endl;
    }
}

void removeAccountWrapper(Database &db) {
    std::cout << "[-]Deleting Account..." << std::endl;
    db.deletePost();
    db.deleteFriendList();
}

void loadCommandWrapper(Database &db) {
    std::cout << "[-]Swithcing to Command Mode..." << std::endl;
// /Users/unajun/Documents/Sophomore/CSED232/ASSN2/command.txt"
    if (std::fopen("command.txt", "r")) {
        db.startCommandMode();
        db.setBuffer("command.txt");
    } else {
        std::cout << "[x]command.txt doesn't exit!" << std::endl;
    }

}


void finishCommandMode(Database &db) {
    db.stopCommandMode();
    std::cout << "Returning to Stdin!" << std::endl;
    std::cin.clear();
    std::cin.sync();
}


void exitProgram(Database &db) {
    db.clear();
    std::ofstream logfile("command.txt");
    logfile << db.getLog();
    logfile.close();

}

