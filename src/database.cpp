#include <iostream>
#include "headers/database.h"

void add_member(Database &db, const Member &m) {
    db.refMemberDB().push_back(m);
}

bool isFriend(List<Member> l, const std::string &ID) {
    Node<Member> *temp = l.begin();
    while (temp != nullptr) {
        if (temp->content().getID() == ID) return true;
        temp = temp->getNext();
    }
    return false;
}

Member sign_in(Database &db) {
    bool modeStatus = db.getModeStatus();
    std::string ID, name, birthday, password;
    std::cout << "ID: ";
    std::getline(modeStatus ? db.filebuf : std::cin, ID);
    db.addLog(ID);
    std::cout << "Name: ";
    std::getline(modeStatus ? db.filebuf : std::cin, name);
    db.addLog(name);
    std::cout << "Birthday: ";
    std::getline(modeStatus ? db.filebuf : std::cin, birthday);
    db.addLog(birthday);
    std::cout << "Password: ";
    std::getline(modeStatus ? db.filebuf : std::cin, password);
    db.addLog(password);

    Member temp = create_member(ID, name, birthday, password);
    return temp;
}

bool log_in(Database &db) {
    bool modeStatus = db.getModeStatus();
    std::string ID, password;
    std::cout << "ID: ";
    std::getline(modeStatus ? db.filebuf : std::cin, ID);
    db.addLog(ID);
    std::cout << "Password: ";
    std::getline(modeStatus ? db.filebuf : std::cin, password);
    db.addLog(password);
    return db.verify(ID, password);
}

void sign_out(Database &db) {
    db.setStatus(false);
}

void print_db(List<Member> member_db) {
    Node<Member> *current = member_db.begin();
    while (current != nullptr) {
        std::cout << "@" << current->content().getID() << std::endl;
        current = current->getNext();
    }
}

bool isExist(List<Member> l, const std::string &ID) {
    Node<Member> *temp = l.begin();
    while (temp != nullptr) {
        if (temp->content().getID() == ID) return true;
        temp = temp->getNext();
    }
    return false;
}

void addFriend(Member &m, const List<Member> &member_db, const std::string &ID) {
    Member target = Member::searchID(member_db, ID);
    if (target.getID() == ID) {
        std::cout << "Successfully added a friend" << std::endl;
        m.refFriendList().push_back(target);
    } else {
        std::cout << "User not found" << std::endl;
    }

}

void removeFriend(Member &m, const List<Member> &member_db, const std::string &name) {
    Node<Member> *target = m.getFriendList().search(name);
    if (target != nullptr) {
        m.refFriendList().removeNode(target);
        std::cout << "Successfully removed a  friend" << std::endl;
    } else {
        std::cout << "User not found" << std::endl;
    }
}

void Database::deletePost() {
    Node<Post> *cur = post_db.begin();
    while (cur != nullptr) {
        if (cur->content().getOwner().getID() == currentUser.getID()) {
            post_db.removeNode(cur);
        }
        cur->ref_content().deleteComment(currentUser);
        cur = cur->next;
    }
}

void Database::deleteFriendList() {
    Node<Member> *cur = member_db.begin();
    while (cur != nullptr) {
        Node<Member> *friend_cur = cur->content().getFriendList().begin();
        while (friend_cur != nullptr) {
            if (friend_cur->content().getID() == currentUser.getID())
                cur->ref_content().refFriendList().removeNode(friend_cur);
            friend_cur = friend_cur->next;
        }
        if (cur->content().getID() == currentUser.getID())
            member_db.removeNode(cur);
        cur = cur->next;
    }
}


void likePost(Post &p, Member &m, Database &db) {
    bool modeStatus = db.getModeStatus();
    std::string s;
    Node<std::string> *cur = p.getLikeList().begin();
    while (cur != nullptr) {
        if (cur->content() == m.getID()) {
            std::cout << "You already Liked it!" << std::endl;
            return;
        }
        cur = cur->next;
    }
    std::cout << "Do you like it? (y/n): ";
    (modeStatus ? db.filebuf : std::cin).ignore();
    std::getline(modeStatus ? db.filebuf : std::cin, s);
    db.addLog(s);
    if (s == "y")
        p.refLikelist().push_back(m.getID());
}
