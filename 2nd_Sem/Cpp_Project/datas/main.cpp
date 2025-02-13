#include<iostream>
#include<cstring>
#include<cstdlib>
#include<windows.h>
#include "backend.h"
using namespace std;

user signup(){
	user newUser;
	char name[100],userName[100],password[100];
	int key;
	cout << "Enter name: ";
	cin.getline(name,100);
	cout << "Enter user name: ";
	cin.getline(userName,100);
	cout << "Enter password: ";
	cin.getline(password,100);
	cout << "Enter your unique key[1-10]: ";
	cin >> key;
	cin.ignore();
	newUser.setData(name,userName,password,key);
	bool isRegistered = setNewUser(newUser);//in header file
	if(!isRegistered){
		cout << "Signup Unsuccessful!";
	}
	system("cls");
	cout << "Signup Successfully!";
	return newUser;
}

user login(){
	char userName[100];
	char password[100];
	cout << "Enter your User Name: ";
	fflush(stdin);
	cin.getline(userName,100);
	cout << "Enter your password: ";
	fflush(stdin);
	cin.getline(password,100);
	user u = getUserDetails(userName,password);//in header file
	if(strcmp(u.getUserName(),"")==0){
		system("cls");
		cout << "User Not Found! Signup" << endl;
		u = signup();
	}
	return u;
}

void dashboard(user u){
	system("cls");
	cout << "User: " << u.getUserName() << endl;
	cout << "Ongoing user Workout Plan: " << endl;
	userWorkout w;
	w = getUserWorkoutPlans(u);
	cout << "Title: " << w.getWorkoutTitle() << endl;
	char (&details)[5][100] = w.getDetails();
	for(int i=0;i<5;i++){
		cout << i+1 << ". " << details[i] << endl;
	}
	cout << "Ongoing Challenge: " << endl;
	cout << "Enter anything to go back: ";
	hold();
}

void workoutPlans(user u){
	system("cls");
	cout << "Current Workout Plans are:" << endl;
	ifstream file;
	file.open("workout.txt",ios::in);
	int i = 0, flag = 0;//flag is used for checking if user already has a workout plan
	char title[100],username[100];
	char details[5][100];
	while(file.getline(title,100)&&file.getline(details[0],100)&&file.getline(details[1],100)
	&&file.getline(details[2],100)&&file.getline(details[3],100)&&file.getline(details[4],100)){
		i++;
		cout << i << ". Title: " << title << endl;
		cout << "Workouts: " << endl;
		for(int j = 0; j<5; j++){
			cout << j+1 << ". " << details[j] << endl;
		}
		cout << endl;
	}
	file.close();
	if(i==0){
		cout << "No Workout Available!";
		cout << endl << "Enter anything to go back: ";
		hold();
		return;
	}
	ifstream temp;
	temp.open("userworkout.txt",ios::in);
	while(temp.getline(username,100)&&temp.getline(title,100)&&temp.getline(details[0],100)&&temp.getline(details[1],100)
	&&temp.getline(details[2],100)&&temp.getline(details[3],100)&&temp.getline(details[4],100)){
		if(strcmp(username,u.getUserName())==0){
			flag = 1;
		}
	}
	temp.close();
	if(flag==1){
		cout << "You already have a workout plan! Press anyting to exit: ";
		hold();
		return;
	}
	int choice;
	retry:
	cout << "Press a workout to add it to your workout plans/ Press 0 to exit: ";
	cin >> choice;
	if(choice == 0){
		return;
	}
	if(choice > i){
		cout << "Ivalid Input! Try again" << endl;
		goto retry;
	}
	ofstream userFile;
	userFile.open("userworkout.txt",ios::app);
	file.open("workout.txt",ios::in);
	int k = 0;
	while(file.getline(title,100)&&file.getline(details[0],100)&&file.getline(details[1],100)
	&&file.getline(details[2],100)&&file.getline(details[3],100)&&file.getline(details[4],100)){
		k++;
		if(k == choice){
			userFile << u.getUserName() << endl;
			userFile << title << endl;
			userFile << details[0] << endl;
			userFile << details[1] << endl;
			userFile << details[2] << endl;
			userFile << details[3] << endl;
			userFile << details[4] << endl;
		}
	}
	file.close();
	userFile.close();
}

