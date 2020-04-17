#ifndef MENU_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define MENU_H

#include <string>
#include <string>
#include <list>
#include <iostream>
#include <utility>
#include "headers/database.h"

class menu;

class menuStack {
private:
    menu *s[4];
    int dp;
public:
    menuStack() {
        dp = -1;
    }

    ~menuStack() = default;

    int isEmpty() {
        return (dp == -1);
    }

    menu *top() {
        return s[dp];
    }

    menu *push(menu *m) {
        dp++;
        s[dp] = m;
        return m;
    }

    menu *pop() {
        if (isEmpty())
            return nullptr;
        menu *temp;
        temp = s[dp];
        --dp;
        return temp;
    }

    menu *at(int idx) {
        if (idx <= dp)
            return s[idx];
        else
            return nullptr;
    }
};

class menu {
private:
    std::string name;
    int menuID;
    menuStack children;

    menu(std::string name, menu *parent, int id) : name(std::move(name)) {
        if (parent) {
            parent->children.push(this);
        }
        menuID = id;
    }

public:
    menu(std::string name) : name(std::move(name)) {}

    ~menu() {
        for (int i = 0; i < 4; i++) {
            if (children.at(i) != nullptr)
                delete children.at(i);
        }
    }

    menu subMenu(const std::string &name, int id) {
        return menu(name, this, id);
    }

    menuStack getChildren() {
        return children;
    }

    std::string getName() {
        return name;
    }

    menu *getChild(int i) {
        return children.at(i);
    }

    int getmenuID() {
        return menuID;
    }

    int has_children() {
        return !children.isEmpty();
    }

    void changeName(const std::string &new_name) {
        name = new_name;
    }
};


int function_handler(Database &mainDatabase, menuStack &s, menu *menuItem);

void addFriendWrapper(Database &db);

void removeFriendWrapper(Database &db);

void addPostWrapper(Database &db);

void printFriendPostWrapper(Database &db);

void printMyPostWrapper(Database &db);

void writeCommentWrapper(Database &db);

void removeAccountWrapper(Database &db);

#endif