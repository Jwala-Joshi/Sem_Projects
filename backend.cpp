#include "backend.h"

#include<iostream>
#include<fstream>
#include<cstring>
#include<windows.h>
using namespace std;

//path where files are stored
string path ="E:/Programming/Qt/GymEase/datas/";

//login
user getUserDetails(char userName[], char password[] ){
    user u,temp;
    char n[100], uN[100], p[100];
    ifstream file;
    file.open(path + "user.txt",ios::in);
    if(!file){
        return temp;
    }
    while(file.getline(n,100)&&file.getline(uN,100)&&file.getline(p,100)){
        u.setData(n,uN,p);
        if(strcmp(u.getUserName(),userName)==0&&strcmp(u.getPassword(),password)==0){
            file.close();
            ifstream adminFile;
            adminFile.open(path + "admin.txt",ios::in);
            char adminUserName[100];
            while(adminFile.getline(adminUserName,100)){
                if(strcmp(adminUserName,userName)==0){
                    u.beAdmin();
                }
            }
            adminFile.close();
            return u;
        }
    }
    file.close();
    return temp;
}

//signup
bool setNewUser(user newUser){
    ofstream file;
    file.open(path + "user.txt",ios::app);
    if(!file){
        return false;
    }
    file << newUser.getName() << endl << newUser.getUserName() << endl << newUser.getPassword() << endl;
    file.close();
    if(newUser.getIsAdmin()){
        cout << "HI" << endl;
        Sleep(5000);
        ofstream adminFile;
        adminFile.open(path + "admin.txt",ios::app);
        if(!adminFile){
            return false;
        }
        adminFile << newUser.getUserName() << endl;
        adminFile.close();
    }
    return true;
}

//to add workout by admin
bool postWorkout(char title[],char details[][100]){
    ofstream file;
    file.open(path + "workout.txt",ios::app);
    if(!file){
        return false;
    }
    file << title << endl;
    for(int i=0; i<5; i++){
        file << details[i] << endl;
    }
    file.close();
    return true;
}

//workoutplans
userWorkout getUserWorkoutPlans(user u){
    userWorkout w;
    ifstream file;
    file.open(path + "userworkout.txt",ios::app);
    if(!file){
        cout << endl << "Workout Plan not available currently!";
        return w;
    }
    char username[100], title[100], details[5][100];
    while(file.getline(username,100)&&file.getline(title,100)&&file.getline(details[0],100)&&file.getline(details[1],100)
           &&file.getline(details[2],100)&&file.getline(details[3],100)&&file.getline(details[4],100)){
        if(strcmp(username,u.getUserName())==0){
            w.setUsername(username);
            w.setWorkoutTitle(title);
            w.setDetails(details);
        }
    }
    return w;
}

//returns the number of admin
int getAdminNumber(){
    int count = 0;
    ifstream file;
    file.open(path + "admin.txt",ios::in);
    if(!file){
        return 0;
    }
    char temp[100];
    while(file.getline(temp,100)){
        count++;
    }
    return count;
}
