#include<bits/stdc++.h>

using namespace std;
vector<deque<pair<string,string>>> patients(21);
string addPatient(int specialization, string name,int status) {
    // all possible return value
    const vector<string> addMessages = {
        "",
        "Patient added successfully",
        "Invalid specialization. Please enter a valid specialization between 1 and 20.",
        "Sorry, this specialization is full (maximum 5 patients).",
        "Invalid status. Please enter 0 for regular or 1 for urgent."
    };

    if (specialization>=1 && specialization<=20) {
        // if status is wrong
        if (status<0 || status>1)return addMessages[4];
        if (patients[specialization].size()<5) {
            if (status==0)
                patients[specialization].push_back({name,"regular"});
            else if (status==1)
                patients[specialization].push_front({name,"urgent"});
        }
        else return addMessages[3];
    }
    else return addMessages[2];
    return addMessages[1];
}
void printAllPatients() {
    for (int i=1;i<=20;i++) {
        if (!patients[i].empty()) {
            cout<<"There are "<<patients[i].size()<<" patients in specialization "<<i<<endl;
            for (int j=0;j<patients[i].size();j++) {
                cout << patients[i][j].first<<" "<<patients[i][j].second<<endl;
            }
        }
    }
}

void getNextPatient(int specialization) {
    if (specialization>=1 && specialization<=20) {
        if (patients[specialization].empty())
            cout << "No patients at the moment. Have rest, Dr\n";
        else {
            cout << patients[specialization].front().first << " please go with the Dr\n";
            patients[specialization].pop_front();
        }
    }
    else cout<<"Invalid specialization. Please enter a valid specialization between 1 and 20.\n";
}

int main() {
    int op;
   while (true) {
       cout << "Enter your choice:\n";
       cout << "1) Add new patient\n";
       cout << "2) Print all patients\n";
       cout << "3) Get next patient\n";
       cout << "4) Exit\n";
       cin>>op;
       if (op==1) {
           cout<<"Enter specialization, name, status: ";
           int specialization,status;
           string name;
           cin>>specialization>>name>>status;
           cout<<addPatient(specialization,name,status)<<endl;
       }
       else if (op==2) {
           printAllPatients();
       }
       else if (op==3) {
           cout<<"Enter specialization: ";
           int specialization;
           cin>>specialization;
           getNextPatient(specialization);
       }
       else if (op==4)
           break;
       else cout << "Invalid choice! Please enter a number between 1 and 4.\n";

       cout<<"*************************************************\n";
   }
}