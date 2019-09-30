#include "network.h"
#include "user.h"
#include <string>
#include <vector>
#include <iomanip> 
#include <sstream>

using namespace std;

Network::Network(){
    people_array.reserve(200);
}

Network::~Network(){
    //Empty
}

int Network::read_friends(const char *filename){
  ifstream ifile (filename);
    
  if (ifile.fail()){
      cout << "Error: Could not read file" << endl;
      return -1;
  }
    
  int num_of_users;
  ifile >> num_of_users;
  for(int i=0; i < num_of_users; i++){
      
      int id, birth, zip;
      
      string name, garbage, first_name, last_name;
      vector <int> friends;
      ifile >> id;
      
      ifile >> first_name >> last_name;
      name = first_name + " " + last_name;
    
      ifile >> birth >> zip; 
      
      getline(ifile, garbage);
      getline(ifile, garbage);
      
      
      int counter = 0;
      while(garbage[counter] != '\0'){
          if(isdigit(garbage[counter])){
              counter++;
          }
          else{
              garbage[counter] = '*';
              counter++;
          }
      }
        
      garbage[counter] = '*';

      for(int j=0; j < counter; j++){
          if(isdigit(garbage[j])){
              if(isdigit(garbage[j+1])){
                  friends.push_back(((int)garbage[j+1]-48)+((int)garbage[j]-48)*(10));
                  j++;
              } 
              else if (isdigit(garbage[j+1]) != true){
                  friends.push_back(((int)garbage[j]-48));
              }
          }         
      }  
      User temp(id, name, birth, zip, friends);
      people_array.push_back(temp);   
  }
  ifile.close();
  return 0;
}

int Network::write_friends(const char *filename){
    ofstream outfile (filename);
    if (outfile.fail()){
        return -1;
    }
    outfile << people_array.size() << endl;
    for(int i=0; i < people_array.size(); i++){
        outfile << people_array[i].get_id() << endl;
        outfile << "\t" << people_array[i].get_name() << endl;
        outfile << "\t" << people_array[i].get_birth() << endl;
        outfile << "\t" << people_array[i].get_zip() << endl;
        outfile << "\t";
        for(int j=0; j < people_array[i].get_friends_counter(); j++){

            outfile << (*people_array[i].get_friends())[j] << " ";
        }
        outfile << endl;
    }
    
    outfile.close();
    return 0;
    
}
//I changed parameters of this function
void Network::add_user(string username, int yr, int zipcode){
    vector <int> vec;
    int size = (int)people_array.size();
    User temp(size, username, yr, zipcode, vec);
    people_array.push_back(temp);
    return;
}

int Network::add_connection(string name1, string name2){
    int id1, id2;
    int check_c = 0;

    for(int i=0; i < people_array.size(); i++){
        if(people_array[i].get_name() == name1){
            id1 = people_array[i].get_id();
            check_c++;
        }
        else if(people_array[i].get_name() == name2){
            id2 = people_array[i].get_id();
            check_c++;
        }
    }
    
    if(check_c != 2){
        return -1;
    }

    for(int i=0; i < people_array.size(); i++){
        if(people_array[i].get_name() == name1){
            cout << people_array[i].get_name() << endl;
            people_array[i].add_friend(id2);
        }
        else if(people_array[i].get_name() == name2){
            cout << people_array[i].get_name() << endl;
            people_array[i].add_friend(id1);
        }
    }
    return 0;
}


int Network::remove_connection(string name1, string name2){
    int id1, id2;
    int check_c = 0;

    for(int i=0; i < people_array.size(); i++){
        if(people_array[i].get_name() == name1){
            id1 = people_array[i].get_id();
            check_c++;
        }
        else if(people_array[i].get_name() == name2){
            id2 = people_array[i].get_id();
            check_c++;
        }
    }
    
    if(check_c != 2){
        return -1;
    }

    for(int i=0; i < people_array.size(); i++){
        if(people_array[i].get_name() == name1){
            people_array[i].delete_friend(id2);
                
        }
        else if(people_array[i].get_name() == name2){
            people_array[i].delete_friend(id1);
        }
    }
    return 0;
}

