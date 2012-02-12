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
 ******************************************************************************/

#include "ast_debug.h"
#include <stdio.h>

STATIC void PrintNodeDefinition(Node_T* tree);
STATIC BOOL HasChildren(Node_T* tree);
STATIC void PrintChildNode(Node_T* tree, int parent);
STATIC void PrintNode(Node_T* tree, int parent);

/******************************************************************************
 * Globals
 ******************************************************************************/
static int Node_Count = 0;

/******************************************************************************
 * Public Functions
 ******************************************************************************/
void PrintAST(Node_T* tree)
{
	Node_Count = 0;
	printf("digraph {\n");
	PrintNode(tree, 0);
	printf("}\n");
}

/******************************************************************************
 * Private Functions
 ******************************************************************************/
void PrintNodeDefinition(Node_T* tree)
{
	switch(tree->node_type)
	{
		case FLOAT:
			printf("\t%d [label=\"%f\"]\n", Node_Count, ((ValueNode_T*)tree)->value.Float);
			break;

		default:
			printf("\t%d [label=\"%d\"]\n", Node_Count, tree->node_type);
			break;
	}
}

BOOL HasChildren(Node_T* tree)
{
	return (tree->node_type < 240) ? TRUE : FALSE;
}

void PrintChildNode(Node_T* tree, int parent)
{
	if (tree != NULL)
	{
		printf("\t%d->%d\n", parent, ++Node_Count);
		PrintNode( tree, parent);
	}
}

void PrintNode(Node_T* tree, int parent)
{
	int current_node = Node_Count;
	PrintNodeDefinition(tree);
	if ( HasChildren(tree) )
	{
		LinkedList_T* child = tree->children;
		while (child != NULL)
		{
			PrintChildNode( (Node_T*)child->contents, current_node );
			child = child->next;
		}
	}
}

