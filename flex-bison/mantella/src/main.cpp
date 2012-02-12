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
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "cl_options.h"
#include "parser.h"
#include "scheme.h"

using namespace std;

const string Compiler_Cmd("csc -I/c/chicken/include/chicken/ -");
const string Interpreter_Cmd("csi");

int main(int argc, char** argv)
{
	U8 ret = 0;
	list<String>* files;
	Parser* parser = _new Parser(_new SchemeFactory());
	CLO_ParseOptions(argc,argv);
	files = CLO_GetFileList();

	if(!files->empty())
	{
		parser->parseFile( _new string(files->front()) );
	}
	
	delete parser;
	CLO_Cleanup();
	REPORT_LEAKS();
	return (int)ret;
}

