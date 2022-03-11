#include "Transactions.h"

//begins a transaction
bool BeginTransaction(PGconn* conn) {
	PGresult* res = NULL;
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
bool PrepareTransaction(PGconn* conn, string transaction) {
	PGresult* res = NULL;
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
bool ExecuteTransaction(PGconn* conn, string transaction) {
	PGresult* res = NULL;
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
bool CommitTransaction(PGconn* conn) {
	//Commit, ending the transaction
	PGresult* res = NULL;
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
bool Rollback(PGconn* conn) {
	//Commit, ending the transaction
	PGresult* res = NULL;
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
	PGresult* res = NULL;
	res = PQexec(conn, command.c_str());
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "DEALLOCATE command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return false;
	}
	PQclear(res);
	return true;
}