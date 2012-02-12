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
/******************************************************************************
 * Includes and Prototypes
 *****************************************************************************/
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "cl_options.h"
#include "linked_list.h"

STATIC void HandleLongOption(U8 opt_index);
STATIC void HandleShortOption(U8 opt);
STATIC void BuildFileList(U32 argc, String* argv);

/******************************************************************************
 * Globals
 *****************************************************************************/
const String Help_String =
"Usage: mark1 [options] file...\n"
"Options:\n"
"  --help            Prints available options\n"
"  --debug-ast       Enables debug printing of the abstract syntax tree.\n"
"  --debug-tac       Enables debug printing of the intermediat three address code.\n"
"  --debug-asm       Enables debug printing of the generated assembly code.\n"
;

// Short Options List
const String Short_Options = "";

// Long Options List
const struct option Long_Options[] = {
	{"help",      0, 0, 0},
	{"debug-ast", 0, 0, 0},
	{"debug-tac", 0, 0, 0},
	{"debug-asm", 0, 0, 0},
	{0,0,0,0}
};
#define IDX_HELP      ((U8)0)
#define IDX_DEBUG_AST ((U8)1)
#define IDX_DEBUG_TAC ((U8)2)
#define IDX_DEBUG_ASM ((U8)3)

// Option Variables
STATIC BOOL DebugAST = FALSE;
STATIC BOOL DebugTAC = FALSE;
STATIC BOOL DebugASM = FALSE;
STATIC LinkedList_T* FileList = NULL;

/******************************************************************************
 * Private Functions
 *****************************************************************************/
void HandleLongOption(U8 opt_index)
{
	switch( opt_index )
	{
		case IDX_HELP:
			printf("%s",Help_String);
			exit(0);
			break;
		case IDX_DEBUG_AST:
			CLO_SetDebugAST( TRUE );
			break;
		case IDX_DEBUG_TAC:
			CLO_SetDebugTAC( TRUE );
			break;
		case IDX_DEBUG_ASM:
			CLO_SetDebugASM( TRUE );
			break;
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
	while (optind < argc)
	{
		if (FileList == NULL)
		{
			FileList = LL_New( argv[optind++] );
		}
		else
		{
			LL_Add( FileList, argv[optind++] );
		}
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
		opt = getopt_long(argc, argv, Short_Options, Long_Options, (int*)&opt_index);
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

LinkedList_T* CLO_GetFileList(void)
{
	return FileList;
}

void CLO_SetDebugAST(BOOL enabled)
{
	DebugAST = enabled; 
}

BOOL CLO_GetDebugAST()
{
	return DebugAST;
}


void CLO_SetDebugTAC(BOOL enabled)
{
	DebugTAC = enabled;
}


BOOL CLO_GetDebugTAC()
{
	return DebugTAC;
}


void CLO_SetDebugASM(BOOL enabled)
{
	DebugASM = enabled;
}


BOOL CLO_GetDebugASM()
{
	return DebugASM;
}


