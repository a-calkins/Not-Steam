#include "Queries.h"
# include <vector>
#include <string>
#include <iostream>
using namespace std;

void Queries::GetGamesByUser(string email, PGconn* conn)
{
    PQprintOpt printOPT = {0};
    printOPT.header = '1';
    printOPT.align = '1';
   printOPT.fieldSep = new char;
    *printOPT.fieldSep = 't\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0'; /*
    char* test = new char;
    *test = 't\0';
    char** testTwo = &test;
    printOPT.fieldName = testTwo;*/
    PGresult* res = PQexec(conn, "BEGIN");
    //PQclear(res);
    string query = "SELECT Title FROM Game;"  ; // JOIN PurchaseItem ON(Game.ID = GameId)";
   // query += " JOIN Purchase ON (Purchase.id = PurchaseID) JOIN Account ON (AccountID = Account.id) ";
   // query += "WHERE email = " + email;
     res = PQexec(conn, query.c_str());
     PQprint(stdout, res, &printOPT);
     
     //cout << *PQresultErrorMessage(res);
     PQclear(res);
     //PQfinish(conn);
     ;
     //delete res;
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
