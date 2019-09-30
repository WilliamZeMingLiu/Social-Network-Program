#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
#include <vector>

using namespace std;


class User {
 public:
    User(int id_, string name_, int birth_, int zip_, vector<int>friends_);
    ~User();
    void add_friend(int id_);
    void delete_friend(int id_);
    string get_name();
    int get_id();
    int get_birth();
    int get_zip();
    int get_friends_counter();
    vector <int>* get_friends();
    
    //New data types
    int depth;
    int predecessor;
    void set_predecessor(int value);
    int get_predecessor();
    void set_depth(int value);
    int get_depth();
   
 private:
    int id;
    string name;
    int birth;
    int zip;
    vector<int> friends;
    int counter;
    
    
};


#endif
