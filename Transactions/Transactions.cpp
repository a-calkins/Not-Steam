#include "Transactions.h"

//begins a transaction
bool BeginTransaction(PGresult* res, PGconn* conn) {
	res = PQexec(conn, "BEGIN");
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	return true;
}

//prepare a transaction
bool PrepareTransaction(PGresult* res, PGconn* conn, string transaction) {
	string command = "PREPARE " + transaction;
	res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "PREPARE command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	return true;
}

//execute a transaction
bool ExecuteTransaction(PGresult* res, PGconn* conn, string transaction) {
	string command = "EXECUTE " + transaction;
	//Execute prepared statement
	res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "EXECUTE command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	return true;
}

//commit
bool CommitTransaction(PGresult* res, PGconn* conn) {
	//Commit, ending the transaction
	res = PQexec(conn, "COMMIT");
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "COMMIT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	return true;
}

//rollback
bool Rollback(PGresult* res, PGconn* conn) {
	//Commit, ending the transaction
	res = PQexec(conn, "ROLLBACK");
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "ROLLBACK command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	return true;
}

//deallocate all prepares
bool DeallocateAllPrepares(PGconn* conn) {
	string command = "DEALLOCATE ALL";
	//Execute prepared statement
	PGresult* res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "DEALLOCATE command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	return true;
}
