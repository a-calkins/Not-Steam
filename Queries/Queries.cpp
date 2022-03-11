#include "Queries.h"
# include <vector>
#include <string>
#include <iostream>
#include "Transactions.h"

using namespace std;

string Queries::GetGamesByUser(string email, PGconn* conn) //user that own a game
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    //PQclear(res);
    string query = "SELECT Title FROM Game JOIN PurchaseItem ON(Game.ID = GameId)";
    query += " JOIN Purchase ON (Purchase.id = PurchaseID) JOIN Account ON (AccountID = Account.id) ";
    query += "WHERE email =  \'" + email + "\'" +  ";";
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }
    res = PQexec(conn, query.c_str());
    return Print(res);
     
}

string Queries::GetGamesSold(PGconn* conn) //all games available for purchase
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
    string query = "GamesSold AS SELECT Title FROM Game;";
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn,"GamesSold;")) {
        return "";
    }
    res = PQexec(conn, query.c_str());
    return Print(res);
}

string Queries::GetGamesReleasedBetweenDates(string dateA, string dateB, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
    string query = "SELECT Title FROM Game WHERE ReleaseDate > \' " + dateA + "\'";
    query += " AND ReleaseDate < \'" + dateB + "\';";
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }
    res = PQexec(conn, query.c_str());
    return Print(res);
}

string Queries::GetGamesPriceRange(double priceA, double priceB, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
    
    string query = "SELECT Title FROM Game WHERE Price::numeric > " + to_string(priceA);
    query += " AND Price::numeric < " + to_string(priceB) + ";";
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }
    res = PQexec(conn, query.c_str());
    return Print(res);
}

string Queries::FriendsOfUser(int id, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
   
    string query = "SELECT * FROM account JOIN Friendship ON(accountID = "+to_string(id) ;
    query += ") WHERE id = friendID;";
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }
   
    res = PQexec(conn, query.c_str());
    return Print(res);
    
}


string Queries::GetGamesByPub(string pub, PGconn* conn) //games by developer
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    string query = "SELECT * FROM game JOIN publisher ON(name = \'" + pub + "\')";
    query += "WHERE publisherID = publisher.ID;";
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }

    res = PQexec(conn, query.c_str());
    return Print(res);
   
}
string Queries::GetGamesByDev(string dev, PGconn* conn) //Games by developer
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
    string query = "SELECT * FROM account JOIN developer ON(name = \'" + dev + "\')";
    query += "WHERE developerID = developer.ID;";
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }

    res = PQexec(conn, query.c_str());
    return Print(res);
   // PQprint(stdout, res, &printOPT);
   
}
string Queries::GetUsersByGame(string gmTitle, PGconn* conn) //Get user that own a game
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    string query = "GetUsersByGame (text) AS SELECT email, username, First_Name FROM account JOIN purchase ON(account.id = AccountID)";
    query += "JOIN PurchaseItem ON(purchase.ID = purchaseID) JOIN Game ON(Game.id = gameID)";
    query +=    "WHERE Title = $1";

    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, "GetUsersByGame('"+gmTitle+"');")) {
        return "";
    }

    res = PQexec(conn, query.c_str());
    //PQprint(stdout, res, &printOPT);
    return Print(res);
}
string Queries::GetGenreCount(string genre, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    string query = "SELECT name, count(*) FROM GENRE JOIN Game ON(genre.ID = genreid)";
    query += "WHERE name = '"+ genre +"' GROUP BY name;";
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }


    res = PQexec(conn, query.c_str());
    return Print(res);

}//Next query: g

string Queries::GetUsers_WT_SM_Games(string email, PGconn* conn) //get users with same game
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    
    string query = "SELECT email FROM (Select title FROM Game JOIN PurchaseItem ON(Game.ID = GameId) ";
    query += "JOIN Purchase ON(Purchase.id = PurchaseID) JOIN Account ON(AccountID = Account.id) ";
    query += "WHERE email = '" + email + "')AS T1 JOIN(Select title, email FROM Game ";
    query += "JOIN PurchaseItem ON(Game.ID = GameId) JOIN Purchase ON(Purchase.id = PurchaseID) ";
    query += "JOIN Account ON(AccountID = Account.id))AS T2 ON(TRUE) WHERE T1.title = T2.title;";
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }
    res = PQexec(conn, query.c_str());
    return Print(res);
   
    
}


string Queries::GetPurchByUser(string email, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
  
    string query = "SELECT PurchaseNum, PurchaseDate FROM Purchase";
    query += " JOIN Account ON (AccountID = Account.id) ";
    query += "WHERE email =  \'" + email + "\'" + ";";

    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }
    res = PQexec(conn, query.c_str());
    return Print(res);

}


string Queries::GetPurchByDate(string date, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    string query = "SELECT PurchaseNum, PurchaseDate FROM Purchase";
    query += " JOIN Account ON (AccountID = Account.id) ";
    query += "WHERE purchaseDate =  \'" + date + "\'" + ";";
    
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }
    res = PQexec(conn, query.c_str());
    return Print(res);
  

}


string Queries::GetPurchByBillAdd(string state, PGconn* conn) //purchases by billing address
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    string query = "SELECT PurchaseNum, PurchaseDate FROM Purchase JOIN Account ON(AccountID=";
    query += "Account.id) JOIN BillingAddress ON(account.id = BillingAddress.AccountID)";
    query += " WHERE stateid = '" + state + "';";
    if (!PrepareTransaction(conn, query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, query)) {
        return "";
    }

    res = PQexec(conn, query.c_str());
 
   
    return Print(res);
}
string Queries::GetPurchByState(string state, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    string query = "GetPurchByState (text) AS SELECT PurchaseNum, PurchaseDate FROM Purchase JOIN Account ON(AccountID=";
    query += "Account.id) JOIN BillingAddress ON(account.id = BillingAddress.AccountID)";
    query += " WHERE stateid = $1;";
    if (!PrepareTransaction(conn,query)) {
        return "";
    }
    if (!ExecuteTransaction(conn, "GetPurchByState('"+state+"');")) {
        return "";
    }
    res = PQexec(conn, query.c_str());
    
    return Print(res);
}
string Queries::Print(PGresult* res)
{
    string resString = "";   //result string
    
    for (int k = 0; k < PQnfields(res); k++)//get column names
    {
        resString += "|" + string(PQfname(res, k));
      
    }
    resString += "|\n";
    for (int i = 0; i < PQntuples(res); i++) //goes through rows
    {
        for (int j = 0; j < PQnfields(res); j++) //fields in each row
        {
            resString += "|" + string(PQgetvalue(res, i, j));
              
        }
        resString += "|\n";
    
    }
    PQclear(res);
    return resString;
}
//{
    
//}
