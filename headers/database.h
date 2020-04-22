
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

#ifndef DATABASE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define DATABASE_H

#include <string>
#include <iostream>
#include <fstream>
#include "member.h"
#include "post.h"
#include "list.h"


class Database {
private:
    List<Member> member_db;
    List<Post> post_db;
    bool status = false;
    bool commandMode = false;
    Member currentUser;
    std::string log;

public:
    //std::ifstream doesn't have copy operator, so I make is public
    std::ifstream filebuf;

    Database() {
        status = false;
        commandMode = false;
        log = "";
    };

    ~Database() = default;;

    bool getStatus() {
        return status;
    }

    void setStatus(bool i) {
        status = i;
    }

    Member getCurrentUser() {
        return currentUser;
    }

    //add string to log DB
    void addLog(std::string s) {
        log += s + '\n';
    }

    // return save log data
    std::string getLog() {
        return log;
    }

    List<Member> getMemberDB() {
        return member_db;
    }

    List<Post> getPostDB() {
        return post_db;
    }

    //return reference of PostDB for changing purpose
    List<Post> &refPostDB() {
        List<Post> &temp = post_db;
        return temp;
    }

    //return reference of MemberDB for changing purpose
    List<Member> &refMemberDB() {
        List<Member> &temp = member_db;
        return temp;
    }

    //init input stream with file name
    void setBuffer(std::string s) {
        filebuf.open(s);
    }

    bool currentStatus() {
        return status;
    }

    //change between Mode (Manual/Command Mode)
    void startCommandMode() {
        commandMode = true;
    }

    void stopCommandMode() {
        commandMode = false;
    }

    bool getModeStatus() {
        return commandMode;
    }

    //Check Login information
    bool verify(const std::string &ID, const std::string &password) {
        //loop through element of memberDB and check ID and pw
        for (int idx = 0; idx < member_db.len(); idx++) {
            Member &temp = member_db.at(idx)->ref_content();
            if (temp.getID() == ID && temp.getPassword() == std::hash<std::string>{}(password)) {
                currentUser = temp;
                status = true;
                return true;
            }
        }
        return false;
    }

    void printUser() {
        std::cout << "@" << currentUser.getID() << " - " << currentUser.getName()
                  << " " << currentUser.getBirthday() << std::endl;
    }

    //print out my post
    bool printMyPost() {
        int cnt = -1;
        //head
        Node<Post> *current = post_db.begin();
        while (current != nullptr) {
            if (currentUser.getID() == current->content().getOwner().getID()) {
                cnt++;
                std::cout << cnt << ": "; //0 based indexing
                current->content().printPost();
                //print written time of post for debuggin purpose
                //current->content().printTime();
            }
            current = current->next;
        }
        return cnt > -1; //if idx remain unchanged it means nothing printed
    }

    //Same structure with @printMypost
    bool printFriendPost() {
        int cnt = -1;
        Node<Post> *current = post_db.begin();
        while (current != nullptr) {
            //loop through all postdb can check owner is currentUser's friend
            if (isFriend(refcurrentID().getFriendList(), current->content().getOwner().getID())) {
                cnt++;
                std::cout << cnt << ": ";
                current->content().printPost();
            }
            current = current->next;
        }
        return cnt > -1; //if idx remain unchanged it means nothing printed
    }

    Member &refcurrentID() {
        return member_db.search(currentUser.getID())->ref_content();
    }

    void clear() {
        Node<Member> *temp1 = member_db.begin();
        while (temp1 != nullptr) {
            temp1->content().deleteFriendlist();
            temp1 = temp1->next;
        }
        member_db.deleteList();
        Node<Post> *temp2 = post_db.begin();
        while (temp2 != nullptr) {
            temp2->content().deletePostContent();
            temp2 = temp2->next;
        }
        post_db.deleteList();
    }
    void deletePost();

    void deleteFriendList();
};



Member
create_member(const std::string &ID, const std::string &name, const std::string &birthday, const std::size_t &password);

void add_member(Database &db, const Member &m);

bool log_in(Database &db);

Member sign_in(Database &db);

void sign_out(Database &db);

void addFriend(Member &m, const List<Member> &member_db, const std::string &ID);

//remove friend with @ID from Member @m
void removeFriend(Member &m, const List<Member> &member_db, const std::string &ID);

//add like to post @p be Member @m
void likePost(Post &p, Member &m, Database &db);

#endif
