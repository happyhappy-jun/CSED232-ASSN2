#include <iostream>
#include <utility>
#include "headers/database.h"

void add_member(Database &db, const Member &m) {
    db.refMemberDB().push_back(m);
}

bool isFriend(List<Member> l, const std::string& name) {
    Node<Member> *temp = l.begin();
    while (temp != nullptr) {
        if (temp->content().getName() == name) return true;
        temp = temp->getNext();
    }
    return false;
}

Member sign_in() {
    std::string ID, name, birthday, password;
    std::cout << "ID: ";
    std::cin >> ID;
    std::cout << "Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Birthday: ";
    std::cin >> birthday;
    std::cout << "Password: ";
    std::cin >> password;

    Member temp = create_member(ID, name, birthday, password);
    return temp;
}

bool log_in(Database &db) {
    std::string ID, password;
    std::cout << "ID: ";
    std::cin >> ID;
    std::cout << "Password: ";
    std::cin >> password;
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

bool isExist(List<Member> l, const std::string& name) {
    Node<Member> *temp = l.begin();
    while (temp != nullptr) {
        if (temp->content().getName() == name) return true;
        temp = temp->getNext();
    }
    return false;
}

void addFriend(Member &m, const List<Member>& member_db, const std::string& name) {
    Member target = Member::searchUser(member_db, name);
    if (target.getName() == name) {
        std::cout << "Successfully added a friend" << std::endl;
        m.refFriendList().push_back(target);
    } else {
        std::cout << "User not found" << std::endl;
    }

}

void removeFriend(Member &m, const List<Member>& member_db, const std::string& name) {
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
        if (cur->content().getOwner().getName() == currentUser.getName()) {
            post_db.removeNode(cur);
        }
        cur->ref_content().deleteComment(currentUser);
        cur = cur->next;
    }
}

void Database::deleteFriendList() {
    Node<Member> *cur = member_db.begin();
    while (cur != nullptr) {
        if (cur->content().getName()==currentUser.getName())
            member_db.removeNode(cur);
        Node<Member> *friend_cur = cur->content().getFriendList().begin();
        while (friend_cur != nullptr) {
            if (friend_cur->content().getName() == currentUser.getName())
                cur->ref_content().refFriendList().removeNode(friend_cur);
            friend_cur = friend_cur->next;
        }
        cur = cur->next;
    }
}

