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

