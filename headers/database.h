#ifndef DATABASE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define DATABASE_H

#include <string>
#include <iostream>
#include "member.h"
#include "post.h"
#include "list.h"


class Database {
private:
    List<Member> member_db;
    List<Post> post_db;
    bool status = false;
    Member currentUser;
public:

    Database() = default;

    ~Database() {
        member_db.deleteList();
        post_db.deleteList();
    };
    bool getStatus(){
        return status;
    }
    void setStatus(bool i){
        status = i;
    }
    Member getCurrentUser() {
        return currentUser;
    }

    List<Member> getMemberDB() {
        return member_db;
    }

    List<Post> getPostDB() {
        return post_db;
    }

    List<Post> &refPostDB() {
        List<Post> &temp = post_db;
        return temp;
    }
    List<Member> &refMemberDB() {
        List<Member> &temp = member_db;
        return temp;
    }

    bool currentStatus() {
        return status;
    }

    bool verify(const std::string& ID, const std::string& password) {
        for (int idx = 0; idx < member_db.len(); idx++) {
            Member &temp = member_db.at(idx)->ref_content();
            if (temp.getID() == ID && temp.getPassword() == password) {
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

    bool printMyPost() {
        int cnt = -1;
        Node<Post> *current = post_db.begin();
        while (current != nullptr) {
            if (currentUser.getName() == current->content().getOwner().getName()) {
                cnt++;
                std::cout << cnt << ": ";
                current->content().printPost();
            }
            current = current->next;
        }
        return cnt > -1;
    }

    bool printFriendPost() {
        int cnt = -1;
        Node<Post> *current = post_db.begin();
        while (current != nullptr) {
            if (isFriend(refcurrentUser().getFriendList(), current->content().getOwner().getName())) {
                cnt++;
                std::cout << cnt << ": ";
                current->content().printPost();
            }
            current = current->next;
        }
        return cnt > -1;
    }

    void deletePost();

    void deleteFriendList();

    Member &refcurrentUser() {
        return member_db.search(currentUser.getName())->ref_content();
    }
};


Member create_member(const std::string &ID, const std::string &name, const std::string &birthday, const std::string &password);

void add_member(Database &db, const Member &m);

bool log_in(Database &db);

Member sign_in();

void sign_out(Database &db);

void addFriend(Member &m, const List<Member>& member_db, const std::string& name);

void removeFriend(Member &m, const List<Member>& member_db, const std::string& name);


#endif
