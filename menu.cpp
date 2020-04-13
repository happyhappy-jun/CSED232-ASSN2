#include <string>
#include <list>
#include "menu.h"
#include "database.h"

int function_handler(Database &mainDatabase, menuStack &s, menu *menuItem) {
    int id = menuItem->getmenuID();
    if (menuItem->has_children()) {
        s.push(menuItem);
        //return 0;
    }
    if (id == 224 or id == 214 or id == 4) {
        s.pop();
        return 0;
    }
    if (id == 1) {
        add_member(mainDatabase, sign_in());
        return 0;
    }
    if (id == 2) {
        if (!mainDatabase.currentStatus()) {
            if (log_in(mainDatabase)) {
                std::cout << "Success Logging in!" << std::endl;
                menuItem->changeName("My page");
            } else {
                std::cout << "Invalid Account" << std::endl;
                std::cout << "Returning previous menu" << std::endl;
                s.pop();
            }
        }else{
            menuItem->changeName("Sign in");
        }
        return 0;
    }
    if(id == 23){
        sign_out(mainDatabase);
        s.top()->changeName("Sign in");
        s.pop();
        return 0;
    }
    if(id == 211){
        addFriendWrapper(mainDatabase);
        return 0;
    }

    if(id == 213){
        print_db(mainDatabase.currentUser.friend_list);
    }
    return 0;
}
void addFriendWrapper(Database &db) {
    std::cout << "Input friend name: ";
    std::string friendName;
    std::cin >> friendName;
    db.currentUser.addFriend(db.member_db, friendName);
}


