/******************************************************************************
 *  Copyright (C) 2011  Michael D. Lowis
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#include <getopt.h>
#include <stdlib.h>
#include "cl_options.h"
#include <iostream>

STATIC void HandleLongOption(U8 opt_index);
STATIC void HandleShortOption(U8 opt);
STATIC void BuildFileList(U32 argc, String* argv);

using namespace std;

/******************************************************************************
 * Globals
 *****************************************************************************/
const string Help_String(
"Usage: mark1 [options] file...\n"
"Options:\n"
"  --help            Prints available options\n"
"  --debug-ast       Enables debug printing of the abstract syntax tree.\n"
"  --debug-scm       Enables debug printing of the generated scheme code.\n"
);

// Short Options List
const string Short_Options("");

// Long Options List
const struct option Long_Options[] = {
	{"help",      0, 0, 0},
	{"debug-ast", 0, 0, 0},
	{"debug-scm", 0, 0, 0},
	{"interpret", 0, 0, 0},
	{0,0,0,0}
};
#define IDX_HELP      ((U8)0)
#define IDX_DEBUG_AST ((U8)1)
#define IDX_DEBUG_SCM ((U8)2)
#define IDX_INTERPRET ((U8)3)

STATIC list<String>* FileList = NULL;

// Option Variables
DECLARE(BOOL,DebugAST);
DECLARE(BOOL,DebugSCM);
DECLARE(BOOL,InterpretMode);

/******************************************************************************
 * Private Functions
 *****************************************************************************/
void HandleLongOption(U8 opt_index)
{
	switch( opt_index )
	{
		case IDX_HELP:
			cout << Help_String;
			exit(0);
			break;
		case IDX_DEBUG_AST:
			CLO_SET(DebugAST,TRUE);
			break;
		case IDX_DEBUG_SCM:
			CLO_SET(DebugSCM,TRUE);
			break;
		case IDX_INTERPRET:
			CLO_SET(InterpretMode,TRUE);
		default:
			break;
	}
}

void HandleShortOption(U8 opt)
{
	switch( opt )
	{
		default:
			break;
	}
}

void BuildFileList(U32 argc, String* argv)
{
	FileList = _new list<String>();
	while ((U32)optind < argc)
	{
		FileList->push_back( argv[optind++] );
	}
}

/******************************************************************************
 * Public Functions
 *****************************************************************************/
void CLO_ParseOptions(U32 argc, String* argv)
{
	S8 opt = 0;
	U8 opt_index = 0;
	while(1)
	{
		opt = getopt_long(argc, argv, Short_Options.c_str(), Long_Options, (int*)&opt_index);
		if (opt == -1)
		{
			break;
		}

		if(opt == 0)
		{
			HandleLongOption(opt_index);
		}
		else
		{
			HandleShortOption(opt);
		}
	}
	BuildFileList(argc,argv);
}

void CLO_Cleanup(void)
{
	delete FileList;
}

list<String>* CLO_GetFileList(void)
{
	return FileList;
}

