#include "Inserts.h"
#include "Transactions.h"
using namespace std;

//adds a new purchase to the specified account. Timestamp is inserted automatically.
bool InsertNewPurchase(PGconn* conn, string purchaseNum, string accountEmail, vector<string> games) {
	string gameIDs[sizeof(games)];
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(conn)) {
		return false;
	}

	string command = "getAccID (text) AS SELECT ID FROM Account WHERE email = $1";
	string exec = "getAccID('" + accountEmail + "');";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	res = ExecuteTransQuery(conn, exec);
	if (res == NULL) {
		cout << "User does not exist." << endl;
		DeallocateAllPrepares(conn);
		return false;
	}
	string accID(PQgetvalue(res, 0, 0));
	PQclear(res);

	command = "addPurch (text, int) AS INSERT INTO Purchase (PurchaseNum, AccountID, PurchaseDate) VALUES ($1, $2, current_date);";
	exec = "addPurch('" + purchaseNum + "', '" + accID + "');";
	//execute instruction
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	if (!ExecuteTransaction(conn, exec)) {
		DeallocateAllPrepares(conn);
		return false;
	}

	//now insert into purchase item
	command = "SELECT ID FROM Purchase WHERE PurchaseNum = '" + purchaseNum + "'" + ";";
	res = PQexec(conn, command.c_str());
	if (PQgetisnull(res, 0, 0) == 1) {
		cout << "Purchase was not found." << endl;
		PQclear(res);
		DeallocateAllPrepares(conn);
		return false;
	}
	string purchaseID(PQgetvalue(res, 0, 0));
	PQclear(res);

	string insert = "INSERT INTO PurchaseItem (purchaseID, gameID) VALUES ";

	command = "getGame (text) AS SELECT ID FROM Game WHERE title = $1;";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}

	size_t length = games.size();
	for (size_t i = 0; i < length; i++) {
		exec = "getGame('" + games[i] + "');";
		res = ExecuteTransQuery(conn, exec);
		if (res == NULL) {
			cout << "Game does not exist." << endl;
			DeallocateAllPrepares(conn);
			return false;
		}
		string gameID(PQgetvalue(res, 0, 0));
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
		DeallocateAllPrepares(conn);
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}

//adds a new friend to the two accounts specified by friendID and accountID (emails)
bool AddFriend(PGconn* conn, string friendEmail, string accountEmail) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(conn)) {
		return false;
	}
	//get account id
	string command = "getAccID (text) AS SELECT ID FROM Account WHERE email = $1;";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	string exec = "getAccID('" + accountEmail + "');";
	res = ExecuteTransQuery(conn, exec);
	if (res == NULL) {
		cout << "Account not found." << endl;
		DeallocateAllPrepares(conn);
		return false;
	}
	string accID(PQgetvalue(res, 0, 0));
	PQclear(res);

	//get friend id
	exec = "getAccID('" + friendEmail + "');";
	res = ExecuteTransQuery(conn, exec);
	if (res == NULL) {
		cout << "Account not found." << endl;
		DeallocateAllPrepares(conn);
		return false;
	}
	string friendID(PQgetvalue(res, 0, 0));
	PQclear(res);

	//now create the friendship
	command = "addFriend (text, text) AS INSERT INTO Friendship (FriendID, AccountID) VALUES ($1, $2), ($2, $1);";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	exec = "addFriend("+ friendID + ", " + accID + ");";
	if (!ExecuteTransaction(conn, exec)) {
		DeallocateAllPrepares(conn);
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}

//creates a new account
bool CreateAccount(PGconn* conn, string firstName, string lastName,
	string email, string password, string username, string billingAddress[]) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(conn)) {
		return false;
	}

	string command = "addAccount (text, text, text, text, text) AS INSERT INTO Account(First_Name, Last_Name, Email, Password, Username) VALUES ($1, $2, $3, $4, $5);";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	string exec = "addAccount('" + firstName + "', '" + lastName + "', '" + email + "', '" + password + "', '" + username + "');";
	if (!ExecuteTransaction(conn, exec)) {
		DeallocateAllPrepares(conn);
		return false;
	}

	if (!InsertNewBillingAddress(conn, email, billingAddress[0], billingAddress[1], billingAddress[2], billingAddress[3])) {
		return false;
	}
	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}

