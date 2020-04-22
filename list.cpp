//
// Created by Yoon Jun on 2020/04/15.
//
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
#include "headers/list.h"
#include "headers/member.h"

//search function for Member list
template <>
Node<Member> * List<Member>::search(const std::string &ID){
    Node<Member> *temp = head;
    while(temp != nullptr){
        if(temp->content().getID() == ID) return temp;
        temp  = temp ->next;
    }
    return nullptr;
}

