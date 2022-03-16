#include <libpq-fe.h>
#include <string>
#include "Queries.h"
#include "Inserts.h"
#include "SteamDBDeletes.h"
#include "SteamDBUpdates.h"
#include "SteamDBComms.h"
#include "Transactions.h"
#include <iostream>

void getInput(string, string);
string stringToLower(string);
bool isValidMode(string);
bool isValidOperation(string, string);
bool executeInsertion(string, string);
bool executeUpdate(string, string);
bool executeDelete(string, string);
bool executeQuery(string, string);
string checkMode(string);
using namespace std;

//globals
PGconn* conn = NULL;
Queries* query = new Queries();

int main()
{
	
	conn = ConnectToSteamDB("postgres", "loulou");
	if (PQstatus(conn) != CONNECTION_OK)
	{
		fprintf(stderr, "Connection to database failed: %s",
			PQerrorMessage(conn));
		PQfinish(conn);
	}
	getInput("What will you do?: ", "Not a valid input.");
	return 0;
}

void getInput(string msg, string error) {
	string response;
	cout << msg;
	while (getline(cin, response)) {
		if (response == "") {
			cout << error << endl;
			cout << msg;
			continue;
		}
		if (response == "exit" || response == "q") {
			break;
		}
		string mode = response.substr(0, response.find(" "));
		mode = stringToLower(mode);
		if (!isValidMode(mode)) {
			cout << error << endl;
			cout << msg;
			continue;
		}
		cout << checkMode(mode);
		getline(cin, response);
		if (!isValidOperation(mode, response)) {
			cout << error << endl;
			cout << msg;
			continue;
		}
		else {
			cout << "Success!" << endl;
			cout << msg;
		}
	}
	
}

string stringToLower(string s) {
	string newStr = "";
	for (int i = 0; i < s.length(); i++) {
		char c = s.at(i);
		newStr += tolower(c);
	}
	return newStr;
}

bool isValidMode(string s) {
	if (s == "insert" || s == "delete" || s == "update" || s == "query") {
		return true;
	}
	return false;
}

bool isValidOperation(string mode, string s) {
	//check the function
	string function = s.substr(0, s.find(" "));
	if (function == "") {
		return false;
	}
	function = stringToLower(function);
	//parameters
	//if no params, error
	if (s.find(" ") == -1 && function != "getgamessold") {
		return false;
	}
	s.erase(0, s.find(" ") + 1);
	if (mode == "insert") {
		if (!executeInsertion(s, function)) {
			return false;
		}
	}
	if (mode == "update") {
		if (!executeUpdate(s, function)) {
			return false;
		}
	}
	if (mode == "delete") {
		if (!executeDelete(s, function)) {
			return false;
		}
	}
	if (mode == "query") {
		if (!executeQuery(s, function)) {
			return false;
		}
	}
}

string checkMode(string s) {
	if (s == "insert") {
		return "Insert what? ";
	}
	else if (s == "update") {
		return "Update what? ";
	}
	else if (s == "delete") {
		return "Delete what? ";
	}
	else {
		return "Query what? ";
	}
}

