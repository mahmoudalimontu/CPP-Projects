#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

string getCurrentDateTime();

struct Book {
    int total_quantity,id,borrowed_quantity;
    string name;
};

map<string,pair<int,int>>mp; // name -> [total,borrowed]
map<int,string>id_to_name; //   id   -> name
map<string,int>name_to_id; //   name -> id
set<int>library_by_id;
set<string>library_by_name;
map<string,multiset<pair<string,int>>> who_borrowed_book_by_name; // Name and date of users who borrowed a specific book
map<int,string> user_info; // National id -----> the name related to this id
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
// option 2: search anywhere in book name (substring search)
void searchBook(string part) {
    bool found=false;
    for (auto i:library_by_name) {
        auto index=i.find(part);
        if (index != string::npos) {
            cout<<i<<endl;
            found=true;
        }
    }
    if (!found)cout<<"No books with this name.\n";
}
// option 3
void printWhoBorrowedBookByName(string bookName) {
    if (library_by_name.contains(bookName) == false) {
        cout<<"Sorry, we couldn't find a book with this name in our library system.\n";
        return;
    }
    auto& my_multiset = who_borrowed_book_by_name[bookName];
    if (my_multiset.empty()) {
        cout<<"No one has borrowed this book yet.\n";
        return;
    }
    cout<<"\nUsers who borrowed '"<<bookName<<"':\n";
    for (auto item : my_multiset) {
        int national_id = item.second;
        string borrow_time = item.first;
        string userName = user_info[national_id];
        cout<<"    - Name: "<<userName<<" | National ID: "<<national_id<<" | Borrowed At: "<<borrow_time<<endl;
    }
}
// option 4
void printLibraryById() {
   for (auto id:library_by_id) {
       string get_name=id_to_name[id];
       cout<<"id: "<<id<<" name: "<<get_name<<" total quantity: "<<mp[get_name].first<<" borrowed quantity: "<<mp[get_name].second<<endl;
   }
}
// option 5
void printLibraryByName() {
    for (auto name:library_by_name) {
        cout<<"name: "<<name<<" id: "<<name_to_id[name]<<" total quantity: "<<mp[name].first<<" borrowed quantity: "<<mp[name].second<<endl;
    }
}
// option 6
void addUser(int national_id,string userName) {
    auto it=user_info.find(national_id);
    if (it!=user_info.end()) {
        if (user_info[national_id]!=userName)
            cout<<"Error: This National ID is already registered under a different name.\n";
        else
            cout << "User already exists with the exact same details.\n";
    }
    else {
        user_info[national_id]=userName;
        cout << "Success: New user added successfully.\n";
    }
}
// option 7
void userBorrowBook(int national_id,string bookName) {
    auto it=user_info.find(national_id);
    if (it==user_info.end())
        cout<<"Sorry: User not found in the system.\n>>>Please add this user first!\n";
    else {
        // Search about the book
        if (library_by_name.contains(bookName)==false) {
            cout<<"Sorry, this book does not exist in our library.\n";
        }
        else {
            // Are there any copies of this book available in the library right now ?
            if (mp[bookName].first-mp[bookName].second<=0) {
                cout<<"Sorry, all copies of this book are currently checked out.\n";
            }
            else {
                mp[bookName].second++;
                who_borrowed_book_by_name[bookName].insert(make_pair(getCurrentDateTime(),national_id));
                cout<<"\n>>> Success: The book has been successfully borrowed!\n";
                cout<<"    - Borrower Name: "<<user_info[national_id]<<endl;
                cout<<"    - National ID: "<<national_id<<endl;
                cout<<"    - Book Name: "<<bookName<<endl;
                cout<<"    - Borrow Date: "<<getCurrentDateTime()<<endl;
                cout<<"    Have a great read!\n";
            }
        }
    }
}
// Option 8
void userReturnBook(int national_id,string bookName) {
    auto it=user_info.find(national_id);
    if (it==user_info.end())
        cout<<"Sorry, this user doesn't exist in our system.\n>>>Perhaps you borrowed the book from another library?\n";
    else {
        if (library_by_name.contains(bookName)==false) {
            cout<<"Sorry, we couldn't find a book with this name in our library system.\n>>>Please check the book title and try again.\n";
        }
        else {
            // search about when user got that book
            bool found=false;
            string borrow_time="";
            pair<string,int> target_item;
            auto& my_multiset=who_borrowed_book_by_name[bookName];
            for (auto item:my_multiset) {
                if (item.second==national_id) {
                    target_item=item;
                    borrow_time=item.first;
                    found=true;
                    break;
                }
            }
            if (!found) {
                cout<<"Sorry, this user didn't borrow this book in the first place!\n";
                return;
            }
            mp[bookName].second--;
            my_multiset.erase(my_multiset.find(target_item));

            cout<<"\n>>> Success: The book has been successfully returned!\n";
            cout<<"    - Borrower Name: " << user_info[national_id]<<endl;
            cout<<"    - National ID: " << national_id<<endl;
            cout<<"    - Book Name: "<<bookName<<endl;
            cout<<"    - Borrowed At: "<<borrow_time<<endl;
            cout<<"    - Return Date: " << getCurrentDateTime()<<endl;
            cout<<"    Thank you! We hope you enjoyed reading the book.\n";
        }
    }
}
void printUsers() {
    bool borrowed_yet=false;
    for (auto user:user_info) {
        int national_id = user.first;
        string userName = user.second;

        cout<<"\nUser Name: "<<userName<<endl;
        cout<<"National ID: "<<national_id<<endl;
        cout<<"Borrowed Books:\n";
        bool hasBook=false;
        borrowed_yet=true;
        for (auto book:library_by_name) {
            for (auto item:who_borrowed_book_by_name[book]) {
                if (item.second==national_id) {
                    cout<<"    - Book: "<<book<<" | Borrow Date: "<<item.first<<endl;
                    hasBook = true;
                }
            }
        }
        if (!hasBook) {
            cout<<"    (No books currently borrowed)\n";
        }
        cout<<"------------------------------\n";
    }
    if (!borrowed_yet)cout<<"No books borrowed yet.\n";
}
// This function was generated by AI, not by me
string getCurrentDateTime() {
    auto now = time(nullptr);
    auto localTime = localtime(&now);

    auto year = 1900 + localTime->tm_year;
    auto month = 1 + localTime->tm_mon;
    auto day = localTime->tm_mday;
    auto hour = localTime->tm_hour;
    auto minute = localTime->tm_min;

    string period = (hour >= 12) ? "PM" : "AM";
    if (hour > 12) hour -= 12;
    if (hour == 0) hour = 12;

    string minuteStr = (minute < 10 ? "0" : "") + to_string(minute);

    return to_string(year) + "/" + to_string(month) + "/" + to_string(day) +
           " - " + to_string(hour) + ":" + minuteStr + " " + period;
}
int main() {
    int choice;
    while (true) {
        cout<<"\n===========================================\n";
        cout<<"     LIBRARY MANAGEMENT SYSTEM\n";
        cout<<"===========================================\n";
        cout<<"1. Add Book\n";
        cout<<"2. Search Book by Full Name or Substring\n";
        cout<<"3. Print Who Borrowed Book by Name\n";
        cout<<"4. Print Library by ID\n";
        cout<<"5. Print Library by Name\n";
        cout<<"6. Add New User\n";
        cout<<"7. Borrow Book\n";
        cout<<"8. Return Book\n";
        cout<<"9. Print Users Report\n";
        cout<<"10. Exit\n";
        cout<<"Enter your choice[1 - 10]: ";
        cin>>choice;
        if (choice==1) {
            int id, quantity;
            string name;
            cout<<"Enter book ID: ";
            cin>>id;
            cout<<"Enter book name: ";
            cin.ignore();
            getline(cin, name);
            cout<<"Enter book quantity: ";
            cin>>quantity;
            cout<<addBook(id, name, quantity);
        }
        else if (choice==2) {
            string part;
            cout<<"Enter part of the book name to search: ";
            cin.ignore();
            getline(cin, part);
            searchBook(part);
        }
        else if (choice==3) {
            string bookName;
            cout<<"Enter book name: ";
            cin.ignore();
            getline(cin, bookName);
            printWhoBorrowedBookByName(bookName);
        }
        else if (choice==4) {
            printLibraryById();
        }
        else if (choice==5) {
            printLibraryByName();
        }
        else if (choice==6) {
            int national_id;
            string userName;
            cout<<"Enter National ID: ";
            cin>>national_id;
            cout<<"Enter user name: ";
            cin.ignore();
            getline(cin, userName);
            addUser(national_id, userName);
        }
        else if (choice==7) {
            int national_id;
            string bookName;
            cout<<"Enter National ID: ";
            cin>>national_id;
            cout<<"Enter book name to borrow: ";
            cin.ignore();
            getline(cin, bookName);
            userBorrowBook(national_id, bookName);
        }
        else if (choice==8) {
            int national_id;
            string bookName;
            cout<<"Enter National ID: ";
            cin>>national_id;
            cout<<"Enter book name to return: ";
            cin.ignore();
            getline(cin, bookName);
            userReturnBook(national_id, bookName);
        }
        else if (choice==9) {
            printUsers();
        }
        else if (choice==10) {
            cout<<"\nThank you for using the Library Management System. Goodbye!\n";
            break;
        }
        else {
            cout<<"Invalid choice! Please select a valid option from the menu.\n";
        }
    }

    return 0;
}