int Network::print_list(string name){
    for(int i = 0; i < people_array.size(); i++){ 
        if(people_array[i].get_name() == name){
            cout << left << setw(10) << "ID" << setw(20) << "NAME";
            cout << setw(10) << "YEAR" << setw(10) << "ZIP" << endl;
            for(int k=0; k < 59; k++){
                cout << "=";
            }

            for(int j=0; j < people_array[i].get_friends_counter(); j++){      
                for(int k=0; k < people_array.size(); k++){
                    if((*people_array[i].get_friends())[j] 
                       == people_array[k].get_id()){
                        cout << endl;
                        stringstream ss;
                        ss << people_array[k].get_id();
                        string str = ss.str() + ".";

                        cout << setw(10) << str;
                        cout << setw(20) << people_array[k].get_name();
                        cout << setw(10) << people_array[k].get_birth();
                        cout << setw(10) << people_array[k].get_zip();
                        cout << endl;
                    }
                }
             }
          return 0;
         }
    }
    return -1;
}

int Network::get_id(string username){
    for(int i=0; i < people_array.size(); i++){
        if(people_array[i].get_name() == username){
            return i;  
        }
    }
    return -1;
}

vector<User>* Network::get_people_array(){
    return &people_array;
}

int Network::get_people_counter(){
    return people_array.size();
}

vector <int> Network::shortest_path(int from, int to){
    int single_friend;
    vector <int> connections, queue, all_numbers, real_connections;
   
    bool check = true;
    if(from == to){
        connections.push_back(from);
        real_connections.push_back(from);
        return real_connections;
    }
    
    int next_node = from;
    all_numbers.push_back(from);
    
    people_array[from].set_depth(0);
    people_array[from].set_predecessor(-1);
    // || 
    while(all_numbers.size() != people_array.size()-1||!queue.size()){    
        //counter++;
        //cout << counter << endl;
        //cout << all_numbers.size() << " " << people_array.size()-1 << endl;
        for(int i=0; i < people_array[next_node].get_friends_counter(); i++){      
            single_friend = (*people_array[next_node].get_friends())[i];
            
            if (single_friend == to){
                connections.push_back(single_friend);
                people_array[single_friend].set_depth(people_array[next_node].get_depth()+1);               
                people_array[single_friend].set_predecessor(next_node);
                while(people_array[single_friend].get_predecessor() != -1){
                    connections.push_back(people_array[single_friend].get_predecessor());
                    single_friend = people_array[single_friend].get_predecessor();
                }
                
                for(int i=0; i < connections.size(); i++){
                    real_connections.push_back(connections[connections.size()-1-i]);
                }
                
                return real_connections;
            }
            else{
                if(all_numbers.size() == 0){
                    all_numbers.push_back(single_friend);
                    queue.push_back(single_friend);
                }
                else{
                    for(int j=0; j < all_numbers.size(); j++){
                        if(all_numbers[j] == single_friend){
                            check = false;
                        }
                    }
                    if(check == true){
                        all_numbers.push_back(single_friend);
                        queue.push_back(single_friend);
                        people_array[single_friend].set_depth(people_array[next_node].get_depth()+1);
                        people_array[single_friend].set_predecessor(next_node); 
                    } 
                }
            }
            check = true;
        }      
        next_node = queue[0];
        for(int j=0; j < queue.size()-1; j++){
            queue[j] = queue[j+1];
        }
        queue.pop_back();
        
    }
    
    return real_connections;
}  

