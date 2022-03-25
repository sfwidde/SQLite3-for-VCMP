#include "SQFuncs.h"
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

_SQUIRRELDEF(SQLite_Connect);
_SQUIRRELDEF(SQLite_Disconnect);
_SQUIRRELDEF(SQLite_Query);
_SQUIRRELDEF(SQLite_GetNextRow);
_SQUIRRELDEF(SQLite_GetColumnCount);
_SQUIRRELDEF(SQLite_GetColumnData);
_SQUIRRELDEF(SQLite_FreeQuery);
_SQUIRRELDEF(SQLite_EscapeString);

void RegisterFuncs( const HSQUIRRELVM v )
{
	RegisterSquirrelFunc(v, SQLite_Connect, _SC("SQLite_Connect"), 1, _SC("s"));
	RegisterSquirrelFunc(v, SQLite_Disconnect, _SC("SQLite_Disconnect"), 1, _SC("p"));
	RegisterSquirrelFunc(v, SQLite_Query, _SC("SQLite_Query"), 2, _SC("ps"));
	RegisterSquirrelFunc(v, SQLite_GetNextRow, _SC("SQLite_GetNextRow"), 1, _SC("p"));
	RegisterSquirrelFunc(v, SQLite_GetColumnCount, _SC("SQLite_GetColumnCount"), 1, _SC("p"));
	RegisterSquirrelFunc(v, SQLite_GetColumnData, _SC("SQLite_GetColumnData"), 2, _SC("pi"));
	RegisterSquirrelFunc(v, SQLite_FreeQuery, _SC("SQLite_FreeQuery"), 1, _SC("p"));
	RegisterSquirrelFunc(v, SQLite_EscapeString, _SC("SQLite_EscapeString"), 1, _SC("s"));
}
