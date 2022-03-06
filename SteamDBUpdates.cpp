#include "SteamDBUpdates.h"

//Rees Anderson
//CSS 475
//3.5.2022
//SteamDBUpdates
//This provides functions for updating entries in the SteamDB

bool UpdateAccountFirstLastName(PGconn* conn, string userEmail, string newFirstName, string newLastName) {
	//Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement to update Firstname
    res = PQexec(conn, "PREPARE updateAccountFirstName (text, text) AS UPDATE Account SET First_Name = $2 WHERE Email = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the command to execute
    string command = "EXECUTE updateAccountFirstName('" + userEmail + "', '" + newFirstName + "');";
    const char* commandInC = command.c_str();

    //Execute prepared statement to update Firstname
    res = PQexec(conn, commandInC);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement to update Lastname
    res = PQexec(conn, "PREPARE updateAccountLastName (text, text) AS UPDATE Account SET Last_Name = $2 WHERE Email = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the command to execute
    command = "EXECUTE updateAccountLastName('" + userEmail + "', '" + newLastName + "');";
    commandInC = command.c_str();

    //Execute prepared statement to update Lastname
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


bool UpdateAccountEmail(PGconn* conn, string oldUserEmail, string newUserEmail) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement
    res = PQexec(conn, "PREPARE updateAccountEmail (text, text) AS UPDATE Account SET Email = $2 WHERE Email = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE updateAccountEmail('" + oldUserEmail + "', '" + newUserEmail + "');";
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


bool UpdateAccountPassword(PGconn* conn, string userEmail, string newPassword) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement
    res = PQexec(conn, "PREPARE updateAccountPassword (text, text) AS UPDATE Account SET Password = $2 WHERE Email = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE updateAccountPassword('" + userEmail + "', '" + newPassword + "');";
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


bool UpdateAccountUsername(PGconn* conn, string userEmail, string newUsername) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement
    res = PQexec(conn, "PREPARE updateAccountUsername (text, text) AS UPDATE Account SET Username = $2 WHERE Email = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE updateAccountUsername('" + userEmail + "', '" + newUsername + "');";
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


bool UpdateGameGenreID(PGconn* conn, string title, string newGenreID) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement
    res = PQexec(conn, "PREPARE updateGameGenreID (text, text) AS UPDATE Game SET GenreID = $2 WHERE Title = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE updateGameGenreID('" + title + "', '" + newGenreID + "');";
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


bool UpdateGameTitle(PGconn* conn, string oldTitle, string newTitle) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement
    res = PQexec(conn, "PREPARE updateGameTitle (text, text) AS UPDATE Game SET Title = $2 WHERE Title = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE updateGameTitle('" + oldTitle + "', '" + newTitle + "');";
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


bool UpdateGameDescription(PGconn* conn, string title, string newDescription) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement
    res = PQexec(conn, "PREPARE updateGameDescription (text, text) AS UPDATE Game SET Description = $2 WHERE Title = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE updateGameDescription('" + title + "', '" + newDescription + "');";
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


bool UpdateGameReleaseDate(PGconn* conn, string title, string newReleaseDate) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement
    res = PQexec(conn, "PREPARE updateGameReleaseDate (text, text) AS UPDATE Game SET ReleaseDate = $2::date WHERE Title = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE updateGameReleaseDate('" + title + "', '" + newReleaseDate + "');";
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


bool UpdateGamePrice(PGconn* conn, string title, string newPrice) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement
    res = PQexec(conn, "PREPARE updateGamePrice (text, text) AS UPDATE Game SET Price = $2::money WHERE Title = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE updateGamePrice('" + title + "', '" + newPrice + "');";
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


bool UpdateDeveloperName(PGconn* conn, string oldName, string newName) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement
    res = PQexec(conn, "PREPARE updateDeveloperName (text, text) AS UPDATE Developer SET Name = $2 WHERE Name = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE updateDeveloperName('" + oldName + "', '" + newName + "');";
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


bool UpdatePublisherName(PGconn* conn, string oldName, string newName) {
    //Begin transaction
    PGresult* res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Prepare statement
    res = PQexec(conn, "PREPARE updatePublisherName (text, text) AS UPDATE Publisher SET Name = $2 WHERE Name = $1;");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return false;
    }
    PQclear(res);

    //Create the execute string with passed parameters
    string command = "EXECUTE updatePublisherName('" + oldName + "', '" + newName + "');";
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