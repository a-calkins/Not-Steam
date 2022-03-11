#pragma once
#include <iostream>
#include <string>
#include <libpq-fe.h>
using namespace std;

//begins a transaction
bool BeginTransaction(PGconn* conn);

//prepare a transaction
bool PrepareTransaction(PGconn* conn, string transaction);

//execute a transaction
bool ExecuteTransaction(PGconn* conn, string transaction);

//commit
bool CommitTransaction(PGconn* conn);

//rollback
bool Rollback(PGconn* conn);

//deallocate all prepares
bool DeallocateAllPrepares(PGconn* conn);