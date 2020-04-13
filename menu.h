#ifndef MENU_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define MENU_H

#include <string>
#include <string>
#include <list>
#include <iostream>
#include <utility>
#include "database.h"

class menu;

class menuStack{
    private:
        menu *s[4];
        int dp;
    public:
        menuStack(){
            dp = -1;
        }
        ~menuStack(){}
        int isEmpty(){
            return (dp == -1);
        }
        menu *top(){
            return s[dp];
        }
        menu *push(menu* m) {
            dp++;
            s[dp] = m;
            return m;
        }
        menu *pop(void){
            if (isEmpty())
                return NULL;
            menu *temp;
            temp = s[dp];
            --dp;
            return temp;
        }
        menu *at(int idx){
            if(idx <= dp)
                return s[idx];
            else
                return NULL;
        }
};

class menu {
    private:
        menu(const std::string &name, menu *parent, int id): name(name) {
            if (parent) {
                parent->children.push(this);
            }
            menuID = id;
        }
    public:
        std::string name;
        int menuID;
        menuStack children;

        menu(const std::string &name): name(name){}
        ~menu(){}
        menu subMenu(const std::string &name, int id){
            return menu(name, this, id);
        }
        menu *getChild(int i) {
            return children.at(i);
        }
        int getmenuID(){
            return menuID;
        }
        int has_children(){
            return !children.isEmpty();
        }
        void changeName(const std::string &new_name){
            name = new_name;
        }

};




int function_handler(Database &mainDatabase, menuStack &s, menu *menuItem);
void addFriendWrapper(Database &db);

#endif