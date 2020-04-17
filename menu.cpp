#include <string>
#include <list>
#include "headers/menu.h"
#include "headers/database.h"

int function_handler(Database &mainDatabase, menuStack &s, menu *menuItem) {
    int id = menuItem->getmenuID();
    if (menuItem->has_children()) {
        s.push(menuItem);
        //return 0;
    }
    if (id == 224 or id == 214 or id == 4) {
        s.pop();
        return 0;
    }
    if (id == 1) {
        add_member(mainDatabase, sign_in());
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
        if (mainDatabase.refcurrentUser().getFriendList().begin() == nullptr)
            std::cout << "Oops, You don't have friends... Try hard!" << std::endl;
        else
            print_db(mainDatabase.refcurrentUser().getFriendList());
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

    return 0;
}

void addFriendWrapper(Database &db) {
    std::cout << "Input friend name: ";
    std::string friendName;
    std::cin >> friendName;
    if (isExist(db.getMemberDB(), friendName) && !isFriend(db.refcurrentUser().getFriendList(), friendName))
        addFriend(db.refcurrentUser(), db.getMemberDB(), friendName);
    else
        std::cout << "Invalid Friend!" << std::endl;
}

void removeFriendWrapper(Database &db) {
    std::cout << "Input friend name: ";
    std::string friendName;
    std::cin >> friendName;
    if (isExist(db.getMemberDB(), friendName) && isFriend(db.refcurrentUser().getFriendList(), friendName))
        removeFriend(db.refcurrentUser(), db.getMemberDB(), friendName);
    else
        std::cout << "Invalid Friend!" << std::endl;
}


void addPostWrapper(Database &db) {
    std::cout << "Write Post! \nPost: ";
    std::string content;
    std::cin.ignore();
    std::getline(std::cin, content);
    if (content.length() != 0)
        db.refPostDB().push_back(Post(db.refcurrentUser(), content));
}

void printFriendPostWrapper(Database &db) {
    bool printed = db.printFriendPost();
    if (printed)
        writeCommentWrapper(db);
    else
        std::cout << "Nothing to Print" << std::endl;

}

void printMyPostWrapper(Database &db) {
    bool printed = db.printMyPost();
    if (printed) {
        int idx, cnt = -1;
        std::string s, content;
        //Select index of Post
        std::cout << "Select Number: ";
        std::cin >> idx;
        if (idx == -1)
            return;
        //Get selected post
        Node<Post> *current = db.refPostDB().begin();
        while (current != nullptr) {
            if (db.getCurrentUser().getName() == current->content().getOwner().getName()) {
                cnt++;
            }
            if (cnt == idx) break;
            current = current->next;
        }
        if (current != nullptr) {
            //print post and comment
            current->content().printPost();
            current->content().printComment();
            std::cout << "Enter -1 to exit: ";
            std::cin >> idx;
            if (idx == -1)
                return;
        }
    } else {
        std::cout << "Nothing to Print" << std::endl;
    }
}


void writeCommentWrapper(Database &db) {
    int idx, cnt = -1;
    std::string s, content;
    //Select index of Post
    std::cout << "Select Number: ";
    std::cin >> idx;
    if (idx == -1)
        return;
    //Get selected post
    Node<Post> *current = db.refPostDB().begin();
    while (current != nullptr) {
        if (isFriend(db.refcurrentUser().getFriendList(), current->content().getOwner().getName())) {
            cnt++;
        }
        if (cnt == idx) break;
        current = current->next;
    }
    //print post and comment
    if (current != nullptr) {
        current->content().printPost();
        current->content().printComment();
        current->ref_content().likePost(db.refcurrentUser());
        std::cout << "Reply: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, content);
        if (content.length() != 0)
            current->ref_content().writeComment(db.refcurrentUser(), content);
    } else {
        std::cout << "Nothing to Print" << std::endl;
    }
}

void removeAccountWrapper(Database &db) {
    std::cout << "Deleting Account..." << std::endl;
    db.deletePost();
    db.deleteFriendList();
}