void challenges(user u){
	system("cls");
	cout << "Current Challenges are:" << endl;
	ifstream file;
	file.open("challenge.txt",ios::in);
	int i = 0, flag = 0;//flag is used for checking if user already has a challenge
	char title[100],username[100];
	char details[5][100];
	char reps[5][100];
	while(file.getline(title,100)&&
	file.getline(details[0],100)&&file.getline(reps[0],100)&&
	file.getline(details[1],100)&&file.getline(reps[1],100)&&
	file.getline(details[2],100)&&file.getline(reps[2],100)&&
	file.getline(details[3],100)&&file.getline(reps[3],100)&&
	file.getline(details[4],100)&&file.getline(reps[4],100)){
		i++;
		cout << i << ". Title: " << title << endl;
		cout << "Workouts: " << endl;
		for(int j = 0; j<5; j++){
			cout << j+1 << ". " << details[j] << "   ";
			cout << reps[j] << " reps" << endl;
		}
		cout << endl;
	}
	file.close();
	if(i==0){
		cout << "No Challenges Available!";
		cout << endl << "Enter anything to go back: ";
		hold();
		return;
	}
	ifstream temp;
	temp.open("userchallenge.txt",ios::in);
	while(temp.getline(username,100)&&
	temp.getline(title,100)&&
	temp.getline(details[0],100)&&temp.getline(reps[0],100)&&
	temp.getline(details[1],100)&&temp.getline(reps[1],100)&&
	temp.getline(details[2],100)&&temp.getline(reps[2],100)&&
	temp.getline(details[3],100)&&temp.getline(reps[3],100)&&
	temp.getline(details[4],100)&&temp.getline(reps[4],100)){
		if(strcmp(username,u.getUserName())==0){
			flag = 1;
		}
	}
	temp.close();
	if(flag==1){
		cout << "You already have ongoing anyting to exit: ";
		hold();
		return;
	}
	int choice;
	retry:
	cout << "Press a challenge to add it to your challenge/ Press 0 to exit: ";
	cin >> choice;
	if(choice == 0){
		return;
	}
	if(choice > i){
		cout << "Ivalid Input! Try again" << endl;
		goto retry;
	}
	ofstream userFile;
	userFile.open("userchallenge.txt",ios::app);
	file.open("challenge.txt",ios::in);
	int k = 0;
	while(file.getline(title,100)&&
	file.getline(details[0],100)&&file.getline(reps[0],100)&&
	file.getline(details[1],100)&&file.getline(reps[1],100)&&
	file.getline(details[2],100)&&file.getline(reps[2],100)&&
	file.getline(details[3],100)&&file.getline(reps[3],100)&&
	file.getline(details[4],100)&&file.getline(reps[4],100)){
		k++;
		if(k == choice){
			userFile << u.getUserName() << endl;
			userFile << title << endl;
			userFile << details[0] << endl;
			userFile << reps[0] << endl;
			userFile << details[1] << endl;
			userFile << reps[1] << endl;
			userFile << details[2] << endl;
			userFile << reps[2] << endl;
			userFile << details[3] << endl;
			userFile << reps[3] << endl;
			userFile << details[4] << endl;
			userFile << reps[4] << endl;
		}
	}
	file.close();
	userFile.close();
}

void calorieTracker(){
	system("cls");
	cout << "List of food with their respective calorie are:" << endl;
	ifstream calorieFile;
	calorieFile.open("calorie.txt",ios::in);
	char food[100], calorie[10];
	while(calorieFile.getline(food,100)&&calorieFile.getline(calorie,10)){
		cout << food << endl;
		cout << "Calorie: " << calorie << endl;
	}
	calorieFile.close();
	cout << "Enter anything to exit: ";
	hold();
}

void settings(user& u){
	system("cls");
	char choice;
	retry:
	cout << "Settings panel of " << u.getUserName() << endl;
	cout << "Your details: " << endl;
	cout << "Name: " << u.getName() << endl;
	cout << "Username: " << u.getUserName() << endl;
	cout << "Password: " << u.getPassword() << endl;
	cout << "Options:" << endl;
	cout << "1. Change Username" << endl;
	cout << "2. Change Name" << endl;
	cout << "3. Change Password" << endl;
	cout << "4. Exit" << endl;
	cout << "Enter your choice: ";
	fflush(stdin);
	cin >> choice;
	switch (choice){
		case '1':
			changeUsername(u);
		break;
		case '2':
			chaneName(u);
		break;
		case '3':
			changePassword(u);
		break;
		case '4':
			return;
		break;
		default:
			cout << "Invalid Input!" << endl;
			goto retry;
	}
}

int homepage(user& u){
	char choice;
	char* userName = u.getUserName();
	system("cls");
	retry:
	cout << "Welcome " <<  userName << "!" << endl;
	cout << "Choose an option: " << endl;
	cout << "1. Dashboard" << endl;
	cout << "2. View Workout Plans" << endl;
	cout << "3. View Challenges" << endl;
	cout << "4. Calorie Tracker" << endl;
	cout << "5. Settings" << endl;
	cout << "6. Log Out" << endl;
	cout << "Enter your choice: ";
	fflush(stdin);
	cin >> choice;
	switch (choice){
		case '1':
			dashboard(u);
		break;
		case '2':
			workoutPlans(u);
		break;
		case '3':
			challenges(u);
		break;
		case '4':
			calorieTracker();
		break;
		case '5':
			settings(u);
		break;
		case '6':
			return 0;
		break;
		default:
			system("cls");
			cout << "Invalid Input!";
			goto retry;	
	}
	return 1;
}

