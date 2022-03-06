#pragma once
#include <iostream>
#include <string>
#include "libpq-fe.h"
using namespace std;

//Rees Anderson
//CSS 475
//3.5.2022
//SteamDBDeletes
//This provides functions for deleting entries in the SteamDB

/// <summary>Deletes the user account, friend connections, addresses, and Purchases associated with the passed email.</summary>
/// <param name="conn">- the connection to delete through</param>
/// <param name="userEmail">- the email of the user to delete</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool DeleteUser(PGconn* conn, string userEmail);

/// <summary>Deletes the friendship between the accounts associated with each email. This will delete the friendship in both directions.</summary>
/// <param name="conn">- the connection to delete through</param>
/// <param name="accountEmail">- the email of the account</param>
/// <param name="friendEmail">- the email of the friend's account</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool DeleteFriendship(PGconn* conn, string accountEmail, string friendEmail);

/// <summary>Deletes the purchase record and associated purchase items with the passed purchaseNumber.</summary>
/// <param name="conn">- the connection to delete through</param>
/// <param name="purchaseNumber">- the purchase number of the purchase record to delete</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool DeletePurchase(PGconn* conn, string purchaseNumber);

/// <summary>Deletes the game with the passed title. DANGER! PurchaseItems associated with the game will also be deleted. Purchases only made up of this game will also be deleted.</summary>
/// <param name="conn">- the connection to delete through</param>
/// <param name="title">- the title of the game to delete</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool DeleteGame(PGconn* conn, string title);

/// <summary>Deletes the developer with the passed name. DANGER! This will also delete games made by the developer, as well as purchaseItems involving this dev. Purchases only made up of this dev's games will also be deleted.</summary>
/// <param name="conn">- the connection to delete through</param>
/// <param name="devName">- the name of the developer to delete</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool DeleteDeveloper(PGconn* conn, string devName);

/// <summary>Deletes the publisher with the passed name. DANGER! This will also delete games published by the publisher, as well as purchaseItems involving this publisher. Purchases only made up of this publisher's games will also be deleted.</summary>
/// <param name="conn">- the connection to delete through</param>
/// <param name="devName">- the name of the publisher to delete</param>
/// <returns>True if successful, false if unsuccessful</returns>
bool DeletePublisher(PGconn* conn, string pubName);