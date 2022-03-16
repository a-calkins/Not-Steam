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
    string query = "GetGamesByUser (text) AS SELECT Title FROM Game JOIN PurchaseItem ON(Game.ID = GameId)";
    query += " JOIN Purchase ON (Purchase.id = PurchaseID) JOIN Account ON (AccountID = Account.id) ";
    query += "WHERE email = $1;";
    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetGamesByUser('"+email+"');");
    if (res == NULL) return"Error";

    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
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
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GamesSold;");
    if (res == NULL) return"Error";

    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
}

string Queries::GetGamesReleasedBetweenDates(string dateA, string dateB, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
    string query = "GetGamesReleasedBetweenDates (date) AS SELECT Title FROM Game WHERE ReleaseDate > $1";
    query += " AND ReleaseDate < $2;";

    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetGamesReleasedBetweenDates('" + dateA + "','"+dateB+"');");
    if (res == NULL) return"Error";


    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
}

string Queries::GetGamesPriceRange(double priceA, double priceB, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
    
    string query = "GetGamesByPriceRange (numeric) AS SELECT Title FROM Game WHERE Price::numeric > $1";
    query += " AND Price::numeric < $2;";

    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetGamesByPriceRange('" + to_string(priceA) + "','" + to_string(priceB) + "');");
    if (res == NULL) return"Error";


    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
}

string Queries::FriendsOfUser(int id, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
   
    string query = "FriendsOfUser (numeric) AS SELECT * FROM account JOIN Friendship ON(accountID = $1" ;
    query += ") WHERE id = friendID;";

    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "FriendsOfUser('" + to_string(id) + "');");
    if (res == NULL) return"Error";


    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
}


string Queries::GetGamesByPub(string pub, PGconn* conn) //games by developer
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    string query = "GetGamesByPub (text) AS SELECT  title ,description, releasedate, price FROM game JOIN publisher ON(name = $1)";
    query += "WHERE publisherID = publisher.ID;";

    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetGamesByPub('" + pub+ "');");
    if (res == NULL) return"Error";


    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
}
string Queries::GetGamesByDev(string dev, PGconn* conn) //Games by developer
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
    string query = "GetGamesByDev (text) AS SELECT title, game.id FROM Game JOIN developer ON(developerID = developer.ID)";
    query += " WHERE developer.name = $1;";

    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetGamesByDev('" + dev + "');");
    if (res == NULL) return"Error";


    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
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
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetUsersByGame('" + gmTitle + "');");
    if (res == NULL) return"Error";


    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
}
string Queries::GetGenreCount(string genre, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    string query = "GetGenreCount (text) AS SELECT name, count(*) FROM GENRE JOIN Game ON(genre.ID = genreid)";
    query += "WHERE name = $1 GROUP BY name;";
    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetGenreCount('" + genre + "');"); 
    if (res == NULL) return"Error";
    

    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);

}

string Queries::GetUsers_WT_SM_Games(string email, PGconn* conn) //get users with same game
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    
    string query = "GetUsers_WT_SM_Games (text) AS SELECT DISTINCT email FROM (Select title FROM Game JOIN PurchaseItem ON(Game.ID = GameId) ";
    query += "JOIN Purchase ON(Purchase.id = PurchaseID) JOIN Account ON(AccountID = Account.id) ";
    query += "WHERE email = $1)AS T1 JOIN(Select title, email FROM Game ";
    query += "JOIN PurchaseItem ON(Game.ID = GameId) JOIN Purchase ON(Purchase.id = PurchaseID) ";
    query += "JOIN Account ON(AccountID = Account.id))AS T2 ON(TRUE) WHERE T1.title = T2.title;";
    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetUsers_WT_SM_Games('" + email + "');");
    if (res == NULL) return"Error";

    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
    
}