void addWorkout(){
	char title[100];
	char workout[5][100];
	system("cls");
	retry:
	cout << "Enter title of Workout Plan: ";
	fflush(stdin);
	cin.getline(title,100);
	for(int i=0; i<5; i++){
		cout << "Enter workout " << i+1 << " : ";
		fflush(stdin);
		cin.getline(workout[i],100);
	}
	if(postWorkout(title,workout)){
		cout << "Workout Successfully Added!";
		Sleep(1000);
		return;
	}
	else{
		cout << "Workout not added try again!" << endl;
		goto retry;
	}
}

void removeWorkout(){
	system("cls");
	cout << "Current Workout Plans are:" << endl;
	ifstream file;
	file.open("workout.txt",ios::in);
	int i = 0;
	char title[100];
	char details[5][100];
	while(file.getline(title,100)&&file.getline(details[0],100)&&file.getline(details[1],100)
	&&file.getline(details[2],100)&&file.getline(details[3],100)&&file.getline(details[4],100)){
		i++;
		cout << i << ". Title: " << title << endl;
		cout << "Workouts: " << endl;
		for(int j = 0; j<5; j++){
			cout << j+1 << ". " << details[j] << endl;
		}
		cout << endl;
	}
	file.close();
	if(i==0){
		cout << "No Workout Available!" << endl;
		cout << "Enter anything to go back: ";
		hold();
		return;
	}
	userWorkout w[i];
	retry:
	cout << endl << endl << "Enter the number of workout you want to delete/ Enter 0 to exit: ";
	int temp;
	cin >> temp;
	if(temp == 0){
		return;
	}
	else if(temp > i){
		cout << "Invalid Input! Try again" << endl;
		goto retry;
	}
	file.open("workout.txt",ios::in);
	int k = 0;
	while(file.getline(title,100)&&file.getline(details[0],100)&&file.getline(details[1],100)
	&&file.getline(details[2],100)&&file.getline(details[3],100)&&file.getline(details[4],100)){
		w[k].setWorkoutTitle(title);
		w[k].setDetails(details);
		k++;
	}
	file.close();
	ofstream file2;
	file2.open("workout.txt",ios::trunc);
	for(k = 0; k<i; k++){
		if(temp == k+1){
			continue;
		}
		else{
			file2 << w[k].getWorkoutTitle() << endl;
			char (&workoutDetails)[5][100] = w[k].getDetails();
			file2 << workoutDetails[0] << endl;
			file2 << workoutDetails[1] << endl;
			file2 << workoutDetails[2] << endl;
			file2 << workoutDetails[3] << endl;
			file2 << workoutDetails[4] << endl;
		}
	}
}

void addChallenges(){
	system("cls");
	char title[100],details[5][100];
	char reps[5][100];
	ofstream file;
	file.open("challenge.txt",ios::app);
	cout << "Enter the title of challenge: ";
	fflush(stdin);
	cin.getline(title,100);
	file << title << endl;
	for(int i=0; i<5; i++){
		cout << "Enter workout " << i+1 << ": ";
		fflush(stdin);
		cin.getline(details[i],100);
		file << details[i] << endl;
		cout << "Enter Reps: ";
		fflush(stdin);
		cin.getline(reps[i],100);
		file << reps[i] << endl;
	}
	cout << "Workout Challenge successfully added!";
	cout << "Enter anything to go back: ";
	hold();
}

