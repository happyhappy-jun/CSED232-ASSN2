//
// Created by Yoon Jun on 2020/04/15.
//

#include <iostream>
#include <headers/list.h>
#include <headers/member.h>

template <>
Node<Member> * List<Member>::search(const std::string &name){
    Node<Member> *temp = head;
    while(temp != nullptr){
        if(temp->content().getName()==name) return temp;
        temp  = temp ->next;
    }
    return nullptr;
}

