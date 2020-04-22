/*
 __   __  _______  __    _  _______  ______      _______  _______  ______   _______
|  | |  ||       ||  |  | ||       ||    _ |    |   _   ||       ||      | |       |
|  |_|  ||   _   ||   |_| ||   _   ||   | ||    |  | |  ||   _   ||  _    ||    ___|
|       ||  | |  ||       ||  | |  ||   |_||_   |       ||  | |  || | |   ||   |___
|       ||  |_|  ||  _    ||  |_|  ||    __  |  |      _||  |_|  || |_|   ||    ___|
|   _   ||       || | |   ||       ||   |  | |  |     |_ |       ||       ||   |___
|__| |__||_______||_|  |__||_______||___|  |_|  |_______||_______||______| |_______|


+==================================================================================+
|                                                                                  |
|       I completed this programming task without the improper help of others.     |
|                                                                                  |
+==================================================================================+
 */


#include <iostream>
#include "headers/database.h"

void add_member(Database &db, const Member &m) {
    //push back member to DB
    db.refMemberDB().push_back(m);
}

//check member with @ID is in list @l
bool isFriend(List<Member> l, const std::string &ID) {
    Node<Member> *temp = l.begin();
    //looo_ooop through list
    //loop through list
    while (temp != nullptr) {
        //if found return ture
        if (temp->content().getID() == ID) return true;
        temp = temp->getNext();
    }
//    else return false
    return false;
}

Member sign_in(Database &db) {
    bool modeStatus = db.getModeStatus();
    std::string ID, name, birthday, password;
    std::cout << "ID: ";
    //read line for target buffer
    std::getline(modeStatus ? db.filebuf : std::cin, ID);
    //if not command mode log input
    if (!modeStatus)
        db.addLog(ID);
    std::cout << "Name: ";
    std::getline(modeStatus ? db.filebuf : std::cin, name);
    if (!modeStatus)
        db.addLog(name);
    std::cout << "Birthday: ";
    std::getline(modeStatus ? db.filebuf : std::cin, birthday);
    if (!modeStatus)
        db.addLog(birthday);
    std::cout << "Password: ";
    std::getline(modeStatus ? db.filebuf : std::cin, password);
    if (!modeStatus)
        db.addLog(password);

    bool check = false;
    Node<Member> *t = db.getMemberDB().begin();
    while (t != nullptr) {
        if (t->content().getID() == ID) {
            check = true;
            break;
        }
        t = t->next;
    }
    if (check) {
        //if user is not found raise exception
        throw UserAlreadyExist();
    }
    //hash password with MURMUR hashing funcion in libstd++
    Member temp = create_member(ID, name, birthday, std::hash<std::string>{}(password));
    return temp;
}

bool log_in(Database &db) {
    bool modeStatus = db.getModeStatus();
    std::string ID, password;
    std::cout << "ID: ";
    std::getline(modeStatus ? db.filebuf : std::cin, ID);
    if (!modeStatus)
        db.addLog(ID);
    std::cout << "Password: ";
    std::getline(modeStatus ? db.filebuf : std::cin, password);
    if (!modeStatus)
        db.addLog(password);
    //get input from input stream and pass to verify function to check validity of user
    return db.verify(ID, password);
}

//change current login status
void sign_out(Database &db) {
    db.setStatus(false);
}

//print member list (used for print friend list)
void printMemberDB(List<Member> member_db) {
    Node<Member> *current = member_db.begin();
    while (current != nullptr) {
        std::cout << "@" << current->content().getID() << std::endl;
        current = current->getNext();
    }
}

//check Member with @ID exist in the list @l
bool isMemberExist(List<Member> l, const std::string &ID) {
    Node<Member> *temp = l.begin();
    while (temp != nullptr) {
        if (temp->content().getID() == ID) return true;
        temp = temp->getNext();
    }
    return false;
}

//add friend with @ID from member db to Member @m
void addFriend(Member &m, const List<Member> &member_db, const std::string &ID) {
    Member target = Member::searchID(member_db, ID);
    if (target.getID() == ID) {
        std::cout << "Successfully added a friend" << std::endl;
        m.refFriendList().push_back(target);
    } else {
        std::cout << "User not found" << std::endl;
    }

}
//add friend with @ID from member db to Member @m
void removeFriend(Member &m, const List<Member> &member_db, const std::string &ID) {
    Node<Member> *target = m.getFriendList().search(ID);
    if (target != nullptr) {
        m.refFriendList().removeNode(target);
        std::cout << "Successfully removed a  friend" << std::endl;
    } else {
        std::cout << "User not found" << std::endl;
    }
}

//delete post of current User
void Database::deletePost() {
    Node<Post> *cur = post_db.begin();
    while (cur != nullptr) {
        if (cur->content().getOwner().getID() == currentUser.getID()) {
            //delete post of current user
            post_db.removeNode(cur);
        }
        //delete comment of current user from all post
        cur->ref_content().deleteComment(currentUser);
        cur = cur->next;
    }
}

void Database::deleteFriendList() {
    Node<Member> *cur = member_db.begin();
    Node<Member> *n;
    while (cur != nullptr) {
        Node<Member> *friend_cur = cur->content().getFriendList().begin();
        while (friend_cur != nullptr) {
            //remove current user from friend's list
            if (friend_cur->content().getID() == currentUser.getID())
                cur->ref_content().refFriendList().removeNode(friend_cur);
            friend_cur = friend_cur->next;
        }
        //remove node from member db and connect rest of db
        if (cur->content().getID() == currentUser.getID()) {
            n = cur->next;
            member_db.removeNode(cur);
            cur = n;
        } else {
            cur = cur->next;
        }
    }
}


void likePost(Post &p, Member &m, Database &db) {
    bool modeStatus = db.getModeStatus();
    std::string s;
    Node<std::string> *cur = p.getLikeList().begin();
    while (cur != nullptr) {
        //check is user already liked
        if (cur->content() == m.getID()) {
            std::cout << "You already Liked it!" << std::endl;
            return;
        }
        cur = cur->next;
    }
    std::cout << "Do you like it? (y/n): ";
    std::getline(modeStatus ? db.filebuf : std::cin, s);
    if (!modeStatus)
        db.addLog(s);
    if (s == "y")
        p.refLikelist().push_back(m.getID());
    else if (s== "n")
        std::cout << "Choose N\n[.]Returing Previous Menu" << std::endl;
    else
        std::cout << "Invalid Input\n[.]Returing Previous Menu" << std::endl;
}
