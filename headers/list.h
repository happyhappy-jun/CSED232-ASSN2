//
// Created by Yoon Jun on 2020/04/14.
//

/*
 __   __  _______  __    _  _______  ______      _______  _______  ______   _______
|  | |  ||       ||  |  | ||       ||    _ |    |       ||       ||      | |       |
|  |_|  ||   _   ||   |_| ||   _   ||   | ||    |       ||   _   ||  _    ||    ___|
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

//Class for basic data structure
#ifndef ASSN2_LIST_H
#define ASSN2_LIST_H

#include <iostream>

template<class T>
class Node {
public:
    //Node member is set public for sake of easy linked list operation
    T value;
    Node<T> *next;

    Node() : value(nullptr), next(nullptr) {}

    //explicit constructor for node with data
    explicit Node(T data) : value(data), next(nullptr) {}

    //set next
    void setNext(Node<T> *n) {
        next = n;
    }

    //get next
    Node<T> *getNext() {
        return next;
    }

    //set value
    void setValue(T data) {
        value = data;
    }

    //set next as nullptr
    void setNull() {
        next = nullptr;
    }

    //get content of node
    T content() {
        return value;
    }

    //return reference value
    T &ref_content() {
        return value;
    }
};

//Node list for
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

    //return head of linked list
    Node<T> *begin() {
        return head;
    }

    //get size of list
    int len() {
        return size;
    }

    //append element at the back of list
    void push_back(const T &data) {
        //create new node
        auto *new_node = new Node<T>(data);
        new_node->setNext(nullptr);

        //set head
        auto *temp = head;
        //if list is empty
        if (head == nullptr) {
            head = new_node;
            size++;
            return;
        }
        //move ptr to need of node
        while (temp->next != nullptr)
            temp = temp->next;

        //append new node
        temp->next = new_node;
        //increase size
        size++;
    }

    //concat new node at the front of list
    void push_front(const T &data) {
        auto *new_node = new Node<T>(data);
        new_node->setNext(nullptr);

        if (head != nullptr)
            new_node->next = head;
        head = new_node;

    }

    //remove node from the linked list
    void removeNode(Node<T> *target) {
        Node<T> *temp = head;
        Node<T> *prev = nullptr;
        //free head
        if (head == target) {
            head = target->next;
            //free node if deleted
            delete target;
            size--;
            return;
        }
        //move ptr to target
        while (temp != target) {
            prev = temp;
            temp = temp->next;
        }
        //if temp is end exit
        if (temp == nullptr) return;

        //free target and concat rest of list
        if (prev != nullptr) {
            prev->next = temp->next;
            delete target;
            size--;
            return;
        }
    }

    //get node at the certain index, return nullptr if out-of-bound
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

    //free all element in the linked list
    void deleteList() {
        Node<T> *n;
        while (head != nullptr) {
            n = head;
            head = head->next;
            delete n;

        }
        head = nullptr;
    }

    Node<T> *search(const std::string &ID);
};


#endif //ASSN2_LIST_H
