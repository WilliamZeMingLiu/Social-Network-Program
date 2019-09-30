#include "network.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip> 
#include <sstream>

using namespace std;


int main(int argc, char *argv[]){
  
  Network net;
  net.read_friends(argv[1]);

  int answer;
    
  while(true){
      cout << "Please select which one of the ";
      cout << "7 options you want (please use numbers)" << endl;
      cout << "Option 1: Add User" << endl;
      cout << "Option 2: Add Friend Connection" << endl;
      cout << "Option 3: Remove Friend Connection" << endl;
      cout << "Option 4: Print Users" << endl;
      cout << "Option 5: List Friends" << endl;
      cout << "Option 6: Write to File" << endl;
      cout << "Option 7: Distance Between Members" << endl;
      cout << "Option 8: Number of Disjoint Sets" << endl;
      cout << "Option 9: Suggest Friends" << endl;
      cout << "Option 10: Exit Program" << endl;
      
      cout << "Which selection do you want?:";
      cin >> answer;
      
      if(answer == 1){
          vector <int> friends;
          string first, last, name;
          int birth, zip;
          cout << "Please provide name, birth year, and zip code:";
          cin >> first >> last >> birth >> zip;
          name = first + " " + last;
          net.add_user(name, birth, zip);
          cout << endl;

      }
      else if(answer == 2){
          string first1, first2, last1, last2;
          string name1, name2;
          cout << "Please provide two names that you want to become friends:";
          cin >> first1 >> last1 >> first2 >> last2;
          name1 = first1 + " " + last1;
          name2 = first2 + " " + last2;
          int check = net.add_connection(name1, name2);
          if(check == -1){
              cout << "One or both users do not";
              cout << "exist.  Please try again" << endl;
              cout << endl;
          }
          else if (check == 0){
              cout << "Friends added succesfully!" << endl;
          }
      }
      else if(answer == 3){
          string first1, last1, first2, last2, name1, name2;
          cout << "Please provide two names that you want to remove:";
          cin >> first1 >> last1 >> first2 >> last2;
          name1 = first1 + " " + last1;
          name2 = first2 + " " + last2;
          int check = net.remove_connection(name1, name2);
          if(check == -1){
              cout << "One or both users do not exist. ";
              cout << "Please try again" << endl;
          }
          else if (check == 0){
              cout << "Friends removed succesfully!" << endl;
          }
      }
      else if(answer == 4){
          cout << left << setw(10) << "ID" << setw(20);
          cout << "NAME" << setw(10) << "YEAR" << setw(10) << "ZIP" << endl;
          for(int i=0; i < 59; i++){
              cout << "=";
          }
          cout << endl;
          for(int i=0; i < net.get_people_counter(); i++){
              stringstream ss;
              ss << (*net.get_people_array())[i].get_id();
              string str = ss.str() + ".";
              
              cout << setw(10) << str;
              cout << setw(20) << (*net.get_people_array())[i].get_name();
              cout << setw(10) << (*net.get_people_array())[i].get_birth();
              cout << setw(10) << (*net.get_people_array())[i].get_zip();
              cout << endl;
          }
      }
      else if(answer == 5){
          string first, last, name;
          cout << "Please provide a username:";
          cin >> first >> last;
          name = first + " " + last;
          
          int check = net.print_list(name);
          if(check == -1){
              cout << "Friend not found.  Please try again" << endl;
          }
 
      }
      else if(answer == 6){
          string filename;
          cout << "Please provide file to write to:";
          cin >> filename;
          const char* s_filename = filename.c_str();
          int check = net.write_friends(s_filename);
          if(check == -1){
              cout << "Error, please try again" << endl;
          }
          else if (check == 0){
              cout << "File printed succesfully!" << endl;
          }      
      }
      else if (answer == 7){
          int id1, id2;
          string first1, first2, last1, last2, name1, name2;
          cout << "Please provide the two users" << endl;
          cin >> first1 >> last1 >> first2 >> last2;
          name1 = first1 + " " + last1;
          name2 = first2 + " " + last2;
          
          for(int i=0; i < net.get_people_counter(); i++){
              if((*net.get_people_array())[i].get_name() == name1){
                  id1 = (*net.get_people_array())[i].get_id();
                  
          }
              if((*net.get_people_array())[i].get_name() == name2){
                  id2 = (*net.get_people_array())[i].get_id(); 
              }
          }              
          
          if(net.shortest_path(id1, id2).empty()){
                  cout <<  "Distance:" << net.shortest_path(id1, id2).size() << endl;
                  cout << "NONE" << endl;      
          }
          
          else{
              cout <<  "Distance:" << net.shortest_path(id1, id2).size()-1 << endl;
              for(int i = 0; i < net.shortest_path(id1, id2).size(); i++){
                  cout << (*net.get_people_array())[net.shortest_path(id1, id2)[i]].get_name() << " ";
                      if(i != net.shortest_path(id1, id2).size()-1){
                          cout << "-> ";
                          
                      }
               }   
               cout << endl;
          }
          cout << endl;

      }
      else if(answer == 8){
          for(int i=0; i < net.groups().size(); i++){
              cout << "Set " << i+1 << " => ";
              for(int j=0; j < net.groups()[i].size(); j++){
                  cout <<(*net.get_people_array())[net.groups()[i][j]].get_name();
                  if(j < net.groups()[i].size()-1){
                      cout << ", ";
                  }
                  
              }
              cout << endl;
          }
          cout << endl;
      }
      
      else if (answer == 9){
          int value = 0;
          int* score = &value;
          string first, last, name;
          int guy;
          
          cout << "Please enter a name:" << endl;
          cin >> first >> last;
          name = first + " " + last;
          for(int i=0; i < net.get_people_counter(); i++){
              if(name == (*net.get_people_array())[i].get_name()){
                  guy = i;
              }
          }
          if(*score == -1){
              cout << "None" << endl;
          }
          else{
              cout << "The suggest friend(s) is/are:" << endl;
              for(int i=0; i < net.suggest_friends(guy, *score).size(); i++){
                  cout << "\t" << (*net.get_people_array())[net.suggest_friends(guy, *score)[i]].get_name();
                  cout << setw(10) << "Score:" << *score << endl;
              }  
          }
          
      }

      else{
          cout << "Programming exiting.  Thank You!" << endl;
          break;
      }
  }
  return 0;
}