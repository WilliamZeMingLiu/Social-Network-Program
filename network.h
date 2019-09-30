#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "user.h"

class Network {
 public:
  Network();
  ~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  //Changed parameters
  void add_user(std::string username, int yr, int zipcode);
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int print_list(std::string name);
  int get_id(std::string username);
  int get_people_counter();
    
  vector <User>* get_people_array();
    
  //New functions
  vector <int> shortest_path(int from, int to);
  vector<vector<int> > groups();
  vector<int> suggest_friends(int who, int& score);
    

 private:
    vector<User>people_array;
  
};


#endif
