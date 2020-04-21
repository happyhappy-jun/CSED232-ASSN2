//
// Created by Yoon Jun on 2020/04/14.
//

#ifndef ASSN2_MEMBER_H
#define ASSN2_MEMBER_H

#include <iostream>
#include "list.h"

class Member {
private:
    std::string ID;
    std::string name;
    std::string birthday;
    std::string password;
    List<Member> friend_list;
public:
    Member() = default;

    Member(std::string ID, std::string name, std::string birthday,
           std::string password) : ID(std::move(ID)), name(std::move(name)), birthday(std::move(birthday)),
                                   password(std::move(password)) {};

    ~Member() = default;

    std::string getID() {
        return ID;
    }

    std::string getName() {
        return name;
    }

    std::string getBirthday() {
        return birthday;
    }

    std::string getPassword() {
        return password;
    }

    List<Member> getFriendList() {
        return friend_list;
    }

    List<Member> &refFriendList() {
        List<Member> &l = friend_list;
        return l;
    }
    void printUser() {
        std::cout << "@" << ID << " - " << name << " " << birthday << std::endl;
    }
    void deleteFriendlist(){
        friend_list.deleteList();
    }
    static Member searchID(List<Member> member_db, const std::string& ID);
};

template<>
void List<Member>::push_back(const Member &data);

bool isFriend(List<Member> l, const std::string& ID);

bool isExist(List<Member> l, const std::string& ID);

void print_db(List<Member> member_db);

#endif //ASSN2_MEMBER_H
