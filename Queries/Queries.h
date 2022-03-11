#pragma once
#include <string>
#include <vector>
#include <libpq-fe.h>
//#include "Queries.cpp"
using namespace std;
class Queries
{
public:
	string GetGamesByUser(string email, PGconn* conn);

	string GetGamesSold(PGconn* conn);

	string GetGamesReleasedBetweenDates(string dateA, string dateB, PGconn* conn);

	string GetGamesPriceRange(double priceA, double priceB, PGconn* conn);

	string FriendsOfUser(int id, PGconn* conn);

	string GetGamesByPub(string pub, PGconn* conn);

	string GetGamesByDev(string dev, PGconn* conn);

	string GetUsersByGame(string gmTitle, PGconn* conn);

	string GetGenreCount(string genre, PGconn* conn);

	string GetUsers_WT_SM_Games(string email, PGconn* conn);

	string GetPurchByUser(string email, PGconn* conn);

	string GetPurchByDate(string email, PGconn* conn);
	string GetPurchByState(string state, PGconn* conn);
	string GetPurchByBillAdd(string state, PGconn* conn);

	
private:
	string Print(PGresult* res);
};

