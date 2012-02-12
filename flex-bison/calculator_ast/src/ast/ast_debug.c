#include "ast_debug.h"
#include <stdio.h>

// Types
typedef unsigned char BOOL;
typedef unsigned char U8;
typedef enum
{
	NONE      = 0,
	UNKNOWN   = 1,
	FLOAT_FMT = 2
} ParamType_T;
typedef struct
{
	int node_type;
	BOOL has_children;
	char* label_string;
	ParamType_T param_type;
} NodeDef_T;

#define TRUE        1
#define FALSE       0
#define CHILDREN    1
#define NO_CHILDREN 0

// Prototypes
void PrintNodeDefinition(Node_T* tree, NodeDef_T* def);
void PrintChildNode(Node_T* tree, int parent);
NodeDef_T* LookupNodeDef(int node_type);

// Globals
static int Node_Count = 0;
#define NODE_DEF_COUNT 7
static const NodeDef_T Node_Lookup_Table[ NODE_DEF_COUNT ] = {
	{ FLOAT, NO_CHILDREN, "\t%d [label=\"%4.2f\"]\n", FLOAT_FMT },
	{ ADD,   CHILDREN,    "\t%d [label=\"+\"]\n",     NONE },
	{ SUB,   CHILDREN,    "\t%d [label=\"-\"]\n",     NONE },
	{ MUL,   CHILDREN,    "\t%d [label=\"*\"]\n",     NONE },
	{ DIV,   CHILDREN,    "\t%d [label=\"/\"]\n",     NONE },
	{ MOD,   CHILDREN,    "\t%d [label=\"MOD\"]\n",   NONE },
	{ 0,     CHILDREN,    "\t%d [label=\"%d\"]\n",    UNKNOWN }
};


// Function Definitions
NodeDef_T* LookupNodeDef(int node_type)
{
	U8 i = 0;
	NodeDef_T* def = (NodeDef_T*) &Node_Lookup_Table[ NODE_DEF_COUNT - 1 ];
	for (i = 0; i < NODE_DEF_COUNT; i++)
	{
		if ( Node_Lookup_Table[i].node_type == node_type )
		{
		def = (NodeDef_T*) &Node_Lookup_Table[ i ];
		break;
		}
	}
	return def;
}

void PrintNodeDefinition(Node_T* tree, NodeDef_T* def)
{	
	switch (def->param_type)
	{
		case NONE:
			printf(def->label_string, Node_Count);
			break;

		case FLOAT_FMT:
			printf(def->label_string, Node_Count, ((ValueNode_T*)tree)->value.Float);
			break;

		case UNKNOWN:
		default:
			printf( Node_Lookup_Table[NODE_DEF_COUNT-1].label_string, Node_Count, tree->node_type);
			break;
	}
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
	int i = 0;
	NodeDef_T* def = LookupNodeDef(tree->node_type);
	PrintNodeDefinition(tree,def);
	if ( def->has_children )
	{
		LinkedList_T* child = tree->children;
		while (child != NULL)
		{
			PrintChildNode( (Node_T*)child->contents, current_node );
			child = child->next;
		}
	}
}

void PrintAST(Node_T* tree)
{
	Node_Count = 0;
	printf("digraph {\n");
	PrintNode(tree,0);
	printf("}\n");
}