bool executeInsertion(string params, string function) {
	vector<string> games;
	if (function == "newpurchase") {
		//get purchase num and email
		string purchaseNum = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string email = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		//get the games
		string s = "";
		for (int i = 0; i < params.length(); i++) {
			if ((params.at(i) == '|' || params.at(i) == ';') && s.length() > 0) {
				games.push_back(s);
				s = "";
				continue;
			}
			s += params.at(i);
		}
		return InsertNewPurchase(conn, purchaseNum, email, games);
	}
	else if (function == "newfriend") {
		string friendEmail = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string accEmail = params.substr(0, params.find(" "));

		return AddFriend(conn, friendEmail, accEmail);
	}
	else if (function == "newaccount") {
		//get first name
		string firstName = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		//get lastname
		string lastName = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		//get email
		string email = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		//get password
		string password = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		//get username
		string username = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string address[4];
		//get the address
		string s = "";
		int j = 0;
		for (int i = 0; i < params.length(); i++) {
			if ((i == (params.length() - 1) && j < 3) || j >= 4) {
				return false;
			}
			if (params.at(i) == ',' && s.length() > 0) {
				address[j] = s;
				s = "";
				j++;
				continue;
			}
			s += params.at(i);
		}
		return CreateAccount(conn, firstName, lastName, email, password, username, address);
	}
	else if (function == "newgame") {
		//get genre
		string genre = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if(params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		//get title
		string title = params.substr(0, params.find("|")- 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		//get desc
		string desc = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false; 
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		//get dev
		string dev = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		//get pub
		string pub = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		//get releaseDate
		string releaseDate = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		//get price
		string price = params.substr(0, params.find(" "));

		return InsertNewGame(conn, genre, title, desc, dev, pub, releaseDate, price);
	}
	else if (function == "newpublisher") {
		string name = params.substr(0, params.find(";"));
		return InsertNewPublisher(conn, name);
	}
	else if (function == "newdeveloper") {
		string name = params.substr(0, params.find(";"));
		return InsertNewDeveloper(conn, name);
	}
	else if (function == "newgenre") {
		//get id
		string id = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		//get name
		string name = params.substr(0, params.find(";"));
		
		return InsertNewGenre(conn, id, name);
	}
	else {
		return false;
	}
}

bool executeUpdate(string params, string function) {
	if (function == "accfirstlastname") {
		string email = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string newFirst = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string newLast = params.substr(0, params.find(" "));

		return UpdateAccountFirstLastName(conn, email, newFirst, newLast);
	}
	else if (function == "accemail") {
		string oldEmail = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string newEmail = params.substr(0, params.find(" "));

		return UpdateAccountEmail(conn, oldEmail, newEmail);
	}
	else if (function == "accpassword") {
		string email = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string newPass = params.substr(0, params.find(" "));

		return UpdateAccountPassword(conn, email, newPass);
	}
	else if (function == "username") {
		string email = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string newName = params.substr(0, params.find(" "));
		return UpdateAccountUsername(conn, email, newName);
	}
	else if (function == "gamegenre") {
		string title = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		string genre = params.substr(0, params.find(" "));
		return UpdateGameGenreID(conn, title, genre);
	}
	else if (function == "gametitle") {
		string title = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		string newTitle = params.substr(0, params.find(";"));
		return UpdateGameTitle(conn, title, newTitle);
	}
	else if (function == "gamedesc") {
		string title = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		string newDesc = params;
		return UpdateGameDescription(conn, title, newDesc);
	}
	else if (function == "gamereleasedate") {
		string title = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		string date = params.substr(0, params.find(" "));
		return UpdateGameReleaseDate(conn, title, date);
	}
	else if (function == "gameprice") {
		string title = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		string price = params.substr(0, params.find(" "));
		return UpdateGamePrice(conn, title, price);
	}
	else if (function == "devname") {
		string oldName = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		string newName = params.substr(0, params.find(";"));
		return UpdateDeveloperName(conn, oldName, newName);
	}
	else if (function == "pubname") {
		string oldName = params.substr(0, params.find("|") - 1);
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);
		if (params.find(" ") == 0)
			params.erase(0, params.find(" ") + 1);

		string newName = params.substr(0, params.find(";"));
		return UpdatePublisherName(conn, oldName, newName);
	}
	else {
		return false;
	}
}
bool executeDelete(string params, string function) {
	if (function == "user") {
		string email = params.substr(0, params.find(" "));
		return DeleteUser(conn, email);
	}
	else if (function == "friend") {
		string accEmail = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string friendEmail = params.substr(0, params.find(" "));
		return DeleteFriendship(conn, accEmail, friendEmail);
	}
	else if (function == "purchase") {
		string purchNum = params.substr(0, params.find(" "));
		return DeletePurchase(conn, purchNum);
	}
	else if (function == "game") {
		string game = params.substr(0, params.find(";"));
		if (params.find(";") == -1) {
			return false;
		}
		return DeleteGame(conn, game);
	}
	else if (function == "dev") {
		string name = params.substr(0, params.find(";"));
		if (params.find(";") == -1) {
			return false;
		}
		return DeleteDeveloper(conn, name);
	}
	else if (function == "pub") {
		string name = params.substr(0, params.find(";"));
		if (params.find(";") == -1) {
			return false;
		}
		return DeletePublisher(conn, name);
	}
	else {
		return false;
	}
}
bool executeQuery(string params, string function) {
	if (function == "getgamesbyuser") {
		string email = params.substr(0, params.find(" "));
		cout << query->GetGamesByUser(email, conn);
		return true;
	}
	else if (function == "getgamessold") {
		cout << query->GetGamesSold(conn);
		return true;
	}
	else if (function == "getgamesreleasedbetweendates") {
		string dateA = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string dateB = params.substr(0, params.find(" "));

		cout << query->GetGamesReleasedBetweenDates(dateA, dateB, conn);
		return true;
	}
	else if (function == "getgamespricerange") {
		string priceA = params.substr(0, params.find(" "));
		if (params.find(" ") == -1) {
			return false;
		}
		params.erase(0, params.find(" ") + 1);

		string priceB = params.substr(0, params.find(" "));

		cout << query->GetGamesPriceRange(stod(priceA), stod(priceB), conn);
		return true;
	}
	else if (function == "getfriendsofuser") {
		string email = params.substr(0, params.find(" "));
		string command = "getAccID (text) AS SELECT ID FROM Account WHERE email = $1;";
		if (!PrepareTransaction(conn, command)) {
			return false;
		}
		PGresult* r = ExecuteTransQuery(conn, "getaccID('" + email + "');");
		if (PQgetisnull(r, 0, 0) == 1) {
			PQclear(r);
			cout << "User not found." << endl;
			return false;
		}
		string userID(PQgetvalue(r, 0, 0));
		PQclear(r);

		cout << query->FriendsOfUser(stoi(userID), conn);
		return true;
	}
	else if (function == "getgamesbypub") {
		string pub = params.substr(0, params.find(";"));
		cout << query->GetGamesByPub(pub, conn);
		return true;
	}
	else if (function == "getgamesbydev") {
		string dev = params.substr(0, params.find(";"));
		cout << query->GetGamesByDev(dev, conn);
		return true;
	}
	else if (function == "getusersbygame") {
		string title = params.substr(0, params.find(";"));
		cout << query->GetUsersByGame(title, conn);
		return true;
	}
	else if (function == "getgenrecount") {
		string genre = params.substr(0, params.find(";"));
		cout << query->GetGenreCount(genre, conn);
		return true;
	}
	else if (function == "getuserswtsmgames") {
		string email = params.substr(0, params.find(" "));
		cout << query->GetUsers_WT_SM_Games(email, conn);
		return true;
	}
	else if (function == "getpurchbyuser") {
		string email = params.substr(0, params.find(" "));
		cout << query->GetPurchByUser(email, conn);
		return true;
	}
	else if (function == "getpurchbydate") {
		string date = params.substr(0, params.find(" "));
		cout << query->GetPurchByDate(date, conn);
		return true;
	}
	else if (function == "getpurchbystate") {
		string state = params.substr(0, params.find(" "));
		cout << query->GetPurchByState(state, conn);
		return true;
	}
	else if (function == "getpurchbybilladd") {
		string street = params.substr(0, params.find("|"));
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);

		string city = params.substr(0, params.find("|"));
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);

		string state = params.substr(0, params.find("|"));
		if (params.find("|") == -1) {
			return false;
		}
		params.erase(0, params.find("|") + 1);

		string zip = params.substr(0, params.find(" "));

		cout << query->GetPurchByBillAdd(street, city, state, zip, conn);
		return true;
	}
	else {
		return false;
	}
}