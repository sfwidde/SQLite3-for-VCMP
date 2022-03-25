#include "squirrel/SQFuncs.h"
#include "sqlite3/sqlite3.h"
#include <stddef.h>
#ifdef _SQ64
#include <limits.h>
#endif

extern HSQAPI sq;

_SQUIRRELDEF(SQLite_Connect)
{
	if (sq->gettop(v) == 2 &&
		sq->gettype(v, 2) == OT_STRING)
	{
		const SQChar* filePath;
		sq->getstring(v, 2, &filePath);

		sqlite3* db;
		if (sqlite3_open(filePath, &db) == SQLITE_OK)
		{
			sq->pushuserpointer(v, db);
			return 1;
		}
		else
		{
			SQInteger retVal = sq->throwerror(v, sqlite3_errmsg(db));
			sqlite3_close(db);
			return retVal;
		}
	}

	sq->pushnull(v);
	return 1;
}

_SQUIRRELDEF(SQLite_Disconnect)
{
	if (sq->gettop(v) == 2 &&
		sq->gettype(v, 2) == OT_USERPOINTER)
	{
		SQUserPointer data;
		sq->getuserpointer(v, 2, &data);

		sqlite3* db = (sqlite3*)data;
		if (sqlite3_close(db) != SQLITE_OK)
			return sq->throwerror(v, sqlite3_errmsg(db));
	}

	return 0;
}

_SQUIRRELDEF(SQLite_Query)
{
	if (sq->gettop(v) == 3 &&
		sq->gettype(v, 2) == OT_USERPOINTER &&
		sq->gettype(v, 3) == OT_STRING)
	{
		SQUserPointer data;
		sq->getuserpointer(v, 2, &data);
		const SQChar* query;
		sq->getstring(v, 3, &query);

		sqlite3* db = (sqlite3*)data;
		sqlite3_stmt* stmt;
		if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK)
		{
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				sq->pushuserpointer(v, stmt);
				return 1;
			}
			else sqlite3_finalize(stmt);
		}
		else return sq->throwerror(v, sqlite3_errmsg(db));
	}

	sq->pushnull(v);
	return 1;
}

_SQUIRRELDEF(SQLite_GetNextRow)
{
	if (sq->gettop(v) == 2 &&
		sq->gettype(v, 2) == OT_USERPOINTER)
	{
		SQUserPointer data;
		sq->getuserpointer(v, 2, &data);

		if (sqlite3_step((sqlite3_stmt*)data) == SQLITE_ROW)
		{
			sq->pushbool(v, SQTrue);
			return 1;
		}
	}

	sq->pushbool(v, SQFalse);
	return 1;
}

_SQUIRRELDEF(SQLite_GetColumnCount)
{
	if (sq->gettop(v) == 2 &&
		sq->gettype(v, 2) == OT_USERPOINTER)
	{
		SQUserPointer data;
		sq->getuserpointer(v, 2, &data);

		sq->pushinteger(v, sqlite3_column_count((sqlite3_stmt*)data));
		return 1;
	}

	sq->pushinteger(v, 0);
	return 1;
}

_SQUIRRELDEF(SQLite_GetColumnData)
{
	if (sq->gettop(v) == 3 &&
		sq->gettype(v, 2) == OT_USERPOINTER &&
		sq->gettype(v, 3) == OT_INTEGER)
	{
		SQInteger columnIndex;
		sq->getinteger(v, 3, &columnIndex);

		if (columnIndex >= 0)
		{
#ifdef _SQ64
			if (columnIndex <= INT_MAX)
			{
#endif
				SQUserPointer data;
				sq->getuserpointer(v, 2, &data);

				sqlite3_stmt* stmt = (sqlite3_stmt*)data;
				int colIdx = (int)columnIndex;
				if (colIdx < sqlite3_column_count(stmt))
				{
					switch (sqlite3_column_type(stmt, colIdx))
					{
					case SQLITE_INTEGER:
#ifdef _SQ64
						sq->pushinteger(v, sqlite3_column_int64(stmt, colIdx));
#else
						sq->pushinteger(v, sqlite3_column_int(stmt, colIdx));
#endif
						return 1;

					case SQLITE_FLOAT:
						sq->pushfloat(v, (SQFloat)sqlite3_column_double(stmt, colIdx));
						return 1;

					case SQLITE_TEXT:
					case SQLITE_BLOB:
						sq->pushstring(v, (const SQChar*)sqlite3_column_text(stmt, colIdx), -1);
						return 1;
					}
				}
				else return sq->throwerror(v, _SC("column index is out of bounds"));
#ifdef _SQ64
			}
			else return sq->throwerror(v, _SC("column index is too big"));
#endif
		}
		else return sq->throwerror(v, _SC("column index is negative"));
	}

	sq->pushnull(v);
	return 1;
}

_SQUIRRELDEF(SQLite_FreeQuery)
{
	if (sq->gettop(v) == 2 &&
		sq->gettype(v, 2) == OT_USERPOINTER)
	{
		SQUserPointer data;
		sq->getuserpointer(v, 2, &data);

		sqlite3_finalize((sqlite3_stmt*)data);
	}

	return 0;
}

_SQUIRRELDEF(SQLite_EscapeString)
{
	if (sq->gettop(v) == 2 &&
		sq->gettype(v, 2) == OT_STRING)
	{
		const SQChar* string;
		sq->getstring(v, 2, &string);

		char* result = sqlite3_mprintf("%q", string);
		if (result)
		{
			sq->pushstring(v, result, -1);
			sqlite3_free(result);
			return 1;
		}
		else return sq->throwerror(v, _SC("sqlite3_mprintf() failed to allocate memory -- not your fault!"));
	}

	sq->pushnull(v);
	return 1;
}
