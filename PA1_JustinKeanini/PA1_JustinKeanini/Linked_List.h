#pragma once
#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

//NODE CLASS
template<class A, class B>
class Node
{
private:
	A _commands;
	B _descriptions;
	Node<A, B>* _next;

public:
	Node(const A commands, const B description, Node<A, B>* next); //Constructor
	~Node(); //Destructor 

	A getCommands();
	B getDescriptions();
	Node<A, B>* getNext();

	void setNext(Node<A, B>* newNext);
};
//constructor
template<class A, class B>
Node<A, B>::Node(const A commands, const B description, Node<A, B>* next) :_commands(commands), _descriptions(description), _next(next) {}
//destructor
template <class A, class B>
Node<A, B>::~Node() {};
//getters
template <class A, class B>
A Node<A, B>::getCommands() {
	return this->_commands;
}
template <class A, class B>
B Node<A, B>::getDescriptions() {
	return this->_descriptions;
}
template<class A, class B>
Node<A, B>* Node<A, B>::getNext() {
	return this->_next;
}
//setters
template<class A, class B>
void Node<A, B>::setNext(Node<A, B>* newNext) {
	this->_next = newNext;
}





//LIST CLASS
template<class A, class B>
class List
{
private:
	Node<A, B>* _head;
	int _size;
	vector<Node<A, B>*> recurrent;
public:

	List();
	~List(); //Destructor

	void insert();
	void remove();
	void playGame(string name, int& points);
	Node<A, B>* randomize(Node<A, B>* wrong1, Node<A, B>* wrong2);
	void display(int random, Node<A, B>* correct, Node<A, B>* wrong1, Node<A, B>* wrong2);
	void writeOut();

	Node<A, B>* getHead();
	int getSize() const;
};
//constructor
template<class A, class B>
List<A, B>::List() :_size(0) {
	Node<A, B>* newNode = nullptr;
	fstream cfile;
	cfile.open("commands.csv", fstream::in);

	string line;

	while (getline(cfile, line))
	{
		stringstream ss(line);
		string commands, descriptions;
		getline(ss, commands, ',');
		getline(ss, descriptions);

		newNode = new Node<A, B>(commands, descriptions, this->_head);
		this->_size++;
		this->_head = newNode;
	}
}

template<class A, class B>
List<A, B>::~List() {
	Node<A, B>* pCur = this->getHead(), *pPrev = nullptr;
	for (int i = 0; i < _size; i++) {
		pPrev = pCur;
		pCur = pCur->getNext();
		delete pPrev;
	}
}

//insert new command/descriptions
template<class A, class B>
void List<A, B>::insert() {
	string newC;
	cout << "Enter the name of the command you would like to add:" << endl;
	cin >> newC;

	Node<A, B>* pCur = _head;

	for (int i = 0; i < _size; ++i) {
		if (newC == pCur->getCommands()) {
			cout << "Error! Command already exists. Please try a different command." << endl;
			return;
		}
		pCur = pCur->getNext();
	}

	string newD;
	cout << "Enter the description for your command: " << endl;
	cin >> newD;

	Node<A, B>* tmp = new Node<A, B>(newC, newD, this->_head);
	if (_head == NULL)
	{
		_head = tmp;
	}
	else
	{
		_head = tmp;
	}
	this->_size++;

}
//remove command/descriptions
template<class A, class B>
void List<A, B>::remove() {
	string removeC;
	cout << "What command would you like to remove?" << endl;
	cin >> removeC;

	Node<A, B>* pCur = _head;
	Node<A, B>* pPrev = nullptr;
	for (int i = 0; i < _size; ++i) {
		if (removeC == pCur->getCommands()) {
			pPrev->setNext(pCur->getNext());
			delete pCur;
			cout << "Successfully removed command" << endl;
			return;
		}
		pCur = pCur->getNext();
	}

	cout << "Error! Command does not exist" << endl;
}
//play game
template<class A, class B>
void List<A, B>::playGame(string name, int& points) {
	int gameSize = 0, response;
	do {
		cout << "Enter the number of rounds you would like to play: (NOTE - Has to be between 5-30)" << endl;
		cin >> gameSize;
	} while (gameSize < 5 || gameSize > 30);

	for (int i = 0; i < gameSize; ++i) {
		int ans = rand() % 3;
		Node<A, B>* correct, * wrong1, * wrong2;

		do {
			correct = randomize(nullptr, nullptr);
		} while (find(recurrent.begin(), recurrent.end(), correct) != recurrent.end());
		wrong1 = randomize(correct, nullptr);
		wrong2 = randomize(correct, wrong1);

		display(ans, correct, wrong1, wrong2);
		cin >> response;
		if (response == ans + 1) {
			cout << "Correct! - " << correct->getDescriptions()<<endl;
			cout << "Points: " << ++points << endl;;
		}
		else {
			cout << "Incorrect! - "<< correct->getDescriptions()<<endl;
			cout << "Points: "<<--points << endl;;
		}
		cout << "\n\n ------------------------------------------------------------------------------------ ";
		cout << "\n\n";
	}
	this->recurrent.clear();

}
//randomize order fucntion
template<class A, class B>
Node<A, B>* List<A, B>::randomize(Node<A, B>* wrong1, Node<A, B>* wrong2) {
	Node<A, B>* tmp = this->_head;

	int randomSize = rand() % _size;
	do {
		for (int i = 0; i < randomSize; ++i) {
			tmp = tmp->getNext();
		}
	} while (tmp == wrong1 || tmp == wrong2);

	return tmp;
}
//display
template<class A, class B>
void List<A, B>::display(int random, Node<A, B>* correct, Node<A, B>* wrong1, Node<A, B>* wrong2) {
	bool choose = true;
	cout << correct->getCommands();
	for (int i = 0; i < 3; ++i) {
		cout << "\t\t" << i + 1 << '.';
		if (i == random) {
			cout << correct->getDescriptions();
		}
		else {
			if (choose) {
				cout << wrong1->getDescriptions();
				choose = !choose;
			}
			else {
				cout << wrong2->getDescriptions();
			}
		}
		cout << '\n';
	}
}
//write out
template<class A, class B>
void List<A, B>::writeOut() {
	fstream cfile;
	cfile.close();
	cfile.open("commands.csv", fstream::out);

	Node<A, B>* pCur = getHead();

	for (int i = 0; i < _size; ++i) {
		cfile << pCur->getCommands() << ',' << pCur->getDescriptions() << endl;
		pCur = pCur->getNext();
	}
}


//getters
template<class A, class B>
Node<A, B>* List<A, B>::getHead() {
	return this->_head;
}
template<class A, class B>
int List<A, B> ::getSize() const {
	return this->_size;
}


int main_menu()
{
	int option = 0;

	do
	{
		cout << "1.Game Rules" << endl;
		cout << "2.Play Game" << endl;
		cout << "3.Load Previous Game" << endl;
		cout << "4.Add Command" << endl;
		cout << "5.Remove Command" << endl;
		cout << "6.Exit" << endl;
		cin >> option;
	} while (option < 1 || option > 6);

	return option;
}
