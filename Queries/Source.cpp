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
	cout << query->GetGamesSold(conn);
	//cout<<query->GetUsersByGame("Bayonetta", conn);
	//cout << query->GetGamesByUser("zeroshift@hasevo.com",conn);
	/*query->GetGamesReleasedBetweenDates("2019-12-25", "2019-12-30",conn);
	query->GetGamesPriceRange(20.00,30.00, conn);
	query->FriendsOfUser(1, conn);
	query->GetGamesByPub("Rockstar Games", conn);
	
	query->GetGenreCount("Action", conn);
	query->GetUsers_WT_SM_Games("xavHow@live.com",conn);
	query->GetPurchByUser("xavHow@live.com", conn);
query->GetPurchByDate("2021-09-24", conn);*/
	//cout << query->GetPurchByState("WA", conn);
	PQfinish(conn);
	fflush(stdout);
	
	
	//delete conninfo;
	//delete conn;
	
}