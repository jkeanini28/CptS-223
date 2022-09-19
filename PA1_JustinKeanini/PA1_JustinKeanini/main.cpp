// PA1_JustinKeanini.cpp :
/*
* Advantages and Disadvantages of linked list:
* Advantages: 
-its a dynamic data structure so it can grow and shrink at runtime
* Disadvantages:
-traversing is slower than compared to an array, array can access at constant runtime

 Advantages and Disadvantages of array:
 * Advantages:
 -The search process can be applied to an array easier than a linked list
 * Disadvantages:
 -increasing size is less efficient than using an linked list
*/

#include "PA1_JustinKeanini.h"
#include "Linked_List.h"
#include "user.h"
#include "time.h"

using namespace std;

int main()
{
	List<string, string> list;
	User user;
	int size = list.getSize();
	int points = 0, option = 0;

	srand(time(NULL));
	do {
		option = main_menu();
		switch (option) {
		case 1:
			cout << "The objective of the game is to match Linux commands to appropriate descriptions of those commands.If a command is matched, then the player earns 1 point.The if the command is not matched, then the player loses a point.Yes, negative point totals are possible.The player selects the number of match questions at the beginning of the game.The game continue until the number is reached.Each player’s profile may be saved. " << endl;
			break;
		case 2: {
			//create user profile for game
			string name;
			cout << "Enter a username for you profile:" << endl;
			cin >> name;

			if (!user.overRide(name)) {
				user.insert(name, 0);
			}
			list.playGame(name, points);
			user.insert(name, points);
		}
			  break;
		case 3: {
			//check for previous user 
			string prevUser;
			cout << "Enter the username of the game you would like to load: " << endl;
			cin >> prevUser;

			points = user.check(prevUser);
			if (points == INT_MIN) {
				cout << "Error! No user with that name exists. Please try a different name or start a new game." << endl;
				break;
			}

			//play game
			list.playGame(prevUser, points);
			user.insert(prevUser, points);
		}
			  break;
		case 4: {
			list.insert();
		}
			  break;
		case 5:
			list.remove();
			break;
		case 6:
			user.writeOut();
			list.writeOut();
			break;
		}
	} while (option != 6);
	return 0;
}
