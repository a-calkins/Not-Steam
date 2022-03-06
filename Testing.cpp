#include "SteamDBComms.h"
#include "SteamDBUpdates.h"
#include "SteamDBDeletes.h"
using namespace std;

//Rees Anderson
//CSS 475
//3.5.2022
//Testing
//This tests all SteamDBComms, SteamDBUpdates, and SteamDBDeletes functions

int main(int argc, char** argv)
{
    //Create connection
    PGconn* conn = ConnectToSteamDB("postgres", "---ADD YOUR PASSWORD---");

    //Updates Testing
    UpdateAccountFirstLastName(conn, "zeroshift@hasevo.com", "Boward", "Woward");
    UpdateAccountPassword(conn, "zeroshift@hasevo.com", "12345");
    UpdateAccountUsername(conn, "zeroshift@hasevo.com", "GherkinGuy");
    UpdateAccountEmail(conn, "zeroshift@hasevo.com", "ZERO@gmail.com");
    UpdateGameGenreID(conn, "Devil May Cry HD Collection", "AD");
    UpdateGameDescription(conn, "Devil May Cry HD Collection", "Featuring Dante from the Devil May Cry Series!");
    UpdateGameReleaseDate(conn, "Devil May Cry HD Collection", "2022-03-05");
    UpdateGamePrice(conn, "Devil May Cry HD Collection", "$99.99");
    UpdateGameTitle(conn, "Devil May Cry HD Collection", "Devil May Cry Ultimate Collection");
    UpdateDeveloperName(conn, "SEGA", "SEGA, Co.");
    UpdatePublisherName(conn, "OMOCAT, LLC", "OMOCAT");

    //Deletes Testing
    DeletePurchase(conn, "101353");
    DeleteGame(conn, "Sonic Adventure 2");
    DeleteFriendship(conn, "admroseliribeiro@beanchatuky.com", "caracarn@nonise.com");
    DeleteUser(conn, "xavHow@live.com");
    DeleteDeveloper(conn, "Playground Games");
    DeletePublisher(conn, "Rockstar Games");
    DeletePublisher(conn, "Xbox Game Studios");

    //Close connection
    CloseConnectionToSteamDB(conn);
    return 0;
}