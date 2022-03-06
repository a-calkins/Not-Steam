#pragma once
#include <iostream>
#include <string>
#include "libpq-fe.h"
using namespace std;

//Rees Anderson
//CSS 475
//3.5.2022
//SteamDBComms
//This provides functions for creating and closing connections to the SteamDB

/// <summary>Creates a connection to the steam database using the passed user and password.</summary>
/// <param name="user">- the user to connect to the DB with</param>
/// <param name="password">- the password to connect to the DB with</param>
/// <returns>The connection to the database, nullptr if connection failed</returns>
PGconn* ConnectToSteamDB(string user, string password);

/// <summary>Closes the passed connection.</summary>
/// <param name="conn">- the connection to close</param>
void CloseConnectionToSteamDB(PGconn* conn);