void removeChallenges(){
	system("cls");
	cout << "Current Challenges are:" << endl;
	ifstream file;
	file.open("challenge.txt",ios::in);
	int i = 0;
	char title[100];
	char details[5][100];
	char reps[5][100];
	while(file.getline(title,100)&&
	file.getline(details[0],100)&&file.getline(reps[0],100)&&
	file.getline(details[1],100)&&file.getline(reps[1],100)&&
	file.getline(details[2],100)&&file.getline(reps[2],100)&&
	file.getline(details[3],100)&&file.getline(reps[3],100)&&
	file.getline(details[4],100)&&file.getline(reps[4],100)){
		i++;
		cout << i << ". Title: " << title << endl;
		cout << "Workouts: " << endl;
		for(int j = 0; j<5; j++){
			cout << j+1 << ". " << details[j] << "   ";
			cout << reps[j] << " reps" << endl;
		}
		cout << endl;
	}
	file.close();
	if(i==0){
		cout << "No Challenges available!" << endl;
		cout << "Enter anything to go back: ";
		hold();
		return;
	}
	userChallenge c[i];
	retry:
	cout << endl << endl << "Enter the number of challenge you want to delete/ Enter 0 to exit: ";
	int temp;
	cin >> temp;
	if(temp == 0){
		return;
	}
	else if(temp > i){
		cout << "Invalid Input! Try again" << endl;
		goto retry;
	}
	file.open("challenge.txt",ios::in);
	int k = 0;
	while(file.getline(title,100)&&
	file.getline(details[0],100)&&file.getline(reps[0],100)&&
	file.getline(details[1],100)&&file.getline(reps[1],100)&&
	file.getline(details[2],100)&&file.getline(reps[2],100)&&
	file.getline(details[3],100)&&file.getline(reps[3],100)&&
	file.getline(details[4],100)&&file.getline(reps[4],100)){
		c[k].setTitle(title);
		c[k].setDetails(details);
		c[k].setReps(reps);
		k++;
	}
	file.close();
	ofstream file2;
	file2.open("challenge.txt",ios::trunc);
	for(k = 0; k<i; k++){
		if(temp == k+1){
			continue;
		}
		else{
			file2 << c[k].getTitle() << endl;
			char (&challengeDetails)[5][100] = c[k].getDetails();
			char (&reps)[5][100] = c[k].getReps();
			file2 << challengeDetails[0] << endl;
			file2 << reps[0] << endl;
			file2 << challengeDetails[1] << endl;
			file2 << reps[1] << endl;
			file2 << challengeDetails[2] << endl;
			file2 << reps[2] << endl;
			file2 << challengeDetails[3] << endl;
			file2 << reps[3] << endl;
			file2 << challengeDetails[4] << endl;
			file2 << reps[4] << endl;
		}
	}
}

void viewCustomer(){
	system("cls");
	int adminCount = getAdminNumber(), i=0, flag=0;
	char adminUsername[adminCount][100];
	ifstream adminFile;
	adminFile.open("admin.txt",ios::in);
	while(adminFile.getline(adminUsername[i],100)){
		i++;
	}
	adminFile.close();
	ifstream file;
	file.open("user.txt",ios::in);
	char name[100],username[100],pass[100];
	cout << "List of users are: " << endl;
	i = 0;
	while(file.getline(name,100)&&file.getline(username,100)&&file.getline(pass,100)){
		for(int j=0; j<adminCount; j++){
			if(strcmp(adminUsername[j],username)==0){
				flag = 1;
			}
		}
		if(flag == 0){
			cout << i+1 << ". " << name << endl;
			i++;
		}
		else{
			flag = 0;
		}
	}
	cout << "Enter anyting to exit: ";
	hold();
}

void addCalorie(){
	system("cls");
	cout << "Add food and its calorie:" << endl;
	char food[100], calorie[10];
	cout << "Enter food name: ";
	fflush(stdin);
	cin.getline(food,100);
	cout << "Enter its calorie: ";
	fflush(stdin);
	cin.getline(calorie,10);
	ofstream calorieFile;
	calorieFile.open("calorie.txt",ios::out);
	calorieFile << food << endl << calorie << endl;
}

int adminHomepage(user u){
	system("cls");
	char choice;
	retry:
	cout << "Welcome admin " << u.getUserName() << endl;
	cout << "Admin Features:" << endl;
	cout << "1. Add Workout Plan" << endl;
	cout << "2. Add Challenges" << endl;
	cout << "3. View Customers" << endl;
	cout << "4. Remove Workouts" << endl;
	cout << "5. Remove Challenges" << endl;
	cout << "6. Add food calorie" << endl;
	cout << "7. Log Out" << endl;
	cout << "Enter your choice: ";
	fflush(stdin);
	cin >> choice;
	switch (choice){
		case '1':
			addWorkout();
		break;
		case '2':
			addChallenges();
		break;
		case '3':
			viewCustomer();
		break;
		case '4':
			removeWorkout();
		break;
		case '5':
			removeChallenges();
		break;
		case '6':
			addCalorie();
		break;
		case '7':
			return 0;
		break;
		default:
			system("cls");
			cout << "Invalid Input! Try Again";
			goto retry;
	}
	return 1;
}

int main(){
	user u;
	int flag;
	u = login();
	if(u.getIsAdmin()){
		re1:
		flag = adminHomepage(u);
	}
	else{
		re2:
		flag = homepage(u);
	}
	if(flag == 0){
		system("cls");
		main();
	}
	else{
		if(u.getIsAdmin()){
			goto re1;
		}
		else{
			goto re2;
		}
	}
	return 0;
}
