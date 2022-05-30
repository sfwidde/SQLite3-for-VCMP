cmake_minimum_required(VERSION 3.8)

project(sqlite3-for-vcmp)

if((NOT (UNIX AND NOT APPLE)) AND (NOT WIN32))
	message(FATAL_ERROR "unsupported platform")
endif()

add_library(
	sqlite3 SHARED
	
	vcmp.h
	main.h
	main.c
	callbacks.c
	functions.h
	functions.c
	
	sqlite3/sqlite3.h
	sqlite3/sqlite3.c
	
	squirrel/squirrel.h
	squirrel/SQModule.h
	squirrel/SQImports.h
	squirrel/SQFuncs.h
	squirrel/SQFuncs.c
)

if(MSVC)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

math(EXPR OUTPUT_SUFFIX "${CMAKE_SIZEOF_VOID_P} * 8")
set_target_properties(
	sqlite3 PROPERTIES
	OUTPUT_NAME sqlite3-${OUTPUT_SUFFIX}
	PREFIX ""
)
