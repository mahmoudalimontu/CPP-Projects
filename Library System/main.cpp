#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

struct Book {
    int total_quantity,id,borrowed_quantity;
    string name;
};
map<string,pair<int,int>>mp; // name -> [total,borrowed]
map<int,string>id_to_name; //   id   -> name
map<string,int>name_to_id; //   name -> id
set<int>library_by_id;
set<string>library_by_name;

// option 1
string addBook(int id,string name,int quantity) {
    if (quantity<0) {
        return "quantity can't be negative.\n";
    }
    auto it=id_to_name.find(id);
    if (it != id_to_name.end() && it->second!=name) {
        return "Sorry, this id is found already.\n";
    }
    mp[name].first+=quantity;
    library_by_name.insert(name);
    library_by_id.insert(id);
    id_to_name[id]=name;
    name_to_id[name]=id;
    return "The book added successfully.\n";
}
// option 2
void searchBook(string part) {
    bool found=false;
    for (auto i:library_by_name) {
        auto index=i.find(part);
        if (index != string::npos) {
            string before_part=i.substr(0,index);
            string after_part=i.substr(index,i.length());
            string part_underlined="\033[4m" + part + "\033[0m";
            cout<<before_part<<part_underlined<<after_part<<endl;
            found=true;
        }
    }
    if (!found)cout<<"No books with this name.\n";
}
// option 4
void printLibraryById() {
   for (auto id:library_by_id) {
       // if there is available quantity
       string get_name=id_to_name[id];
       int available_quantity=mp[get_name].first-mp[get_name].second;
       if (available_quantity>0) {
           cout<<"id: "<<id<<" name: "<<get_name<<" total quantity: "<<mp[get_name].first<<" borrowed quantity: "<<mp[get_name].second<<endl;
       }
   }
}
// option 5
void printLibraryByName() {
    for (auto name:library_by_name) {
        int available_quantity=mp[name].first-mp[name].second;
        if (available_quantity>0) {
            cout<<"name: "<<name<<" id: "<<name_to_id[name]<<" total quantity: "<<mp[name].first<<" borrowed quantity: "<<mp[name].second<<endl;
        }
    }
}


int main() {

    return 0;
}