string Queries::GetPurchByUser(string email, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }
  
    string query = "GetPurchByUser (text) AS SELECT PurchaseNum, PurchaseDate FROM Purchase";
    query += " JOIN Account ON (AccountID = Account.id) ";
    query += "WHERE email =  $1;";
    
    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetPurchByUser('" + email +"');");
    if (res == NULL) return"Error";

    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
}


string Queries::GetPurchByDate(string date, PGconn* conn)
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    string query = "GetPurchByDate (date) AS SELECT PurchaseNum, PurchaseDate FROM Purchase";
    query += " JOIN Account ON (AccountID = Account.id) ";
    query += "WHERE purchaseDate =  $1;";
    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetPurchByDate('" + date + "');");
    if (res == NULL) return"Error";

    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
  

}


string Queries::GetPurchByBillAdd(string street, string city, string state, string zipcode, PGconn* conn) //purchases by billing address
{
    PGresult* res = NULL;
    if (!BeginTransaction(conn)) {
        return "";
    }

    string query = "GetPurchByBillAdd (text) AS SELECT PurchaseNum, PurchaseDate FROM Purchase JOIN Account ON(AccountID=";
    query += "Account.id) JOIN BillingAddress ON(account.id = BillingAddress.AccountID)";
    query += " WHERE stateid = $1 AND city = $2 AND zipcode = $3;";
    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetPurchByBillAdd('" + state + "','" + city + "','" + zipcode + "');");
    if (res == NULL) return"Error";

    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
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
    if (!PrepareTransaction(conn, query)) {
        return "Error";
    }
    res = ExecuteTransQuery(conn, "GetPurchByState('" + state + "');");
    if (res == NULL) return"Error";

    if (!CommitTransaction(conn))return"Error";

	DeallocateAllPrepares(conn);
    return Print(res);
}
string Queries::Print(PGresult* res)
{
    string resString = "";   //result string
    vector<int> maxLengths;
    vector<int> lineIndexes;
     ////////////////////////////////////////////FORMAT FIELDS
    int totalLength = 0;
    resString += "\n";
    for (int i = 0; i < PQnfields(res); i++) //goes through all 
    {
        int maxSize = 0;
        for (int j = 0; j < PQntuples(res); j++) //rows in each field
        {
            if(string(PQgetvalue(res, j, i)).length() > maxSize) 
				maxSize = (int)string(PQgetvalue(res, j, i)).length();                                                                //resString += "|" + string(PQgetvalue(res, i, j));
              
        }
        int size = maxSize-2;
        for (int k = 1; k < size  / 2; k++)
        {
            resString += " ";
        }
        resString += " " + string(PQfname(res,i)) + " ";
        for (int k =1; k < size / 2; k++)
        {
            resString += " ";
        }
        if (i < PQnfields(res) - 1) { 
			resString += "|"; 
			lineIndexes.push_back((int)resString.length() - 2); 
		}
        maxLengths.push_back(maxSize + (int)string(PQfname(res, i)).length());
        totalLength += maxSize+(int)string(PQfname(res, i)).length();
    }
       
    resString += "\n";
    for (int x = 0; x < totalLength+1; x++)
    {
        resString += "-";
    }
    resString += "\n";
    ////////////////////////////////////////////FORMAT VALUES
    string lineAttributes;
    for (int i = 0; i < PQntuples(res); i++) //goes through rows
    {
        
        lineAttributes = " ";
        for (int j = 0; j < PQnfields(res); j++) //fields in each row
        {
            string value = string(PQgetvalue(res, i, j));
                                                   
            lineAttributes +=  " " + string(PQgetvalue(res, i, j))  + " ";
            for (int y = 2; y < maxLengths[j] - value.length()-1; y++) { lineAttributes += " "; }
            //resString += "|" + string(PQgetvalue(res, i, j));
        }
        int k = 0;
        while(k < lineIndexes.size()){  lineAttributes[lineIndexes[k]] = '|';k++;}
        resString += lineAttributes + "\n";
    }
    PQclear(res);
    return resString;
}

