#include "SteamDBUpdates.h"
#include "Transactions.h"
//Rees Anderson
//CSS 475
//3.5.2022
//SteamDBUpdates
//This provides functions for updating entries in the SteamDB

bool UpdateAccountFirstLastName(PGconn* conn, string userEmail, string newFirstName, string newLastName) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(conn)) {
		return false;
	}
    //Prepare statement to update Firstname
	string updateFirstName = "updateAccountFirstName(text, text) AS UPDATE Account SET First_Name = $2 WHERE Email = $1;";
	if (!PrepareTransaction(conn, updateFirstName)) {
		return false;
	}

    //Create the command to execute
    string command = "updateAccountFirstName('" + userEmail + "', '" + newFirstName + "');";
    //Execute prepared statement to update Firstname
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

    //Prepare statement to update Lastname
	string updateLastName = "updateAccountLastName (text, text) AS UPDATE Account SET Last_Name = $2 WHERE Email = $1;";
	if (!PrepareTransaction(conn, updateLastName)) {
		return false;
	}

    //Create the command to execute
    command = "updateAccountLastName('" + userEmail + "', '" + newLastName + "');";
	//Execute prepared statement to update Lastname
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

    //Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}


bool UpdateAccountEmail(PGconn* conn, string oldUserEmail, string newUserEmail) {
    //Begin transaction
    PGresult* res = NULL;
	if (!BeginTransaction(conn)) {
		return false;
	}
    //Prepare statement
	string updateAccEmail = "updateAccountEmail (text, text) AS UPDATE Account SET Email = $2 WHERE Email = $1;";
	if (!PrepareTransaction(conn, updateAccEmail)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "updateAccountEmail('" + oldUserEmail + "', '" + newUserEmail + "');";
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

    //Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}


bool UpdateAccountPassword(PGconn* conn, string userEmail, string newPassword) {
    //Begin transaction
	PGresult* res = NULL;
	if (!BeginTransaction(conn)) {
		return false;
	}

    //Prepare statement
	string updateAccPassword = "updateAccountPassword (text, text) AS UPDATE Account SET Password = $2 WHERE Email = $1;";
	if (!PrepareTransaction(conn, updateAccPassword)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "updateAccountPassword('" + userEmail + "', '" + newPassword + "');";
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

    //Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}


bool UpdateAccountUsername(PGconn* conn, string userEmail, string newUsername) {
	//Begin transaction
	PGresult* res = NULL;
	if (!BeginTransaction(conn)) {
		return false;
	}

    //Prepare statement
	string updateAccUsername = "updateAccountUsername (text, text) AS UPDATE Account SET Username = $2 WHERE Email = $1;";
	if (!PrepareTransaction(conn, updateAccUsername)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "updateAccountUsername('" + userEmail + "', '" + newUsername + "');";
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}


bool UpdateGameGenreID(PGconn* conn, string title, string newGenreID) {
	//Begin transaction
	PGresult* res = NULL;
	if (!BeginTransaction(conn)) {
		return false;
	}

    //Prepare statement
	string updateGenreID = "updateGameGenreID (text, text) AS UPDATE Game SET GenreID = $2 WHERE Title = $1;";
	if (!PrepareTransaction(conn, updateGenreID)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "updateGameGenreID('" + title + "', '" + newGenreID + "');";
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}


bool UpdateGameTitle(PGconn* conn, string oldTitle, string newTitle) {
	//Begin transaction
	PGresult* res = NULL;
	if (!BeginTransaction(conn)) {
		return false;
	}

    //Prepare statement
	string updateTitle = "updateGameTitle (text, text) AS UPDATE Game SET Title = $2 WHERE Title = $1;";
	if (!PrepareTransaction(conn, updateTitle)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "updateGameTitle('" + oldTitle + "', '" + newTitle + "');";
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}


bool UpdateGameDescription(PGconn* conn, string title, string newDescription) {
	//Begin transaction
	PGresult* res = NULL;
	if (!BeginTransaction(conn)) {
		return false;
	}

    //Prepare statement
	string updateDescription = "updateGameDescription (text, text) AS UPDATE Game SET Description = $2 WHERE Title = $1;";
	if (!PrepareTransaction(conn, updateDescription)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "updateGameDescription('" + title + "', '" + newDescription + "');";
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}


bool UpdateGameReleaseDate(PGconn* conn, string title, string newReleaseDate) {
	//Begin transaction
	PGresult* res = NULL;
	if (!BeginTransaction(conn)) {
		return false;
	}

    //Prepare statement
	string updateReleaseDate = "updateGameReleaseDate (text, text) AS UPDATE Game SET ReleaseDate = $2::date WHERE Title = $1;";
	if (!PrepareTransaction(conn, updateReleaseDate)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "updateGameReleaseDate('" + title + "', '" + newReleaseDate + "');";
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}


bool UpdateGamePrice(PGconn* conn, string title, string newPrice) {
	//Begin transaction
	PGresult* res = NULL;
	if (!BeginTransaction(conn)) {
		return false;
	}

    //Prepare statement
	string updatePrice = "updateGamePrice (text, text) AS UPDATE Game SET Price = $2::money WHERE Title = $1;";
	if (!PrepareTransaction(conn, updatePrice)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "updateGamePrice('" + title + "', '" + newPrice + "');";
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}


bool UpdateDeveloperName(PGconn* conn, string oldName, string newName) {
	//Begin transaction
	PGresult* res = NULL;
	if (!BeginTransaction(conn)) {
		return false;
	}

    //Prepare statement
	string updateDev = "updateDeveloperName (text, text) AS UPDATE Developer SET Name = $2 WHERE Name = $1;";
	if (!PrepareTransaction(conn, updateDev)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "updateDeveloperName('" + oldName + "', '" + newName + "');";
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	return true;
}


bool UpdatePublisherName(PGconn* conn, string oldName, string newName) {
	//Begin transaction
	PGresult* res = NULL;
	if (!BeginTransaction(conn)) {
		return false;
	}

    //Prepare statement
	string updatePub = "updatePublisherName (text, text) AS UPDATE Publisher SET Name = $2 WHERE Name = $1;";
	if (!PrepareTransaction(conn, updatePub)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "updatePublisherName('" + oldName + "', '" + newName + "');";
	if (!ExecuteTransaction(conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(conn)) {
		return false;
	}
	DeallocateAllPrepares(conn);
	return true;
}