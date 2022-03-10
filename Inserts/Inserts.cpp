#include "Inserts.h"
#include "Transactions.h"
using namespace std;

//adds a new purchase to the specified account. Timestamp is inserted automatically.
bool InsertNewPurchase(PGconn* conn, string purchaseNum, string accountEmail, vector<string> games) {
	string gameIDs[sizeof(games)];
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}
	string command = "SELECT ID FROM Account WHERE email = '" + accountEmail + "'" + ";";
	cout << command << endl;
	res = PQexec(conn, command.c_str());
	if (PQgetisnull(res, 0, 0) == 1) {
		return false;
	}
	string accID(PQgetvalue(res, 0, 0));
	PQclear(res);

	command = "INSERT INTO Purchase (PurchaseNum, AccountID, PurchaseDate) VALUES ('" 
		+ purchaseNum + "', '" + accID + "', current_date);";
	cout << command << endl;

	//execute instruction
	res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "INSERT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}

	PQclear(res);

	//now insert into purchase item
	command = "SELECT ID FROM Purchase WHERE PurchaseNum = '" + purchaseNum + "'" + ";";
	res = PQexec(conn, command.c_str());
	if (PQgetisnull(res, 0, 0) == 1) {
		return false;
	}
	string purchaseID(PQgetvalue(res, 0, 0));
	PQclear(res);

	string insert = "INSERT INTO PurchaseItem (purchaseID, gameID) VALUES ";
	size_t length = games.size();
	for (size_t i = 0; i < length; i++) {
		command = "SELECT ID FROM Game WHERE title = '" + games[i] + "'" + ";";
		res = PQexec(conn, command.c_str());
		if (PQgetisnull(res, 0, 0) == 1) {
			return false;
		}
		string gameID(PQgetvalue(res, 0, 0));
		cout << gameID << endl;
		gameIDs[i] = gameID;
		PQclear(res);

		insert += "(" + purchaseID + ", " + gameIDs[i] + ")";
		if (i != (length - 1))
			insert += ", ";
		else {
			insert += ";";
		}
	}
	
	res = PQexec(conn, insert.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "INSERT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}

//adds a new friend to the two accounts specified by friendID and accountID (emails)
bool AddFriend(PGconn* conn, string friendEmail, string accountEmail) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}
	//get account id
	string command = "SELECT ID FROM Account WHERE email = '" + accountEmail + "'" + ";";
	res = PQexec(conn, command.c_str());
	if (PQgetisnull(res, 0, 0) == 1) {
		return false;
	}
	string accID(PQgetvalue(res, 0, 0));
	PQclear(res);

	//get friend id
	command = "SELECT ID FROM Account WHERE email = '" + friendEmail + "'" + ";";
	res = PQexec(conn, command.c_str());
	if (PQgetisnull(res, 0, 0) == 1) {
		return false;
	}
	string friendID(PQgetvalue(res, 0, 0));
	PQclear(res);

	//now create the friendship
	command = "INSERT INTO Friendship (FriendID, AccountID) VALUES ("
		+ friendID + ", " + accID + "), (" + accID + ", " + friendID + ");";
	res = PQexec(conn, command.c_str());

	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "INSERT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}

//creates a new account
bool CreateAccount(PGconn* conn, string firstName, string lastName,
	string email, string password, string username, string billingAddress[]) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

	string command = "INSERT INTO Account(First_Name, Last_Name, Email, Password, Username) VALUES ('"
		+ firstName + "', '" + lastName + "', '" + email + "', '" + password + "', '" + username + "');";
	res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "INSERT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);

	if (!InsertNewBillingAddress(conn, email, billingAddress[0], billingAddress[1], billingAddress[2], billingAddress[3])) {
		return false;
	}
	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}

//add a billing address for a new account, only called when a new account is added
bool InsertNewBillingAddress(PGconn* conn, string accEmail, string street, string city, string stateID, string zip) {
	PGresult* res = NULL;
	//get account id
	string command = "SELECT ID FROM Account WHERE email = '" + accEmail + "'" + ";";
	res = PQexec(conn, command.c_str());
	if (PQgetisnull(res, 0, 0) == 1) {
		return false;
	}
	string accID(PQgetvalue(res, 0, 0));
	PQclear(res);

	command = "INSERT INTO BillingAddress (AccountID, StreetAddress, City, StateID, ZipCode) VALUES ("
		+ accID + ", '" + street + "', '" + city + "', '"+ stateID + "', '" + zip + "');";
	res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "INSERT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	return true;
}

//adds a new game
bool InsertNewGame(PGconn* conn, string genre, string title, string description,
	string developer, string publisher, string releaseDate, string price) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

	//first, get developer and publisher. If they don't exist, add them to the DB.
	string command = "SELECT ID FROM Developer WHERE name = '" + developer + "';";
	res = PQexec(conn, command.c_str());
	if (PQgetisnull(res, 0, 0) == 1) {
		if (!InsertNewDeveloper(conn, developer))
			return false;
	}
	string devID(PQgetvalue(res, 0, 0));
	PQclear(res);

	command = "SELECT ID FROM Publisher WHERE name = '" + publisher + "';";
	res = PQexec(conn, command.c_str());
	if (PQgetisnull(res, 0, 0) == 1) {
		if (!InsertNewDeveloper(conn, publisher))
			return false;
	}
	string pubID(PQgetvalue(res, 0, 0));
	PQclear(res);

	command = "INSERT INTO Game (GenreID, Title, Description, DeveloperID, PublisherID, ReleaseDate, Price) ";
	command += "VALUES ('" + genre + "', '" + title + "', '" + description + "', " + devID + ", " + pubID
		+ ", '" + releaseDate + "', '$" + price + "');";
	res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "INSERT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}

//adds a new publisher
bool InsertNewPublisher(PGconn* conn, string name) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

	string command = "INSERT INTO Publisher(Name) VALUES ('" + name + "');";
	res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "INSERT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}

//adds a new dev
bool InsertNewDeveloper(PGconn* conn, string name) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

	string command = "INSERT INTO Developer(Name) VALUES ('" + name + "');";
	res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "INSERT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}

//adds a new genre
bool InsertNewGenre(PGconn* conn, string id, string name) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

	string command = "INSERT INTO Genre(ID, Name) VALUES ('" + id + "', '" + name + "');";
	res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "INSERT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}