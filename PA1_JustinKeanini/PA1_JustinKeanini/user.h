#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct user {
	string name;
	int points;
};

class User {
private:
	struct user* _arr;
	int _curUsers;
	fstream _ufile;

public:
	//constructor
	User();
	//destructor
	~User() {
		_ufile.close();
		if (_arr) 
			delete[] _arr;
	}

	bool overRide(string name);
	int check(string name);
	void insert(string newUser, int points);
	void writeOut();

};

User::User():_curUsers(0) {
	_arr = new struct user[1];
	_ufile.open("profiles.csv", fstream::in);
	string line;

	while (getline(_ufile, line))
	{
		stringstream ss(line);
		string username, points;
		getline(ss, username, ',');
		getline(ss, points,'\n');
		insert(username, stoi(points));
		this->_curUsers++;
	}

}

bool User::overRide(string name) {
	for (int i = 0; i < _curUsers; ++i) {
		if (name == _arr[i].name) {
			_arr[i].points = 0;
			return true;
		}
	}
	return false;
}
//checking for previous user from file
int User::check(string name) {
	for (int i = 0; i < _curUsers; ++i) {
		if (name == _arr[i].name) {
			return _arr[i].points;
		}
	}
	return INT_MIN;
}
//inserting a new user to file
void User::insert(string newUser, int points) {
	_arr = new struct user[1 + _curUsers];

	for (int i = _curUsers; i > 0; --i) {
		_arr[i] = _arr[i - 1];
	}
	_arr[0].name = newUser;
	_arr[0].points = points;
}
//writing to profile
void User::writeOut() {
	_ufile.close();
	_ufile.open("profiles.csv", fstream::out);

	for (int i = 0; i < _curUsers; ++i) {
		_ufile << _arr[i].name << ',' << _arr[i].points << endl;
	}
}
