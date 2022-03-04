#include <libpq-fe.h>
#include <string>
#include "Queries.h"

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
	query->GetGamesByUser("zeroshift@hasevo.com",conn);
	
	PQfinish(conn);
	fflush(stdout);
	
	
	//delete conninfo;
	//delete conn;
	
}