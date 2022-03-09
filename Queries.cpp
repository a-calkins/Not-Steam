#include "Queries.h"
# include <vector>
#include <string>
#include <iostream>
using namespace std;

void Queries::GetGamesByUser(string email, PGconn* conn) //user that own a game
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
    string query = "SELECT Title FROM Game JOIN PurchaseItem ON(Game.ID = GameId)";
    query += " JOIN Purchase ON (Purchase.id = PurchaseID) JOIN Account ON (AccountID = Account.id) ";
    query += "WHERE email =  \'" + email + "\'" +  ";";
     res = PQexec(conn, query.c_str());
     PQprint(stdout, res, &printOPT);
     
     //cout << *PQresultErrorMessage(res);
     PQclear(res);
     
}

void Queries::GetGamesSold(PGconn* conn) //all games available for purchase
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = 't\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0'; 
    
    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT Title FROM Game;";
    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);
}

void Queries::GetGamesReleasedBetweenDates(string dateA, string dateB, PGconn* conn)
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = 't\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT Title FROM Game WHERE ReleaseDate > \' " + dateA + "\'";
    query += " AND ReleaseDate < \'" + dateB + "\';";
    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);
}

void Queries::GetGamesPriceRange(double priceA, double priceB, PGconn* conn)
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = 't\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT Title FROM Game WHERE Price::numeric > " + to_string(priceA);
    query += " AND Price::numeric < " + to_string(priceB) + ";";
    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);
}

void Queries::FriendsOfUser(int id, PGconn* conn)
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = '|\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';
    
    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT * FROM account JOIN Friendship ON(accountID = "+to_string(id) ;
    query += ") WHERE id = friendID;";

   
    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);
    
}


void Queries::GetGamesByPub(string pub, PGconn* conn) //games by developer
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = '|\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT * FROM game JOIN publisher ON(name = \'" + pub + "\')";
    query += "WHERE publisherID = publisher.ID;";


    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);
   
}
void Queries::GetGamesByDev(string dev, PGconn* conn) //Games by developer
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = '|\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT * FROM account JOIN developer ON(name = \'" + dev + "\')";
    query += "WHERE developerID = developer.ID;";


    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);
   
}
void Queries::GetUsersByGame(string gmTitle, PGconn* conn) //Get user that own a game
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = '|\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT email, username, First_Name FROM account JOIN purchase ON(account.id = AccountID)";
    query += "JOIN PurchaseItem ON(purchase.ID = purchaseID) JOIN Game ON(Game.id = gameID)";
    query +=    "WHERE Title = 'Bayonetta'";


    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);
    
}
void Queries::GetGenreCount(string genre, PGconn* conn)
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = '|\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT name, count(*) FROM GENRE JOIN Game ON(genre.ID = genreid)";
    query += "WHERE name = '"+ genre +"' GROUP BY name;";
       


    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);

}//Next query: g

void Queries::GetUsers_WT_SM_Games(string email, PGconn* conn) //get users with same game
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = '|\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT email FROM (Select title FROM Game JOIN PurchaseItem ON(Game.ID = GameId) ";
    query += "JOIN Purchase ON(Purchase.id = PurchaseID) JOIN Account ON(AccountID = Account.id) ";
    query += "WHERE email = '" + email + "')AS T1 JOIN(Select title, email FROM Game ";
    query += "JOIN PurchaseItem ON(Game.ID = GameId) JOIN Purchase ON(Purchase.id = PurchaseID) ";
    query += "JOIN Account ON(AccountID = Account.id))AS T2 ON(TRUE) WHERE T1.title = T2.title;";

    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);
    
}


void Queries::GetPurchByUser(string email, PGconn* conn)
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = '|\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT PurchaseNum, PurchaseDate FROM Purchase";
        query += " JOIN Account ON (AccountID = Account.id) ";
    query += "WHERE email =  \'" + email + "\'" + ";";

    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);

}


void Queries::GetPurchByDate(string date, PGconn* conn)
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = '|\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT PurchaseNum, PurchaseDate FROM Purchase";
    query += " JOIN Account ON (AccountID = Account.id) ";
    query += "WHERE purchaseDate =  \'" + date + "\'" + ";";

    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);

}
void Queries::GetPurchByState(string state, PGconn* conn)
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = '|\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT PurchaseNum, PurchaseDate FROM Purchase JOIN Account ON(AccountID=";
    query += "Account.id) JOIN BillingAddress ON(account.id = BillingAddress.AccountID)";
    query += " WHERE stateid = '" + state + "';";

    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);
}

void Queries::GetPurchByBillAdd(string state, PGconn* conn) //purchases by billing address
{
    PQprintOpt printOPT = { 0 };
    printOPT.header = '1';
    printOPT.align = '1';
    printOPT.fieldSep = new char;
    *printOPT.fieldSep = '|\0';
    printOPT.tableOpt = new char;
    *printOPT.tableOpt = 't\0';
    printOPT.caption = new char;
    *printOPT.caption = 't\0';

    PGresult* res = PQexec(conn, "BEGIN");
    string query = "SELECT PurchaseNum, PurchaseDate FROM Purchase JOIN Account ON(AccountID=";
    query += "Account.id) JOIN BillingAddress ON(account.id = BillingAddress.AccountID)";
    query += " WHERE stateid = '" + state + "';";

    res = PQexec(conn, query.c_str());
    PQprint(stdout, res, &printOPT);
    PQclear(res);
}
//{
    
//}
