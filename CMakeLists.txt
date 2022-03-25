cmake_minimum_required(VERSION 3.8)

project("SQLite3 for VCMP")

add_library(sqlite3 SHARED
					vcmp.h
					main.h
					main.c
					callbacks.c
					functions.c
					
					sqlite3/sqlite3.h
					sqlite3/sqlite3.c
					
					squirrel/squirrel.h
					squirrel/SQModule.h
					squirrel/SQImports.h
					squirrel/SQFuncs.h
					squirrel/SQFuncs.c)

target_compile_definitions(sqlite3 PRIVATE PLUGIN_NAME="${CMAKE_PROJECT_NAME}")

if(NOT WIN32)
	# uncomment to force 32-bit compilation on Linux
	#set_target_properties(sqlite3 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()
