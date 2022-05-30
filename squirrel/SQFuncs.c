#include "../functions.h"
#include "../main.h"
#include <stdio.h>

extern HSQAPI sq;

SQInteger RegisterSquirrelFunc( HSQUIRRELVM v, SQFUNCTION f, const SQChar* fname, unsigned char ucParams, const SQChar* szParams )
{
	char szNewParams[32];

	sq->pushroottable( v );
	sq->pushstring( v, fname, -1 );
	sq->newclosure( v, f, 0 ); /* create a new function */

	if ( ucParams > 0 )
	{
		ucParams++; /* This is to compensate for the root table */

		sprintf( szNewParams, "t%s", szParams );
		sq->setparamscheck( v, ucParams, szNewParams ); /* Add a param type check */
	}

	sq->setnativeclosurename( v, -1, fname );
	sq->newslot( v, -3, SQFalse );
	sq->pop( v, 1 ); /* pops the root table */

	return 0;
}

void RegisterFuncs( const HSQUIRRELVM v )
{
	RegisterSquirrelFunc(v, SQLite_Open, "SQLite_Open", 1, "s");
	RegisterSquirrelFunc(v, SQLite_Close, "SQLite_Close", 1, "p");
	RegisterSquirrelFunc(v, SQLite_Prepare, "SQLite_Prepare", 2, "ps");
	RegisterSquirrelFunc(v, SQLite_GetNextRow, "SQLite_GetNextRow", 1, "p");
	RegisterSquirrelFunc(v, SQLite_GetColumnCount, "SQLite_GetColumnCount", 1, "p");
	RegisterSquirrelFunc(v, SQLite_GetColumnData, "SQLite_GetColumnData", 2, "pi");
	RegisterSquirrelFunc(v, SQLite_Finalize, "SQLite_Finalize", 1, "p");
	RegisterSquirrelFunc(v, SQLite_EscapeString, "SQLite_EscapeString", 1, "s");
}
