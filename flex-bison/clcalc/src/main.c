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
#include <stdio.h>
#include "cl_options.h"
#include "control.h"
#include "hashtable.h"

int main(int argc, char** argv)
{
	U8 ret = 0;
	HashTable_T* table = Hash_New(128,NULL);
	CLO_ParseOptions(argc,argv);
	Control_StartInterpreter(table, stdin);
	return (int)ret;
}

