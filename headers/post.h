//
// Created by Yoon Jun on 2020/04/14.
//


#ifndef ASSN2_POST_H
#define ASSN2_POST_H

#include <ctime>
#include <utility>
#include <fstream>
#include "headers/member.h"
#include "headers/list.h"


class Comment {
private:
    Member owner;
    std::string content;
public:
    Comment() = default;

    Comment(const Member &owner, std::string content) : owner(owner), content(std::move(content)) {};

    Member getOwner() {
        return owner;
    }

    std::string getContent() {
        return content;
    }
};

class Post {
private:
    time_t timer{};
    Member owner;
    std::string content;
    List<Comment> commentList;
    List<std::string> likeList;
public:

    Post() = default;

    explicit Post(const Member &owner, std::string content) : owner(owner), content(std::move(content)) {
        timer = std::time(nullptr);
    };

    time_t getTime() {
        return timer;
    }

    Member getOwner() {
        return owner;
    }

    List<Comment> getCommentList() {
        return commentList;
    }

    List<std::string> getLikeList() {
        return likeList;
    }

    std::string getContent() {
        return content;
    }

    List<std::string>& refLikelist(){
        List<std::string>& a = likeList;
        return a;
    }
    void printTime(){
        std::cout << timer << std::endl;
    }
    void printPost();

    void printComment();

    void writeComment(Member &m, std::string &c);

    void deleteComment(Member &m);
};

template<>
void List<Post>::push_back(const Post &p);

#endif //ASSN2_POST_H
