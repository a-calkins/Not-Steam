#include "SteamDBDeletes.h"
#include "Transactions.h"

//Rees Anderson
//CSS 475
//3.5.2022
//SteamDBDeletes
//This provides functions for deleting entries in the SteamDB

bool DeleteUser(PGconn* conn, string userEmail) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

    //Part 1 - Deleting Friendships
    //Prepare statement
	string deleteFriendships = "deleteFriendshipsInvolvingEmail (text) AS DELETE FROM Friendship WHERE accountID = (SELECT id FROM Account WHERE Email = $1) OR friendID = (SELECT id FROM Account WHERE Email = $1);";
	if (!PrepareTransaction(res, conn, deleteFriendships)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "deleteFriendshipsInvolvingEmail('" + userEmail + "');";
	//Execute prepared statement to update Lastname
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 2 - Deleting BillingAddresses
    //Prepare statement
	string deleteAddresses = "deleteAddressesInvolvingEmail (text) AS DELETE FROM BillingAddress WHERE accountID = (SELECT id FROM Account WHERE Email = $1);";
	if (!PrepareTransaction(res, conn, deleteAddresses)) {
		return false;
	}

    //Create the execute string with passed parameters
    command = "deleteAddressesInvolvingEmail('" + userEmail + "');";
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 3 - Deleting Purchase Items
    //Prepare statement
	string deletePurchases = "deletePurchaseItemsInvolvingEmail (text) AS DELETE FROM PurchaseItem WHERE purchaseID IN (SELECT id FROM Purchase WHERE accountID = (SELECT id FROM Account WHERE Email = $1));";
	if (!PrepareTransaction(res, conn, deletePurchases)) {
		return false;
	}

    //Create the execute string with passed parameters
    command = "deletePurchaseItemsInvolvingEmail('" + userEmail + "');";

    //Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 4 - Deleting Purchases
    //Prepare statement
	deletePurchases = "deletePurchasesInvolvingEmail (text) AS DELETE FROM Purchase WHERE accountID = (SELECT id FROM Account WHERE Email = $1);";
	if (!PrepareTransaction(res, conn, deletePurchases)) {
		return false;
	}

    //Create the execute string with passed parameters
    command = "deletePurchasesInvolvingEmail('" + userEmail + "');";

	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 5 - Deleting Account
    //Prepare statement
	string deleteAccount = "deleteAccountInvolvingEmail (text) AS DELETE FROM Account WHERE Email = $1;";
	if (!PrepareTransaction(res, conn, deleteAccount)) {
		return false;
	}

    //Create the execute string with passed parameters
    command = "deleteAccountInvolvingEmail('" + userEmail + "');";

	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}


bool DeleteFriendship(PGconn* conn, string accountEmail, string friendEmail) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

    //Part 1 - Deleting Friendship from account to friend
    //Prepare statement
	string deleteFriend = "deleteFriendship (text, text) AS DELETE FROM Friendship WHERE accountID = (SELECT id FROM Account WHERE Email = $1) AND friendID = (SELECT id FROM Account WHERE Email = $2);";
	if (!PrepareTransaction(res, conn, deleteFriend)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "deleteFriendship('" + accountEmail + "', '" + friendEmail + "');";

    //Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 2 - Deleting Friendship from friend to account (we can reuse previously defined prepare)
    //Create the execute string with passed parameters
    command = "deleteFriendship('" + friendEmail + "', '" + accountEmail + "');";

	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}


bool DeletePurchase(PGconn* conn, string purchaseNumber) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

    //Part 1 - Deleting PurchaseItems
    //Prepare statement
	string deletePurchaseItem = "deletePurchaseItems (text) AS DELETE FROM PurchaseItem WHERE PurchaseID = (SELECT id FROM Purchase WHERE PurchaseNum = $1);";
	if (!PrepareTransaction(res, conn, deletePurchaseItem)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "deletePurchaseItems('" + purchaseNumber + "');";
    //Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 2 - Deleting Purchase
    //Prepare statement
	string deletePurchase = "deletePurchase (text) AS DELETE FROM Purchase WHERE PurchaseNum = $1;";
	if (!PrepareTransaction(res, conn, deletePurchase)) {
		return false;
	}

    //Create the execute string with passed parameters
    command = "deletePurchase('" + purchaseNumber + "');";
	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}


