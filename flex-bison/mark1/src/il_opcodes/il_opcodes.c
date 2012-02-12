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
#include "il_opcodes.h"

/******************************************************************************
 * Globals
 *****************************************************************************/
STATIC const OpcodeInfo_T Opcode_Info_Lookup[] = {
	{ ROOT,    "ROOT",    "ModuleStart" },
	{ ADD,     "ADD",     "Add" },
	{ SUB,     "SUB",     "Subtract" },
	{ MUL,     "MUL",     "Multiply" },
	{ DIV,     "DIV",     "Divide" },
	{ MOD,     "MOD",     "Modulus" },
	{ AND,     "AND",     "And" },
	{ OR,      "OR",      "Or" },
	{ NOT,     "NOT",     "Not" },
	{ EQ,      "EQ",      "Equal" },
	{ NE,      "NE",      "NotEqual" },
	{ LT,      "LT",      "LessThan" },
	{ GT,      "GT",      "GreaterThan" },
	{ LTE,     "LTE",     "LessOrEqual" },
	{ GTE,     "GTE",     "GreatOrEqual" },
	{ ASSIGN,  "ASSIGN",  "Assign" },

	{ TERN,    "TERN",    NULL },
	{ ARRAY,   "ARRAY",   NULL },
	{ MAP,     "MAP",     NULL },
	{ FUNC,    "FUNC",    NULL },

	{ ID,      "ID",      NULL },
	{ INT,     "INT",     NULL },
	{ FLOAT,   "FLOAT",   NULL },
	{ STRING,  "STRING",  NULL },
	{ BOOLEAN, "BOOLEAN", NULL }
};

/******************************************************************************
 * Public Functions
 *****************************************************************************/
OpcodeInfo_T* IL_LookupOpcodeDefinition( Opcode_T opcode )
{
	U32 lower = 0;
	U32 upper = NUM_ELEMENTS(Opcode_Info_Lookup);
	OpcodeInfo_T* found_item = NULL;

	while( lower <= upper )
	{
		U32 index = ((upper - lower) / 2) + lower;
		OpcodeInfo_T* item = (OpcodeInfo_T*)&Opcode_Info_Lookup[index];
		
		if(opcode == item->opcode)
		{
			found_item = item;
			break;
		}
		else if(opcode > item->opcode)
		{
			lower = index;
		}
		else
		{
			upper = index;
		}
	}
	return found_item;
}

String IL_LookupDisplayText( Opcode_T opcode )
{
	OpcodeInfo_T* info = IL_LookupOpcodeDefinition( opcode );
	return (info == NULL) ? NULL : info->display_txt;
}

String IL_LookupMacroText( Opcode_T opcode )
{
	OpcodeInfo_T* info = IL_LookupOpcodeDefinition( opcode );
	return (info == NULL) ? NULL : info->macro_txt;
}

