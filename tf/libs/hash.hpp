

// #include <bits/stdc++.h>
// #include <string>

// using namespace std;

// class HashU
// {
//     int size;   
  
//     // Pointer to an array 
//     vector<vector<vector<string>>> table;
// public:
//     HashU(int V);  // Constructor
  
//     // inserts a key into hash table
//     void insertItem(vector<string> &user);
  
//     // hash function to map values to key
//     int hashFunction(vector<string> &user) {
//         return (stoi(user[0]) % size);
//     }
  
//     void displayHash();
// };

// class HashT
// {
//     int size;   
  
//     // Pointer to an array 
//     list<int> *table;
// public:
//     HashT(int V);  // Constructor
  
//     // inserts a key into hash table
//     void insertItem(string tag);
  
//     // deletes a key from hash table
//     void deleteItem(string tag);
  
//     // hash function to map values to key
//     int hashFunction(string tag) {
//         int i = 0, hash = 0;

//         for(auto& c : tag){
//             if(c != ' '){
//                 hash = (int(c) + 127 * hash) % size;    
//             }
//         }
//         return int(hash);
//     }
  
//     void displayHash();
// };

// class HashM
// {
//     int size;   
  
//     // Pointer to an array 
//     list<int> *table;
// public:
//     HashM(int V);  // Constructor
  
//     // inserts a movieId into hash table
//     void insertItem(int movieId);
  
//     // deletes a movieId from hash table
//     void deleteItem(int movieId);
  
//     // hash function to map values to movieId
//     int hashFunction(int movieId) {
//         return (movieId % size);
//     }
  
//     void displayHash();
// };
  
// HashU::HashU(int b)
// {
//     this->size = b;
// }
  
// void HashU::insertItem(vector<vector<string>> &user)
// {
//     int tag = 0;
//     int index = hashFunction(user);
//     if (table[index].size()>0){
//         for(<vector<string>> node, int i =0; i<table.size(); i++){
//             if(node[0].compare(user[0])){
//                 node.push_back(user[1])
//                 node.push_back(user[2])
//                 tag = 1;
//             }

//         }
//         if(!tag){
//           table[index].push_back()
//         }
//     }
//     table[index].push_back(userId); 
// }
  
// // function to display hash table
// void HashU::displayHash() {
//   for (int i = 0; i < size; i++) {
//     cout << i;
//     for (auto x : table[i])
//       cout << " --> " << x;
//     cout << endl;
//   }
// }

// HashT::HashT(int b)
// {
//     this->size = b;
//     table = new list<int>[size];
// }
  
// void HashT::insertItem(string tag)
// {
//     int index = hashFunction(tag);
//     table[index].push_back(tag); 
// }
  
// void HashT::deleteItem(string tag)
// {
//   // get the hash index of key
//   int index = hashFunction(tag);
  
//   // find the key in (inex)th list
//   list <int> :: iterator i;
//   for (i = table[index].begin();
//            i != table[index].end(); i++) {
//     // if (*i == tag)
//       break;
//   }
  
//   // if key is found in hash table, remove it
//   if (i != table[index].end())
//     table[index].erase(i);
// }
  
// // function to display hash table
// void HashT::displayHash() {
//   for (int i = 0; i < size; i++) {
//     cout << i;
//     for (auto x : table[i])
//       cout << " --> " << x;
//     cout << endl;
//   }
// }

// HashM::HashM(int b)
// {
//     this->size = b;
//     table = new list<int>[size];
// }
  
// void HashM::insertItem(int key)
// {
//     int index = hashFunction(key);
//     table[index].push_back(key); 
// }
  
// void HashM::deleteItem(int key)
// {
//   // get the hash index of key
//   int index = hashFunction(key);
  
//   // find the key in (inex)th list
//   list <int> :: iterator i;
//   for (i = table[index].begin();
//            i != table[index].end(); i++) {
//     if (*i == key)
//       break;
//   }
  
//   // if key is found in hash table, remove it
//   if (i != table[index].end())
//     table[index].erase(i);
// }
  
// // function to display hash table
// void HashM::displayHash() {
//   for (int i = 0; i < size; i++) {
//     cout << i;
//     for (auto x : table[i])
//       cout << " --> " << x;
//     cout << endl;
//   }
// }

/////////////////////////////////////////////////////////////////////////

// #include <vector>
// #include <string>

// int hashingUM(int n, int size){
//     return int(n%size);
// }

// int hashingT(string tag, int size){
//     int i = 0, hash = 0;

//     for(auto& c : tag){
//         if(c != ' '){
//             hash = (int(c) + 127 * hash) % size;    
//         }
//     }
//     return int(hash);
// }

// int insertChainUT(int hash, std::vector<std::string> tuple, std::vector<std::vector<std::string>> table){
//     int tag = 0;

//     for(auto& node : table){
//         if (stoi(node[0]) == hash){
//             for(auto& subnode : node){
//                 if(subnode == tuple[0]){

//                 }
//             }
//         }
//     }
// }

// int insertChainM(int hash, std::vector<std::string> tuple, std::vector<std::vector<std::string>> table){
//     int tag = 0;

//     for(auto& node : table){
//         if (stoi(node[0]) == hash){
//             if(node.size()>2){
//                 for(auto&)
//             }
//         }
//     }
// }

// std::vector<std::string> searchChainUM(int id, std::vector<std::vector<std::string>> table, int size){
//     int hash = hashingUM(id,size);

//     for(auto& node : table){
//         if (stoi(node[0]) == hash){
//                 if(id == stoi(node[1]])){
                    
//                 }
//             }
//         }
//     }
// }