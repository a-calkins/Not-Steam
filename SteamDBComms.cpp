#include "SteamDBComms.h"

//Rees Anderson
//CSS 475
//3.5.2022
//SteamDBComms
//This provides functions for creating and closing connections to the SteamDB

PGconn* ConnectToSteamDB(string user, string password) {
    //Set connection info
    string connectionInfo = "dbname = steam user = " + user + " password = " + password;
    const char* conninfo = connectionInfo.c_str();

    //Make the connection to the database
    PGconn* conn = PQconnectdb(conninfo);

    //Return connection
    return conn;
}

void CloseConnectionToSteamDB(PGconn* conn) {
	PQfinish(conn);
}