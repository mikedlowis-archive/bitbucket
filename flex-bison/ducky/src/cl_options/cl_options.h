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
#ifndef CL_OPTIONS_H
#define CL_OPTIONS_H

#include "common.h"
#include <list>

void CLO_ParseOptions(U32 argc, String* argv);
void CLO_Cleanup(void);
std::list<String>* CLO_GetFileList(void);

#define PROTOTYPE(type,name) \
	type CLO_Get##name(void); \
	void CLO_Set##name(type)

#define DECLARE(type,name) \
	static type name; \
	type CLO_Get##name(void) { return name; } \
	void CLO_Set##name(type x) { name = x; }

#define CLO_GET(name) CLO_Get##name()
#define CLO_SET(name,value) CLO_Set##name(value)


PROTOTYPE(BOOL,DebugAST);
PROTOTYPE(BOOL,DebugSCM);
PROTOTYPE(BOOL,InterpretMode);

#endif
