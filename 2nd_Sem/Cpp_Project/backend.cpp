#include "backend.h"

#include<iostream>
#include<fstream>
#include<cstring>
#include<windows.h>
#include <QDebug>
using namespace std;

int workoutNumbers=0;

//path where files are stored
string path ="E:/Programming/Qt/Sem_Projects/2nd_Sem/Cpp_Project/datas/";

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

void hold(){// function used to hold screen
    char choice;
    fflush(stdin);
    cin >> choice;
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

//username change
void changeUsername(user& u, char usern[100]){
    int userCount = 0, i = 0, flag = 0;
    char username[100],name[100],password[100],newUsername[100],oldUsername[100];
    strcpy(oldUsername,u.getUserName());
    // cout << "Enter your new username: ";
    // fflush(stdin);
    // cin.getline(newUsername,100);
    strcpy(newUsername,usern);

    ifstream file;
    file.open(path +"user.txt",ios::in);
    while(file.getline(name,100)&&file.getline(username,100
                                                   )&&file.getline(password,100)){
        userCount++;
    }
    file.close();
    user users[userCount];
    file.open(path +"user.txt",ios::in);
    while(file.getline(name,100)&&file.getline(username,100
                                                   )&&file.getline(password,100)){
        users[i].setData(name,username,password);
        if(flag == 0){
            if(strcmp(users[i].getUserName(),u.getUserName())==0){
                users[i].setUsername(newUsername);
                u.setUsername(newUsername);
                flag = 1;
            }
        }
        i++;
    }
    file.close();
    ofstream file2;
    file2.open(path +"user.txt",ios::trunc);
    for(i=0;i<userCount;i++){
        file2 << users[i].getName() << endl;
        file2 << users[i].getUserName() << endl;
        file2 << users[i].getPassword() << endl;
    }
    file2.close();
    ifstream challengeFile;
    challengeFile.open(path +"userchallenge.txt",ios::in);
    char uName[100], title[100], details[5][100], reps[5][100];
    int cCount = 0;
    while(challengeFile.getline(uName,100)&&
           challengeFile.getline(title,100)&&
           challengeFile.getline(details[0],100)&&challengeFile.getline(reps[0],100)&&
           challengeFile.getline(details[1],100)&&challengeFile.getline(reps[1],100)&&
           challengeFile.getline(details[2],100)&&challengeFile.getline(reps[2],100)&&
           challengeFile.getline(details[3],100)&&challengeFile.getline(reps[3],100)&&
           challengeFile.getline(details[4],100)&&challengeFile.getline(reps[4],100)){
        cCount++;
    }
    challengeFile.close();
    userChallenge c[cCount];
    i = 0;
    flag = 0;
    challengeFile.open(path +"userchallenge.txt",ios::in);
    while(challengeFile.getline(uName,100)&&
           challengeFile.getline(title,100)&&
           challengeFile.getline(details[0],100)&&challengeFile.getline(reps[0],100)&&
           challengeFile.getline(details[1],100)&&challengeFile.getline(reps[1],100)&&
           challengeFile.getline(details[2],100)&&challengeFile.getline(reps[2],100)&&
           challengeFile.getline(details[3],100)&&challengeFile.getline(reps[3],100)&&
           challengeFile.getline(details[4],100)&&challengeFile.getline(reps[4],100)){
        c[i].setUsername(uName);
        c[i].setTitle(title);
        c[i].setDetails(details);
        c[i].setReps(reps);
        if(flag == 0){
            if(strcmp(oldUsername,c[i].getUsername())==0){
                c[i].setUsername(newUsername);
                flag = 1;
            }
        }
        i++;
    }
    challengeFile.close();
    ofstream cFile;
    cFile.open(path +"userchallenge.txt",ios::trunc);
    for(i = 0; i<cCount; i++){
        cFile << c[i].getUsername() << endl;
        cFile << c[i].getTitle() << endl;
        char (&details)[5][100] = c[i].getDetails();
        char (&reps)[5][100] = c[i].getReps();
        cFile << details[0] << endl;
        cFile << reps[0] << endl;
        cFile << details[1] << endl;
        cFile << reps[1] << endl;
        cFile << details[2] << endl;
        cFile << reps[2] << endl;
        cFile << details[3] << endl;
        cFile << reps[3] << endl;
        cFile << details[4] << endl;
        cFile << reps[4] << endl;
    }
    cFile.close();
    ifstream workoutFile;
    workoutFile.open(path +"userworkout.txt",ios::in);
    int wCount = 0;
    while(workoutFile.getline(uName,100)&&
           workoutFile.getline(title,100)&&
           workoutFile.getline(details[0],100)&&
           workoutFile.getline(details[1],100)&&
           workoutFile.getline(details[2],100)&&
           workoutFile.getline(details[3],100)&&
           workoutFile.getline(details[4],100)){
        wCount++;
    }
    workoutFile.close();
    userWorkout w[wCount];
    i = 0;
    flag = 0;
    workoutFile.open(path +"userworkout.txt",ios::in);
    while(workoutFile.getline(uName,100)&&
           workoutFile.getline(title,100)&&
           workoutFile.getline(details[0],100)&&
           workoutFile.getline(details[1],100)&&
           workoutFile.getline(details[2],100)&&
           workoutFile.getline(details[3],100)&&
           workoutFile.getline(details[4],100)){
        w[i].setUsername(uName);
        w[i].setWorkoutTitle(title);
        w[i].setDetails(details);
        if(flag == 0){
            if(strcmp(oldUsername,w[i].getUsername())==0){
                w[i].setUsername(newUsername);
                flag = 1;
            }
        }
        i++;
    }
    workoutFile.close();
    ofstream wFile;
    wFile.open(path +"userworkout.txt",ios::trunc);
    for(i = 0; i<wCount; i++){
        wFile << w[i].getUsername() << endl;
        wFile << w[i].getWorkoutTitle() << endl;
        char (&Details)[5][100] = w[i].getDetails();
        wFile << Details[0] << endl;
        wFile << Details[1] << endl;
        wFile << Details[2] << endl;
        wFile << Details[3] << endl;
        wFile << Details[4] << endl;
    }
    wFile.close();
    cout << "Your username is successfully changed to " << newUsername << endl;
    // hold();
}

//name change
void changeName(user& u,char Name[100]){
    int userCount = 0, i = 0, flag = 0;
    char username[100],name[100],password[100],newName[100];
    // cout << "Enter your new Name: ";
    // fflush(stdin);
    // cin.getline(newName,100);

    strcpy(newName,Name);
    ifstream file;
    file.open(path + "user.txt",ios::in);
    while(file.getline(name,100)&&file.getline(username,100
                                                   )&&file.getline(password,100)){
        userCount++;
    }
    file.close();
    user users[userCount];
    file.open(path + "user.txt",ios::in);
    while(file.getline(name,100)&&file.getline(username,100
                                                   )&&file.getline(password,100)){
        users[i].setData(name,username,password);
        if(flag == 0){
            if(strcmp(users[i].getUserName(),u.getUserName())==0){
                users[i].setName(newName);
                u.setName(newName);
                flag = 1;
            }
        }
        i++;
    }
    file.close();
    ofstream file2;
    file2.open(path + "user.txt",ios::trunc);
    for(i=0;i<userCount;i++){
        file2 << users[i].getName() << endl;
        file2 << users[i].getUserName() << endl;
        file2 << users[i].getPassword() << endl;
    }
    file2.close();
    cout << "Your name is successfully changed to " << newName << endl;
    // cout << "Enter anything to exit: ";
    // hold();
}

//password change
void changePassword(user& u,char pass[100]){
    int userCount = 0, i = 0, flag = 0;
    char username[100],name[100],password[100],newPassword[100];
    // cout << "Enter your new Password: ";
    // fflush(stdin);
    // cin.getline(newPassword,100);
    strcpy(newPassword,pass);
    ifstream file;
    file.open(path + "user.txt",ios::in);
    while(file.getline(name,100)&&file.getline(username,100
                                                   )&&file.getline(password,100)){
        userCount++;
    }
    file.close();
    user users[userCount];
    file.open(path + "user.txt",ios::in);
    while(file.getline(name,100)&&file.getline(username,100
                                                   )&&file.getline(password,100)){
        users[i].setData(name,username,password);
        if(flag == 0){
            if(strcmp(users[i].getUserName(),u.getUserName())==0){
                users[i].setPassword(newPassword);
                u.setPassword(newPassword);
                flag = 1;
            }
        }
        i++;
    }
    file.close();
    ofstream file2;
    file2.open(path + "user.txt",ios::trunc);
    for(i=0;i<userCount;i++){
        file2 << users[i].getName() << endl;
        file2 << users[i].getUserName() << endl;
        file2 << users[i].getPassword() << endl;
    }
    file2.close();
    cout << "Your password is successfully changed to " << newPassword << endl;
    // cout << "Enter anything to exit: ";
    // hold();
}
