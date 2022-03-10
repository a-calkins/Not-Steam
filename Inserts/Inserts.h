#pragma once
#include <string>
#include <vector>
#include <libpq-fe.h>
using namespace std;

//adds a new purchase to the specified account. Timestamp is inserted automatically.
bool InsertNewPurchase(PGconn* conn, string purchaseNum, string accountID, vector<string> games);

//adds a new friend to the two accounts specified by friendID and accountID (emails)
bool AddFriend(PGconn* conn, string friendID, string accountID);

//creates a new account
bool CreateAccount(PGconn* conn, string firstName, string lastName, 
	string email, string password, string username, string billingAddress[]);

//add a billing address for a new account
bool InsertNewBillingAddress(PGconn* conn, string accEmail, string street, string city, string stateID, string zip);

//adds a new game
bool InsertNewGame(PGconn* conn, string genre, string title, string description, 
	string developer, string publisher, string releaseDate, string price);

//adds a new publisher
bool InsertNewPublisher(PGconn* conn, string name);

//adds a new dev
bool InsertNewDeveloper(PGconn* conn, string name);

//adds a new genre
bool InsertNewGenre(PGconn* conn, string id, string name);