bool DeleteGame(PGconn* conn, string title) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

    //Part 1 - Deleting PurchaseItems
    //Prepare statement
	string deletePurchaseItemsByGame = "deletePurchaseItemsByGame (text) AS DELETE FROM PurchaseItem WHERE GameID = (SELECT id FROM Game WHERE title = $1);";
	if (!PrepareTransaction(res, conn, deletePurchaseItemsByGame)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "deletePurchaseItemsByGame('" + title + "');";
	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 2 - Deleting Purchases where its only purchaseItem has just been deleted
    res = PQexec(conn, "DELETE FROM Purchase WHERE id IN (SELECT Purchase.id FROM Purchase LEFT JOIN (SELECT PurchaseID, COUNT(*) FROM PurchaseItem GROUP BY PurchaseID ORDER BY PurchaseID) AS T1 ON (Purchase.id = T1.PurchaseID) WHERE T1.count IS NULL);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Deleting Empty Purchases command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 3 - Deleting the Game
    //Prepare statement
	string deleteGame = "deleteGame (text) AS DELETE FROM Game WHERE title = $1;";
	if (!PrepareTransaction(res, conn, deleteGame)) {
		return false;
	}

    //Create the execute string with passed parameters
    command = "deleteGame('" + title + "');";
	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}


bool DeleteDeveloper(PGconn* conn, string devName) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

    //Part 1 - Delete PurchaseItems involving developer
    //Prepare statement
	string deletePurchaseItemsByDev = "deletePurchaseItemsByDev (text) AS DELETE FROM PurchaseItem WHERE GameID IN (SELECT id FROM Game WHERE DeveloperID = (SELECT id FROM Developer WHERE Name = $1));";
	if (!PrepareTransaction(res, conn, deletePurchaseItemsByDev)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "deletePurchaseItemsByDev('" + devName + "');";
	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 2 - Delete Purchases without any purchaseItems (because they were just deleted)
    res = PQexec(conn, "DELETE FROM Purchase WHERE id IN (SELECT Purchase.id FROM Purchase LEFT JOIN (SELECT PurchaseID, COUNT(*) FROM PurchaseItem GROUP BY PurchaseID ORDER BY PurchaseID) AS T1 ON (Purchase.id = T1.PurchaseID) WHERE T1.count IS NULL);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Deleting Empty Purchases command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 3 - Delete Games involving developer
	string deleteGamesByDev = "deleteGamesByDev (text) AS DELETE FROM Game WHERE DeveloperID = (SELECT id FROM Developer WHERE Name = $1);";
	if (!PrepareTransaction(res, conn, deleteGamesByDev)) {
		return false;
	}

    //Create the execute string with passed parameters
    command = "deleteGamesByDev('" + devName + "');";
	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 4 - Delete Developer
    //Prepare statement
	string deleteDev = "deleteDeveloper (text) AS DELETE FROM Developer WHERE Name = $1;";
	if (!PrepareTransaction(res, conn, deleteDev)) {
		return false;
	}

    //Create the execute string with passed parameters
    command = "deleteDeveloper('" + devName + "');";
	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}


bool DeletePublisher(PGconn* conn, string pubName) {
	//Begin transaction
	PGresult* res = NULL;
	//if BEGIN fails, return false
	if (!BeginTransaction(res, conn)) {
		return false;
	}

    //Part 1 - Delete PurchaseItems involving publisher
    //Prepare statement
	string deletePurchaseByPub = "deletePurchaseItemsByPublisher (text) AS DELETE FROM PurchaseItem WHERE GameID IN (SELECT id FROM Game WHERE PublisherID = (SELECT id FROM Publisher WHERE Name = $1));";
	if (!PrepareTransaction(res, conn, deletePurchaseByPub)) {
		return false;
	}

    //Create the execute string with passed parameters
    string command = "deletePurchaseItemsByPublisher('" + pubName + "');";
	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 2 - Delete Purchases without any purchaseItems (because they were just deleted)
    res = PQexec(conn, "DELETE FROM Purchase WHERE id IN (SELECT Purchase.id FROM Purchase LEFT JOIN (SELECT PurchaseID, COUNT(*) FROM PurchaseItem GROUP BY PurchaseID ORDER BY PurchaseID) AS T1 ON (Purchase.id = T1.PurchaseID) WHERE T1.count IS NULL);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Deleting Empty Purchases command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 3 - Delete Games involving publisher
	string deleteGamesByPub = "deleteGamesByPublisher (text) AS DELETE FROM Game WHERE PublisherID = (SELECT id FROM Publisher WHERE Name = $1);";
	if (!PrepareTransaction(res, conn, deleteGamesByPub)) {
		return false;
	}

    //Create the execute string with passed parameters
    command = "deleteGamesByPublisher('" + pubName + "');";
	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

    //Part 4 - Delete Publisher
    //Prepare statement
	string deletePub = "deletePublisher (text) AS DELETE FROM Publisher WHERE Name = $1;";
	if (!PrepareTransaction(res, conn, deletePub)) {
		return false;
	}

    //Create the execute string with passed parameters
    command = "deletePublisher('" + pubName + "');";
	//Execute prepared statement
	if (!ExecuteTransaction(res, conn, command)) {
		return false;
	}

	//Commit, ending the transaction
	if (!CommitTransaction(res, conn)) {
		return false;
	}
	return true;
}