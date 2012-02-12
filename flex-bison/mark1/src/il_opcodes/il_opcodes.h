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
#ifndef IL_OPCODES_H
#define IL_OPCODES_H

#include "common.h"

typedef enum
{
	ROOT    = 0,
	ADD     = 1,
	SUB     = 2,
	MUL     = 3,
	DIV     = 4,
	MOD     = 5,
	AND     = 6,
	OR      = 7,
	NOT     = 8,
	EQ      = 9,
	NE      = 10,
	LT      = 11,
	GT      = 12,
	LTE     = 13,
	GTE     = 14,
	ASSIGN  = 15,

	TERN    = 16,
	ARRAY   = 17,
	MAP     = 18,
	FUNC    = 19,

	ID      = 251,
	INT     = 252,
	FLOAT   = 253,
	STRING  = 254,
	BOOLEAN = 255,
} Opcode_T;

typedef struct
{
	Opcode_T opcode;
	String   display_txt;
	String   macro_txt;
} OpcodeInfo_T;

OpcodeInfo_T* IL_LookupOpcodeDefinition( Opcode_T opcode );
String IL_LookupDisplayText( Opcode_T opcode );
String IL_LookupMacroText( Opcode_T opcode );

#endif
