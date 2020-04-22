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
#ifndef ASSN2_MEMBER_H
#define ASSN2_MEMBER_H

#include <iostream>
#include "list.h"

class Member {
private:
    std::string ID;
    std::string name;
    std::string birthday;
    std::size_t password;
    List<Member> friend_list;
public:
    Member() = default;

    Member(std::string ID, std::string name, std::string birthday,
           std::size_t password) : ID(std::move(ID)), name(std::move(name)), birthday(std::move(birthday)),
                                   password(password) {};

    ~Member() = default;

    //get Member data
    std::string getID() {
        return ID;
    }

    std::string getName() {
        return name;
    }

    std::string getBirthday() {
        return birthday;
    }

    std::size_t getPassword() {
        return password;
    }

    List<Member> getFriendList() {
        return friend_list;
    }

    List<Member> &refFriendList() {
        List<Member> &l = friend_list;
        return l;
    }
    //end of getting member data

    void deleteFriendlist(){
        friend_list.deleteList();
    }
    static Member searchID(List<Member> member_db, const std::string& ID);
};

//Custom error for SearchUser cannot find target user
//the return type was Member instance for use of try-catch was inevitable
struct UserAlreadyExist : public std::exception
{
    const char * what () const noexcept override
    {
        return "UserAlreadyExist";
    }
};

template<>
void List<Member>::push_back(const Member &data);

bool isFriend(List<Member> l, const std::string& ID);

bool isMemberExist(List<Member> l, const std::string& ID);

void printMemberDB(List<Member> member_db);

#endif //ASSN2_MEMBER_H
