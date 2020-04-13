# ASSN 2

## Planning
- Menu structure

```bash
└── main_memu
    ├── 1.\ Sign_up
    │   └── create_account()
    ├── 2.\ Sign_in
    │   ├── 1.\ Freinds
    │   │   ├── 1.\ Add_friends
    │   │   │   └── add_friend(self, target)
    │   │   ├── 2.\ Delete_friends
    │   │   │   └── delete_friend(self, target)
    │   │   ├── 3.\ My_friends
    │   │   │   └── show_friend(self)
    │   │   └── 4.\ Previous_menu
    │   ├── 2.\ Feed
    │   │   ├── 1.\ All_Feed
    │   │   │   └── show_feed()
    │   │   ├── 2.\ Post
    │   │   │   └── create_post()
    │   │   ├── 3.\ My_posting
    │   │   │   └── show_feed(self)
    │   │   └── 4.\ Previous_menu
    │   ├── 3.\ Sign\ out
    │   │   └── log_out()
    │   ├── 4.\ Delete\ my\ account
    │   │   └── delete_account()
    │   └── log_in()
    ├── 3.\ Load_Command
    └── 4.\ Program_exit
```