//
// Created by Yoon Jun on 2020/04/14.
//

#include "headers/post.h"


void Post::likePost(Member &m) {
    std::string s;
    Node<std::string> *cur = likeList.begin();
    while (cur != nullptr) {
        if (cur->content()==m.getName()) {
            std::cout << "You already Liked it!" << std::endl;
            return;
        }
        cur = cur->next;
    }
    std::cout << "Do you like it? (y/n): ";
    std::cin >> s;
    if (s == "y")
        likeList.push_back(m.getName());
}

void Post::printPost() {
    std::cout << "@" << owner.getName() << "(Like: " << likeList.size << ")" << std::endl;
    std::cout << " - " << content << std::endl;
}

void Post::writeComment(Member &m, std::string &c) {
    commentList.push_front(Comment(m, c));
}

void Post::printComment() {
    Node<Comment> *cur = commentList.begin();
    while (cur != nullptr) {
        std::cout << "@" << cur->content().getOwner().getName() << " - " << cur->content().getContent() << std::endl;
        cur = cur->next;
    }
}

void Post::deleteComment(Member &m) {
    Node<Comment> *cur = commentList.begin();
    while (cur != nullptr) {
        if (m.getName() == cur->content().getOwner().getName()) {
            commentList.removeNode(cur);
            cur = commentList.begin();
            continue;
        }
        cur = cur->next;
    }
}

template<>
void List<Post>::push_back(const Post &data) {
    Node<Post> *current;
    auto *temp = new Node<Post>(data);
    temp->setNext(nullptr);
    if (head == nullptr) {
        head = temp;
        size++;
    } else if (head->content().getTime() < temp->content().getTime()) {
        temp->setNext(head);
        head = temp;
        size++;
    } else {
        current = head;
        while (current->getNext() != nullptr &&
               current->getNext()->content().getTime() > temp->content().getTime()) {
            current = current->getNext();
        }
        temp->setNext(current->getNext());
        current->setNext(temp);
        size++;
    }
}
