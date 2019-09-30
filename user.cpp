#include "user.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

User::User(int id_, string name_, int birth_, int zip_, vector<int>friends_){
    id = id_;
    name = name_;
    birth = birth_;
    zip = zip_;
    counter = (int)friends_.size();
    for(int i=0; i < counter; i++){
        friends.push_back(friends_[i]);
    }
    predecessor = -1;
    //depth = -1;
}

User::~User(){
    //Empty
}

void User::add_friend(int id_){
    bool check = false;
    for(int i=0; i < counter; i++){
        if(friends[i] == id_){
            check = true;
        }
    }
    
    if(!check){
        friends.push_back(id_);
        counter++;
    }
    return;
}

void User::delete_friend(int id_){
    for(int i = 0; i < counter; i++){
        if(friends[i] == id_){
            for(int j=i; j < counter-1; j++){
                friends[j] = friends[j+1];
                friends.pop_back();
            }
            counter--;
        }
    }
    
    return;
}

int User::get_id(){
    return id;
}

string User::get_name(){
    return name;
}

int User::get_birth(){
    return birth;
}

int User::get_zip(){
    return zip;
}

int User::get_friends_counter(){
    return counter;
}

vector<int>* User::get_friends(){
    return &friends;
}

void User::set_predecessor(int value){
    predecessor = value;
}

int User::get_predecessor(){
    return predecessor;
}

void User::set_depth(int value){
    depth = value;
}

int User::get_depth(){
    return depth;
}