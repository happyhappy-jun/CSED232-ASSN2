#include <iostream>
#include "database.h"

Member create_member(const std::string ID, const std::string name, const std::string birthday,
                     const std::string passward) {
    return Member(ID, name, birthday, passward);
}

void add_member(Database &db, Member m) {
    db.member_db.push_back(m);
}

Member::Member(const std::string ID, const std::string name, const std::string birthday, const std::string passward)
        : ID(ID), name(name), birthday(birthday), passward(passward) {
}

template<>
void List<Member>::push_back(Member data) {
    Node<Member> *current;
    Node<Member> *temp = new Node<Member>(data);
    temp->setNext(NULL);
    if (head == NULL) {
        head = temp;
        tail = head;
        size++;
    } else if (head->content().getID().compare(temp->content().getID()) > 0) {
        temp->setNext(head);
        tail = temp;
        head = temp;
        size++;
    } else {
        current = head;
        while (current->getNext() != NULL &&
               current->getNext()->content().getID().compare(temp->content().getID()) < 0) {
            current = current->getNext();
        }
        temp->setNext(current->getNext());
        current->setNext(temp);
        size++;
    }
}


void Member::addFriend(List<Member> member_db, std::string name) {
    Member target = searchUser(member_db, name);
    if (target.name == name){
        std::cout << "Successfully added a friend" << std::endl;
        friend_list.push_back(target);}
    else {
        std::cout << "User not found" << std::endl;
    }

}

Member Member::searchUser(List<Member> member_db, std::string name) {
    Node<Member> *temp = member_db.begin();
    while (temp != NULL) {
        if (temp->content().getName() == name) return temp->content();
        temp = temp->getNext();
    }
}

Member sign_in() {
    std::string ID, name, birthday, password;
    std::cout << "ID: ";
    std::cin >> ID;
    std::cout << "Name: ";
    std::cin >> name;
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
    if (db.verify(ID, password)) {
        return true;
    } else {
        return false;
    }
}

void sign_out(Database &db) {
    db.status = false;
}

void print_db(List<Member> member_db) {
    Node<Member> *current = member_db.begin();
    while(current!= NULL){
        std::cout << "@" << current->content().getID() << std::endl;
        current = current->getNext();
    }
}
