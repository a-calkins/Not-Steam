#include "SteamDBDeletes.h"

//Rees Anderson
//CSS 475
//3.5.2022
//SteamDBDeletes
//This provides functions for deleting entries in the SteamDB

bool DeleteUser(PGconn* conn, string userEmail) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 1 - Deleting Friendships
    //Prepare statement
    res = PQexec(conn, "PREPARE deleteFriendshipsInvolvingEmail (text) AS DELETE FROM Friendship WHERE accountID = (SELECT id FROM Account WHERE Email = $1) OR friendID = (SELECT id FROM Account WHERE Email = $1);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE deleteFriendshipsInvolvingEmail('" + userEmail + "');";
    const char* commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 2 - Deleting BillingAddresses
    //Prepare statement
    res = PQexec(conn, "PREPARE deleteAddressesInvolvingEmail (text) AS DELETE FROM BillingAddress WHERE accountID = (SELECT id FROM Account WHERE Email = $1);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    command = "EXECUTE deleteAddressesInvolvingEmail('" + userEmail + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 3 - Deleting Purchase Items
    //Prepare statement
    res = PQexec(conn, "PREPARE deletePurchaseItemsInvolvingEmail (text) AS DELETE FROM PurchaseItem WHERE purchaseID IN (SELECT id FROM Purchase WHERE accountID = (SELECT id FROM Account WHERE Email = $1));");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    command = "EXECUTE deletePurchaseItemsInvolvingEmail('" + userEmail + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 4 - Deleting Purchases
    //Prepare statement
    res = PQexec(conn, "PREPARE deletePurchasesInvolvingEmail (text) AS DELETE FROM Purchase WHERE accountID = (SELECT id FROM Account WHERE Email = $1);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    command = "EXECUTE deletePurchasesInvolvingEmail('" + userEmail + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 5 - Deleting Account
    //Prepare statement
    res = PQexec(conn, "PREPARE deleteAccountInvolvingEmail (text) AS DELETE FROM Account WHERE Email = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    command = "EXECUTE deleteAccountInvolvingEmail('" + userEmail + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Commit, ending the transaction
    res = PQexec(conn, "COMMIT");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "COMMIT command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);
    return true;
}


bool DeleteFriendship(PGconn* conn, string accountEmail, string friendEmail) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 1 - Deleting Friendship from account to friend
    //Prepare statement
    res = PQexec(conn, "PREPARE deleteFriendship (text, text) AS DELETE FROM Friendship WHERE accountID = (SELECT id FROM Account WHERE Email = $1) AND friendID = (SELECT id FROM Account WHERE Email = $2);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE deleteFriendship('" + accountEmail + "', '" + friendEmail + "');";
    const char* commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 2 - Deleting Friendship from friend to account (we can reuse previously defined prepare)
    //Create the execute string with passed parameters
    command = "EXECUTE deleteFriendship('" + friendEmail + "', '" + accountEmail + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Commit, ending the transaction
    res = PQexec(conn, "COMMIT");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "COMMIT command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);
    return true;
}


bool DeletePurchase(PGconn* conn, string purchaseNumber) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 1 - Deleting PurchaseItems
    //Prepare statement
    res = PQexec(conn, "PREPARE deletePurchaseItems (text) AS DELETE FROM PurchaseItem WHERE PurchaseID = (SELECT id FROM Purchase WHERE PurchaseNum = $1);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE deletePurchaseItems('" + purchaseNumber + "');";
    const char* commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 2 - Deleting Purchase
    //Prepare statement
    res = PQexec(conn, "PREPARE deletePurchase (text) AS DELETE FROM Purchase WHERE PurchaseNum = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    command = "EXECUTE deletePurchase('" + purchaseNumber + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Commit, ending the transaction
    res = PQexec(conn, "COMMIT");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "COMMIT command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);
    return true;
}


bool DeleteGame(PGconn* conn, string title) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 1 - Deleting PurchaseItems
    //Prepare statement
    res = PQexec(conn, "PREPARE deletePurchaseItemsByGame (text) AS DELETE FROM PurchaseItem WHERE GameID = (SELECT id FROM Game WHERE title = $1);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE deletePurchaseItemsByGame('" + title + "');";
    const char* commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

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
    res = PQexec(conn, "PREPARE deleteGame (text) AS DELETE FROM Game WHERE title = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    command = "EXECUTE deleteGame('" + title + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Commit, ending the transaction
    res = PQexec(conn, "COMMIT");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "COMMIT command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);
    return true;
}


bool DeleteDeveloper(PGconn* conn, string devName) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 1 - Delete PurchaseItems involving developer
    //Prepare statement
    res = PQexec(conn, "PREPARE deletePurchaseItemsByDev (text) AS DELETE FROM PurchaseItem WHERE GameID IN (SELECT id FROM Game WHERE DeveloperID = (SELECT id FROM Developer WHERE Name = $1));");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE deletePurchaseItemsByDev('" + devName + "');";
    const char* commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

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
    res = PQexec(conn, "PREPARE deleteGamesByDev (text) AS DELETE FROM Game WHERE DeveloperID = (SELECT id FROM Developer WHERE Name = $1);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    command = "EXECUTE deleteGamesByDev('" + devName + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 4 - Delete Developer
    //Prepare statement
    res = PQexec(conn, "PREPARE deleteDeveloper (text) AS DELETE FROM Developer WHERE Name = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    command = "EXECUTE deleteDeveloper('" + devName + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Commit, ending the transaction
    res = PQexec(conn, "COMMIT");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "COMMIT command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);
    return true;
}


bool DeletePublisher(PGconn* conn, string pubName) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 1 - Delete PurchaseItems involving publisher
    //Prepare statement
    res = PQexec(conn, "PREPARE deletePurchaseItemsByPublisher (text) AS DELETE FROM PurchaseItem WHERE GameID IN (SELECT id FROM Game WHERE PublisherID = (SELECT id FROM Publisher WHERE Name = $1));");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE deletePurchaseItemsByPublisher('" + pubName + "');";
    const char* commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

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
    res = PQexec(conn, "PREPARE deleteGamesByPublisher (text) AS DELETE FROM Game WHERE PublisherID = (SELECT id FROM Publisher WHERE Name = $1);");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    command = "EXECUTE deleteGamesByPublisher('" + pubName + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Part 4 - Delete Publisher
    //Prepare statement
    res = PQexec(conn, "PREPARE deletePublisher (text) AS DELETE FROM Publisher WHERE Name = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    command = "EXECUTE deletePublisher('" + pubName + "');";
    commandInC = command.c_str();

    //Execute prepared statement
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Commit, ending the transaction
    res = PQexec(conn, "COMMIT");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "COMMIT command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);
    return true;
}