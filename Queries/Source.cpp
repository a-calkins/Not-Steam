#include <libpq-fe.h>
#include <string>
#include "Queries.h"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
	const char* conninfo;
	PGconn* conn;
	conninfo = "dbname = steam user = postgres password = orangejuice";
	conn = PQconnectdb(conninfo);
	//if (PQstatus(conn) != CONNECTION_OK)
	//{
	//	fprintf(stderr, "Connection to database failed: %s",
		//	PQerrorMessage(conn));
		//PQfinish(conn);
	//}
	Queries* query = new Queries();
	cout << query->GetGamesByUser("zeroshift@hasevo.com",conn) + "\n";
	cout << query->GetGamesSold(conn) + "\n";
	
	cout<<query->GetUsersByGame("Bayonetta", conn);
	
	cout<< query->GetGamesReleasedBetweenDates("2019-12-25", "2019-12-30",conn);
	cout<<query->GetGamesPriceRange(20.00,30.00, conn);
	cout << query->FriendsOfUser(1, conn);
	cout << query->GetGamesByPub("Rockstar Games", conn);
    cout << query->GetGenreCount("Action", conn);
	cout << query->GetUsers_WT_SM_Games("xavHow@live.com",conn);
	cout << query->GetPurchByUser("xavHow@live.com", conn);
	cout << query->GetPurchByDate("2021-09-24", conn);
	cout << query->GetPurchByState("WA",conn);
	cout << query->GetPurchByBillAdd("1111 Wilshire Blvd", "Los Angeles", "CA", "90017", conn);
	PQfinish(conn);
	//fflush(stdout);
	
	
	//delete conninfo;
	//delete conn;
	
}