#pragma once
#include <iostream>
#include <string>
#include <libpq-fe.h>
using namespace std;

//begins a transaction
bool BeginTransaction(PGresult* res, PGconn* conn);

//prepare a transaction
bool PrepareTransaction(PGresult* res, PGconn* conn, string transaction);

//execute a transaction
bool ExecuteTransaction(PGresult* res, PGconn* conn, string transaction);

//commit
bool CommitTransaction(PGresult* res, PGconn* conn);

//rollback
bool Rollback(PGresult* res, PGconn* conn);

//deallocate all prepares
bool DeallocateAllPrepares(PGconn* conn);
