//
// Created by Yoon Jun on 2020/04/14.
//

#ifndef ASSN2_LIST_H
#define ASSN2_LIST_H

#include <iostream>

template<class T>
class Node {
public:
    T value;
    Node<T> *next;

    Node() : value(nullptr), next(nullptr) {}

    explicit Node(T data) : value(data), next(nullptr) {}

    void setNext(Node<T> *n) {
        next = n;
    }

    Node<T> *getNext() {
        return next;
    }

    void setValue(T data) {
        value = data;
    }

    void setNull() {
        next = nullptr;
    }

    T content() {
        return value;
    }

    T &ref_content() {
        return value;
    }
};

template<class T>
class List {

public:
    Node<T> *head;
    int size;

    List() {
        head = nullptr;
        size = 0;
    }

    ~List() = default;;

    Node<T> *begin() {
        return head;
    }

    int len() {
        return size;
    }

    void push_back(const T &data) {
        auto *new_node = new Node<T>(data);
        new_node->setNext(nullptr);

        auto *temp = head;
        if (head == nullptr) {
            head = new_node;
            size++;
            return;
        }
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = new_node;
        size++;
    }

    void push_front(const T &data) {
        auto *new_node = new Node<T>(data);
        new_node->setNext(nullptr);

        if (head != nullptr)
            new_node->next = head;
        head = new_node;

    }

    void removeNode(Node<T> *target) {
        Node<T> *temp = head;
        Node<T> *prev = nullptr;
        if (head == target) {
            head = target->next;
            delete target;
            size--;
            return;
        }
        while (temp != target) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr) return;
        if(prev!=nullptr) {
            prev->next = temp->next;
            delete target;
            size--;
            return;
        }
    }

    Node<T> *search() {};

    Node<T> *search(const std::string &ID);

    Node<T> *at(int idx) {
        int cnt = 0;
        Node<T> *temp = head;
        if (idx < size) {
            while (temp->getNext() != nullptr && cnt < idx) {
                temp = temp->getNext();
                cnt++;
            }
            return temp;
        } else {
            return nullptr;
        }
    }

    void deleteList() {
        Node<T> *cur = head;
        Node<T> *n;
        while (cur != nullptr) {
            n = cur->next;
            delete cur;
            cur = n;
        }
        head = nullptr;
    }
};


#endif //ASSN2_LIST_H
