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
#ifndef AST_H
#define AST_H

#include <stdarg.h>
#include "common.h"
#include "il_opcodes.h"
#include "linked_list.h"


/// Definition of the node type.
typedef Opcode_T NodeType_T;

/// The value portion of a node in the tree.
typedef union
{
	BOOL     Boolean;
	int      Integer;
	double   Float;
	char*    String;
} Value_T;

/// A parent node that contains an operator.
typedef struct
{
	NodeType_T    node_type;
	LinkedList_T* children;
} Node_T;

/// A child node that contains a value.
typedef struct
{
	NodeType_T node_type;
	Value_T    value;
} ValueNode_T;

/**
 * @brief Creates a new operator node with the specified number of children.
 *
 * This is a variadic function that takes a node type, a number of children,
 * and a variable number of NODE_T pointers representing the children of the
 * newly created node.
 *
 * @param	type           The type of node to create.
 * @param	child_count    The number of children you are passing in.
 * @param	...            A variable number of NODE_T pointers representing children.
 *
 * @return	Returns a pointer to the newly created node.
 **/
Node_T* NODE(NodeType_T type, int child_count, ...);

/**
 *
 **/
Node_T* NODE_APPEND(Node_T* node, Node_T* child);

/**
 * @brief	Creates and returns a new Boolean value node.
 *
 * This function takes the input string and converts it into a boolean value.
 * The boolean value is then stored as the contents of the newly created node.
 * A pointer to the newly created node is then returned to the caller.
 *
 * @param	value    String containing that data to use for this node.
 **/
Node_T* VAL_BOOL(char* value);

/**
 * @brief	Creates and returns a new Integer value node.
 *
 * This function takes the input string and converts it to a float using atoi().
 * The integer value is then used as the value of the newly created node. A
 * pointer to the newly created node is then returned to the caller.
 *
 * @param	value    String containing that data to use for this node.
 **/
Node_T* VAL_INT(char* value);

/**
 * @brief	Creates and returns a new Float value node.
 *
 * This function takes the input string and converts it to a float using atof().
 * The floating point value is then used as the value of the newly created node.
 * A pointer to the newly created node is then returned to the caller.
 *
 * @param	value    String containing that data to use for this node.
 **/
Node_T* VAL_FLOAT(char* value);

/**
 * @brief	Creates and returns a new String value node.
 *
 * This function takes the input string and uses it as the value of the newly
 * created node. A pointer to the newly created node is then returned to the
 * caller.
 *
 * @param	value    String containing that data to use for this node.
 **/
Node_T* VAL_STRING(char* value);

#endif
