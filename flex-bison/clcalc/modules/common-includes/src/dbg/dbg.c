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
#include "dbg.h"

#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
 * Public Functions
 *****************************************************************************/
inline void DBG_Breakpoint(String file, U32 line)
{
	U8 c = 0;
	printf("Breakpoint [%s line %d] ", file, (int)line);
	c = getchar();
}

inline void DBG_Assert(String file, U32 line, String cond_text, BOOL condition)
{
	if(!condition)
	{
		printf("Assertion Failure [%s line %d] (%s)\n", file, (int)line, cond_text);
		exit(1);
	}
}