vector<vector<int> > Network::groups(){
    vector <int> queue, all_numbers;
    vector <int> groups;
    vector<vector<int> > group_of_group;
    bool check = true;
    int single_friend;
    
    for(int i = 0; i < people_array.size(); i++){
        
        if(people_array[i].get_predecessor() == -1){
            //cout << people_array[i].get_name() << endl;
            vector <int> queue, all_numbers;
            vector <int> groups;
            int next_node = i;
            all_numbers.push_back(next_node);
            queue.push_back(next_node);
            
            while(!queue.empty()){
                //cout << "Starting Node:" << people_array[next_node].get_id() << endl;
                //cout << "Node Friends:";

                for(int j=0; j < people_array[next_node].get_friends_counter(); j++){
                    single_friend = (*people_array[next_node].get_friends())[j];
                    //cout << single_friend << " ";
                    for(int k=0; k < all_numbers.size(); k++){
                        if(single_friend == all_numbers[k]){
                            check = false;
                        }
                    }

                    if(check){
                        queue.push_back(single_friend);
                        all_numbers.push_back(single_friend);
                        people_array[single_friend].set_predecessor(100);
                    }
                    check = true;   
                }

                //cout << endl;
                //cout << "-All Numbers:";
                for(int i=0; i < all_numbers.size(); i++){
                    //cout << all_numbers[i] << " ";

                }
                //cout << endl;


                for(int j=0; j < queue.size()-1; j++){
                    queue[j] = queue[j+1];
                }
                next_node = queue[0];
                queue.pop_back();
            }

            for(int i=0; i < all_numbers.size(); i++){
                groups.push_back(all_numbers[i]);
            }
            group_of_group.push_back(groups);    
        }
    }
    
    return group_of_group;
}


vector<int> Network::suggest_friends(int who, int& score){
    int single_friend;
    vector <int> queue, all_numbers, suggestions, candidates;

    int next_node = who;
    int temp_score = -1;
    int max = 0;
    all_numbers.push_back(who);
    queue.push_back(who);
    
    people_array[who].set_depth(0);
    people_array[who].set_predecessor(-1);
    
    int check=true;
    
    for(int i=0; i < people_array[next_node].get_friends_counter(); i++){  
        check = true;
        
        single_friend = (*people_array[next_node].get_friends())[i];

        people_array[single_friend].set_depth(people_array[next_node].get_depth()+1);               
        people_array[single_friend].set_predecessor(next_node);
        
        for(int j=0; j < all_numbers.size(); j++){
            if(all_numbers[j] == single_friend){
                check = false;
             }
        }

        if(check){
            all_numbers.push_back(single_friend);
            queue.push_back(single_friend);
        }

    }
    for(int i=1; i < queue.size(); i++){
        for(int j=0; j < people_array[queue[i]].get_friends_counter(); j++){
            check = true;
        
            single_friend = (*people_array[queue[i]].get_friends())[j];
            

            people_array[single_friend].set_depth(people_array[queue[i]].get_depth()+1);               
            people_array[single_friend].set_predecessor(queue[i]);
            
            for(int j=0; j < all_numbers.size(); j++){
                if(all_numbers[j] == single_friend){
                    check = false;
                 }
            }

            if(check){
                candidates.push_back(single_friend);
                all_numbers.push_back(single_friend);
            }      
        }
    }
    
    for(int i=0; i < candidates.size(); i++){
        temp_score = 0;
        for(int j=0; j < people_array[candidates[i]].get_friends_counter(); j++){
            
            check = true;
        
            single_friend = (*people_array[candidates[i]].get_friends())[j];

            people_array[single_friend].set_depth(people_array[candidates[i]].get_depth()+1);               
            people_array[single_friend].set_predecessor(candidates[i]);
            
            
            for(int k=0; k < queue.size(); k++){
                if(queue[k] == single_friend){
                    temp_score++;
                }
            }
        }
        if(temp_score > max){
            max = temp_score;
        }
        
    }
    
    for(int i=0; i < candidates.size(); i++){
        temp_score = 0;
        for(int j=0; j < people_array[candidates[i]].get_friends_counter(); j++){
            single_friend = (*people_array[candidates[i]].get_friends())[j];
    
            for(int k=0; k < queue.size(); k++){
                if(queue[k] == single_friend){
                    temp_score++;
                }
            }
        }
        if(temp_score == max){
            suggestions.push_back(candidates[i]);
        }
    }
    
    if(max == 0){
        score = -1;
    }
    else{
        score = max;
    }
    
    return suggestions;
    
}
