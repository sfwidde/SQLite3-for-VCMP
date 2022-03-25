#pragma once
#ifndef __SQFUNCS_H
#define __SQFUNCS_H

#include "SQModule.h"

SQInteger				RegisterSquirrelFunc				( HSQUIRRELVM v, SQFUNCTION f, const SQChar* fname, unsigned char uiParams, const SQChar* szParams );
void					RegisterFuncs						( const HSQUIRRELVM v );

#define _SQUIRRELDEF(x) SQInteger x( HSQUIRRELVM v )

#endif
