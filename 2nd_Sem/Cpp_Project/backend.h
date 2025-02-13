#ifndef BACKEND_H
#define BACKEND_H

#pragma once

#include<iostream>
#include<fstream>
#include<cstring>
#include<windows.h>
using namespace std;

class user{
    char name[100];
    char userName[100];
    char password[100];
    bool isMember;
    bool isAdmin;
    int memberExpiry;
    int key;
public:
    user(){
        strcpy(name,"");
        strcpy(userName,"");
        isMember = false;
        isAdmin = false;
    }
    void setData(char name[], char userName[], char password[], int key=0){
        strcpy(this->name,name);
        strcpy(this->userName,userName);
        strcpy(this->password,password);
        this->key = key;
        if(strcmp(this->password,"admin123")==0&&this->key==69){
            isAdmin = true;
        }
        else{
            isAdmin = false;
        }
    }
    void setUsername(char username[]){
        strcpy(this->userName,username);
    }
    void setName(char name[]){
        strcpy(this->name,name);
    }
    void setPassword(char pass[]){
        strcpy(this->password,pass);
    }
    void beAdmin(){
        isAdmin = true;
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
    int getMemberExpiry(){
        return memberExpiry;
    }
    bool getIsMember(){
        return isMember;
    }
    bool getIsAdmin(){
        return isAdmin;
    }
};

class userWorkout{
    char username[100];
    char workoutTitle[100];
    char details[5][100];
public:
    userWorkout(){
        strcpy(username,"");
        strcpy(workoutTitle,"NAN");
    }
    void setUsername(char u[]){
        strcpy(username,u);
    }
    void setWorkoutTitle(char t[]){
        strcpy(workoutTitle,t);
    }
    void setDetails(char d[][100]){
        for(int i=0; i<5; i++){
            strcpy(details[i],d[i]);
        }
    }
    char* getUsername(){
        return username;
    }
    char* getWorkoutTitle(){
        return workoutTitle;
    }
    char (&getDetails())[5][100]{
        return details;
    }
};

class userChallenge{
    char username[100];
    char title[100];
    char details[5][100];
    char reps[5][100];
public:
    void setUsername(char u[]){
        strcpy(username,u);
    }
    void setTitle(char t[]){
        strcpy(title,t);
    }
    void setDetails(char d[][100]){
        for(int i=0; i<5; i++){
            strcpy(details[i],d[i]);
        }
    }
    void setReps(char r[][100]){
        for(int i=0; i<5; i++){
            strcpy(reps[i],r[i]);
        }
    }
    char* getUsername(){
        return username;
    }
    char* getTitle(){
        return title;
    }
    char (&getDetails())[5][100]{
        return details;
    }
    char (&getReps())[5][100]{
        return reps;
    }
};

user getUserDetails(char [], char [] );
void hold();
bool setNewUser(user );
bool postWorkout(char [],char [][100]);
userWorkout getUserWorkoutPlans(user );
int getAdminNumber();
void changeUsername(user& u, char [100]);
void changeName(user& u, char [100]);
void changePassword(user& u, char [100]);

#endif // BACKEND_H
