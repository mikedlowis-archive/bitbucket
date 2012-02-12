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
#ifndef DBG_H
#define DBG_H

#include "common.h"

#define DEBUG
#ifdef DEBUG
	#define DBG_BREAKPOINT() DBG_Breakpoint(__FILE__, __LINE__)
	#define DBG_ASSERT(cond) DBG_Assert(__FILE__, __LINE__, QUOTE(cond), cond)
	#define DBG_WATCH()
#else
	#define DBG_BREAKPOINT()
	#define DBG_ASSERT()
	#define DBG_WATCH()
#endif

inline void DBG_Breakpoint(String file, U32 line);
inline void DBG_Assert(String file, U32 line, String cond_text, BOOL condition);

#endif
