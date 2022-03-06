#pragma once
#include <iostream>
#include <string>
#include "libpq-fe.h"
using namespace std;

//Rees Anderson
//CSS 475
//3.5.2022
//SteamDBUpdates
//This provides functions for updating entries in the SteamDB

/// <summary>Updates the first and last name of the account with the passed email.</summary>
/// <param name="conn">- the connection to update through</param>
/// <param name="userEmail">- the email of the user to update</param>
/// <param name="newFirstName">- the new first name of the user (limited to 30 characters)</param>
/// <param name="newLastName">- the new last name of the user (limited to 30 characters)</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdateAccountFirstLastName(PGconn* conn, string userEmail, string newFirstName, string newLastName);

/// <summary>Updates the email of the account with the passed oldUserEmail.</summary>
/// <param name="conn">- the connection to update through</param>
/// <param name="oldUserEmail">- the current email of the user</param>
/// <param name="newUserEmail">- the new email of the user (limited to 100 characters)</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdateAccountEmail(PGconn* conn, string oldUserEmail, string newUserEmail);

/// <summary>Updates the password of the account with the passed email.</summary>
/// <param name="conn">- the connection to update through</param>
/// <param name="userEmail">- the email of the user to update</param>
/// <param name="newPassword">- the new password of the user (limited to 30 characters)</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdateAccountPassword(PGconn* conn, string userEmail, string newPassword);

/// <summary>Updates the username of the account with the passed email.</summary>
/// <param name="conn">- the connection to update through</param>
/// <param name="userEmail">- the email of the user to update</param>
/// <param name="newUsername">- the new username of the user (limited to 30 characters)</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdateAccountUsername(PGconn* conn, string userEmail, string newUsername);

/// <summary>Updates the GenreID of the Game with the passed title.</summary>
/// <param name="conn">- the connection to update through</param>
/// <param name="title">- the title of the game to update</param>
/// <param name="newGenreID">- the new GenreID of the Game (limited to 2 characters)</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdateGameGenreID(PGconn* conn, string title, string newGenreID);

/// <summary>Updates the Title of the Game with the passed oldTitle.</summary>
/// <param name="conn">- the connection to update through</param>
/// <param name="oldTitle">- the current title of the game to update</param>
/// <param name="newTitle">- the new title of the Game (limited to 100 characters)</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdateGameTitle(PGconn* conn, string oldTitle, string newTitle);

/// <summary>Updates the description of the Game with the passed title.</summary>
/// <param name="conn">- the connection to update through</param>
/// <param name="title">- the title of the game to update</param>
/// <param name="newDescription">- the new description of the Game (limited to 500 characters)</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdateGameDescription(PGconn* conn, string title, string newDescription);

/// <summary>Updates the release date of the Game with the passed title.</summary>
/// <param name="conn">- the connection to update through</param>
/// <param name="title">- the title of the game to update</param>
/// <param name="newReleaseDate">- the new release date of the Game (in the format "yyyy-mm-dd")</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdateGameReleaseDate(PGconn* conn, string title, string newReleaseDate);

/// <summary>Updates the price of the Game with the passed title.</summary>
/// <param name="conn">- the connection to update through</param>
/// <param name="title">- the title of the game to update</param>
/// <param name="newPrice">- the new price of the Game (in the format "$XX.XX")</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdateGamePrice(PGconn* conn, string title, string newPrice);

/// <summary>Updates the name of developer identified by the parameter oldName, and changes it to newName.</summary>
/// <param name="conn">- the connection to delete through</param>
/// <param name="oldName">- the name of the developer to update</param>
/// <param name="newName">- the new name of the developer (limited to 30 characters)</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdateDeveloperName(PGconn* conn, string oldName, string newName);

/// <summary>Updates the name of publisher identified by the parameter oldName, and changes it to newName.</summary>
/// <param name="conn">- the connection to delete through</param>
/// <param name="oldName">- the name of the publisher to update</param>
/// <param name="newName">- the new name of the publisher (limited to 30 characters)</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool UpdatePublisherName(PGconn* conn, string oldName, string newName);