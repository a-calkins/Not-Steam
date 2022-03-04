#pragma once
#include <string>
#include <vector>
#include <libpq-fe.h>
//#include "Queries.cpp"
using namespace std;
class Queries
{
public:
	void GetGamesByUser(string email, PGconn* conn);

	vector<string> GetGamesSold(PGconn* conn);

	vector<string> GetGamesReleasedBetweenDates(string dateA, string dateB, PGconn* conn);

	vector<string> GetGamesPriceRange(double priceA, double priceB, PGconn* conn);

	vector<string> GetGamesByPubDev(string pub_dev, PGconn* conn);



};

