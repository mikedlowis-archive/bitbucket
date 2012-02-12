#include "linked_list.h"
#include <stdlib.h>

LinkedList_T* LL_New( PTR_TYPE contents )
{
	LinkedList_T* list = (LinkedList_T*)malloc( sizeof(LinkedList_T) );
	list->contents = contents;
	list->next = NULL;
	return list;
}

LinkedList_T* LL_Last(LinkedList_T* list)
{
	LinkedList_T* node = list;
	while((node != NULL) && (node->next != NULL))
	{
		node = node->next;
	}
	return node;
}

LinkedList_T* LL_Get(LinkedList_T* list, int index)
{
	int current = 0;
	LinkedList_T* node = list;
	LinkedList_T* indexed_node = NULL;
	while ((node != NULL) && (node->next != NULL))
	{
		current++;
		node = node->next;
		if ( current == index )
		{
		indexed_node = node;
		break;
		}
	}
	return indexed_node;
}

void LL_Add( LinkedList_T* list, PTR_TYPE contents )
{
	LinkedList_T* node = LL_Last( list );
	node->next = LL_New( contents );
}

void LL_Insert( LinkedList_T* list, int index, PTR_TYPE contents)
{
	LinkedList_T* node = LL_Get( list, index );
	node->next = LL_New( contents );
}

void LL_Delete( LinkedList_T* list, int index )
{
	LinkedList_T* node = LL_Get( list, (index-1));
	if((node != NULL) && (node->next != NULL))
	{
		LinkedList_T* node_to_delete = node->next;
		node->next = node_to_delete->next;
		free(node_to_delete);
	}
}

void LL_Free( LinkedList_T* list)
{
	LinkedList_T* node = list;
	while( node != NULL )
	{
		LinkedList_T* next = node->next;
		free(node);
		node = next;
	}
}
