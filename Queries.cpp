#include "Queries.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//prints the queries
void Queries::ProcessQuery(PGconn* conn, const char* query) {
	PGresult* res;
	PQprintOpt opt = { 0 };

	res = PQexec(conn, query);
	if (res == NULL) {
		cout << PQerrorMessage(conn) << endl;
		return;
	}
	opt.header = 1; //gets column headers
	opt.align = 1;
	char fieldSep = ' ';
	opt.fieldSep = &fieldSep;

	//PQprint(stdout, res, &opt);
	cout << PQgetvalue(res, 0, 0) << endl;
	PQclear(res);
}
void Queries::GetGamesByUser(string email, PGconn* conn)
{
	/*char fieldSep = ' ';
	char tableOpt = 't\0';
	char caption = 't\0';
    PQprintOpt printOPT = {0};
    printOPT.header = '1';
    printOPT.align = '1';
   printOPT.fieldSep = &fieldSep;
    //*printOPT.fieldSep = 't\0';
    //printOPT.tableOpt = &tableOpt;
    //*printOPT.tableOpt = 't\0';
    //printOPT.caption = &caption;
    //*printOPT.caption = 't\0'; 
	/*
    char* test = new char;
    *test = 't\0';
    char** testTwo = &test;
    printOPT.fieldName = testTwo;*/
    /*PGresult* res;
    //PQclear(res);
    string query = "SELECT Title FROM Game;"  ; // JOIN PurchaseItem ON(Game.ID = GameId)";
   // query += " JOIN Purchase ON (Purchase.id = PurchaseID) JOIN Account ON (AccountID = Account.id) ";
   // query += "WHERE email = " + email;
     res = PQexec(conn, query.c_str());
     PQprint(stdout, res, &printOPT);
     
     //cout << *PQresultErrorMessage(res);
     PQclear(res);
     //PQfinish(conn);
     
     //delete res;*/
	string query = "SELECT Title FROM Game";
	ProcessQuery(conn, query.c_str());


}

vector<string> Queries::GetGamesSold(PGconn* conn)
{
    return vector<string>();
}

vector<string> Queries::GetGamesReleasedBetweenDates(string dateA, string dateB, PGconn* conn)
{
    return vector<string>();
}

vector<string> Queries::GetGamesPriceRange(double priceA, double priceB, PGconn* conn)
{
    return vector<string>();
}

vector<string> Queries::GetGamesByPubDev(string pub_dev, PGconn* conn)
{
    return vector<string>();
}

//vector<string> Queries::GetGamesSold()
//{
    
//}
