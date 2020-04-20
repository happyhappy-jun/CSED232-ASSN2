//
// Created by Yoon Jun on 2020/04/14.
//
#include "headers/member.h"
#include "headers/list.h"

#include <iostream>

Member create_member(const std::string &ID, const std::string &name, const std::string &birthday,
                     const std::string &password) {
    return Member(ID, name, birthday, password);
}

template<>
void List<Member>::push_back(const Member &data) {
    Node<Member> *current;
    auto *temp = new Node<Member>(data);
    temp->setNext(nullptr);
    if (head == nullptr) {
        head = temp;
        size++;
    } else if (head->content().getID().compare(temp->content().getID()) > 0) {
        temp->setNext(head);
        head = temp;
        size++;
    } else {
        current = head;
        while (current->getNext() != nullptr &&
               current->getNext()->content().getID().compare(temp->content().getID()) < 0) {
            current = current->getNext();
        }
        temp->setNext(current->getNext());
        current->setNext(temp);
        size++;
    }
}


Member Member::searchID(List<Member> member_db, const std::string& ID) {
    Node<Member> *temp = member_db.begin();
    while (temp != nullptr) {
        if (temp->content().getID() == ID) return temp->content();
        temp = temp->next;
    }
    return temp->content();
}
