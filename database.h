#ifndef DATABASE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define DATABASE_H

#include <string>
#include <list>
#include <iostream>


template<class T>
class Node {
    T value;
    Node<T> *next;
public:

    Node (): value(NULL), next(nullptr){}
    Node(T data):value(data), next(nullptr){}

    void setNext(Node<T>* n){
        next = n;
    }
    Node<T>* getNext(){
        return next;
    }
    void setValue(T data) {
        value = data;
    }

    void setNull() {
        next = NULL;
    }
    T content(){
        return value;
    }

};

template<class T>
class List {
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    List() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~List() = default;
    Node<T> *begin(){
        return head;
    }
    Node<T> *end(){
        return tail;
    }
    int len(){
        return size;
    }
    void push_back(T data) {
        Node<T> *temp = new Node<T>(data);
        temp->setNext(NULL);
        if (head == NULL) {
            head = temp;
            tail = head;
            size++;
        } else {
            tail->setNext(temp);
            tail = tail->getNext();
            size++;
        }
    }
    Node<T>* at(int idx){
        int cnt = 0;
        Node<T> *temp = head;
        if (idx<size){
            while(temp->getNext() != NULL && cnt < idx){
                temp = temp ->getNext();
                cnt++;
            }
            return temp;
        }else{
            return nullptr;
        }
    }
};

class Member{
private:
     std::string ID;
     std::string name;
     std::string birthday;
     std::string passward;

public:
    List<Member> friend_list;
    Member() = default;
    Member( std::string ID,  std::string name,  std::string birthday,
             std::string passward);
    ~Member()= default;
    std::string getID(){
        return ID;
    }
    std::string getName(){
        return name;
    }
    std::string getBirthday(){
        return birthday;
    }
    std::string getPassward(){
        return passward;
    }
    void printUser() {
        std::cout << "@" << ID << " - " << name << " " << birthday << std::endl;
    }

    void addFriend(List<Member> member_db, std::string name);
    Member searchUser(List<Member> member_db, std::string name);
};
class Post{
public:
private:
};

class Database {
private:
public:
    List<Member> member_db;
    List<Post> post_db;
    bool status = false;
    Member currentUser;
    Database()= default;
    ~Database()= default;

    bool currentStatus(){
        return status;
    }
    bool verify(std::string ID, std::string password){
        for(int idx = 0; idx < member_db.len(); idx++){
            Member temp = member_db.at(idx)->content();
            if(temp.getID() == ID && temp.getPassward() == password){
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

};

template <> void List<Member>::push_back(Member data);
void print_db(List<Member> member_db);

Member create_member(std::string ID, std::string name, std::string birthday, std::string passward);
void add_member(Database& db, Member m);
bool log_in(Database &db);
Member sign_in();
void sign_out(Database &db);


#endif
