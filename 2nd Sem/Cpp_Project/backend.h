#ifndef BACKEND_H
#define BACKEND_H

#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class user{
    char name[100];
    char userName[100];
    char password[100];
    bool isMember;
    char memberExpiry[20];
    int key;
public:
    user(){
        strcpy(name,"");
        strcpy(userName,"");
        isMember = false;
        strcpy(memberExpiry,"N/A");
    }
    void setData(char name[], char userName[], char password[], int key=0){
        strcpy(this->name,name);
        strcpy(this->userName,userName);
        strcpy(this->password,password);
        this->key = key;
    }
    void beMember(int memberDuration){
        isMember = true;
        //strcpy(memberExpiry,calculateMemberExpiry(memberDuration));
    }
    char* getName(){
        return name;
    }
    char* getUserName(){
        return userName;
    }
    char* getPassword(){
        return password;
    }
    bool getIsMember(){
        return isMember;
    }
};

user getUserDetails(char userName[], char password[], int key){
    user u,temp;
    char n[100], uN[100], p[100];
    ifstream file;
    file.open("user.txt",ios::in);
    if(!file){
        return temp;
    }
    while(file.getline(n,100)&&file.getline(uN,100)&&file.getline(p,100)){
        u.setData(n,uN,p);
        if(strcmp(u.getUserName(),userName)==0&&strcmp(u.getPassword(),password)==0){
            file.close();
            return u;
        }
    }
    file.close();
    return temp;
}

bool setNewUser(user newUser){
    ofstream file;
    file.open("user.txt",ios::app);
    if(!file){
        return false;
    }
    file << newUser.getName() << endl << newUser.getUserName() << endl << newUser.getPassword() << endl;
    file.close();
    return true;
}

#endif // BACKEND_H