//add a billing address for a new account, only called when a new account is added
bool InsertNewBillingAddress(PGconn* conn, string accEmail, string street, string city, string stateID, string zip) {
	PGresult* res = NULL;
	//get account id
	string command = "getAccID (text) AS SELECT ID FROM Account WHERE email = $1;";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	string exec = "getAccID('" + accEmail + "');";
	res = ExecuteTransQuery(conn, exec);
	if (res == NULL) {
		cout << "Account not found." << endl;
		DeallocateAllPrepares(conn);
		return false;
	}
	string accID(PQgetvalue(res, 0, 0));
	PQclear(res);

	command = "addAddress (int, text, text, text, text) AS INSERT INTO BillingAddress (AccountID, StreetAddress, City, StateID, ZipCode) VALUES ($1, $2, $3, $4, $5);";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	exec = "addAddress("+ accID + ", '" + street + "', '" + city + "', '"+ stateID + "', '" + zip + "');";
	if (!ExecuteTransaction(conn, exec)) {
		DeallocateAllPrepares(conn);
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}

//adds a new game
bool InsertNewGame(PGconn* conn, string genre, string title, string description,
	string developer, string publisher, string releaseDate, string price) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(conn)) {
		return false;
	}

	//first, get developer and publisher. If they don't exist, add them to the DB.
	string command = "getDevID (text) AS SELECT ID FROM Developer WHERE name = $1;";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	string exec = "getDevID('" + developer + "');";
	res = ExecuteTransQuery(conn, exec);
	if (res == NULL) {
		cout << "Developer not found." << endl;
		DeallocateAllPrepares(conn);
		return false;
	}
	string devID(PQgetvalue(res, 0, 0));
	PQclear(res);

	command = "getPubID (text) AS SELECT ID FROM Publisher WHERE name = $1;";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	exec = "getPubID('" + publisher + "');";
	res = ExecuteTransQuery(conn, exec);
	if (res == NULL) {
		cout << "Publisher not found." << endl;
		DeallocateAllPrepares(conn);
		return false;
	}
	string pubID(PQgetvalue(res, 0, 0));
	PQclear(res);

	command = "addGame (text, text, text, int, int, text, text) AS INSERT INTO Game (GenreID, Title, Description, DeveloperID, PublisherID, ReleaseDate, Price) ";
	command += "VALUES ($1, $2, $3, $4, $5, $6, $7);";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	exec = "addGame('" + genre + "', '" + title + "', '" + description + "', " + devID + ", " + pubID
		+ ", '" + releaseDate + "'::date, '$" + price + "');";
	if (!ExecuteTransaction(conn, exec)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}

//adds a new publisher
bool InsertNewPublisher(PGconn* conn, string name) {
	//Begin transaction
	//if BEGIN fails, return false
	if (!BeginTransaction(conn)) {
		return false;
	}

	string command = "insertPub (text) AS INSERT INTO Publisher(Name) VALUES ($1);";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	string exec = "insertPub('" + name + "');";
	if (!ExecuteTransaction(conn, exec)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}

//adds a new dev
bool InsertNewDeveloper(PGconn* conn, string name) {
	//Begin transaction
	//if BEGIN fails, return false
	if (!BeginTransaction(conn)) {
		return false;
	}
	string command = "insertDev (text) AS INSERT INTO Developer(Name) VALUES ($1);";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	string exec = "insertDev('" + name + "');";
	if (!ExecuteTransaction(conn, exec)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}

//adds a new genre
bool InsertNewGenre(PGconn* conn, string id, string name) {
	//Begin transaction
	//if BEGIN fails, return false
	if (!BeginTransaction(conn)) {
		return false;
	}

	string command = "insertGenre (text, text) AS INSERT INTO Genre(ID, Name) VALUES ($1, $2);";
	if (!PrepareTransaction(conn, command)) {
		return false;
	}
	string exec = "insertGenre('" + id + "', '" + name + "');";
	if (!ExecuteTransaction(conn, exec)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		DeallocateAllPrepares(conn);
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}