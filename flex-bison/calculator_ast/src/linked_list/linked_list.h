#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Some macro magic to change the pointer type of each cell
//#include  "ast.h"             // The include that contains the necessary typedef
#define   PTR_TYPE  void *    // The macro used within this module (default: (void *))

typedef struct LinkedList
{
	PTR_TYPE contents;
	struct LinkedList * next;
} LinkedList_T;

LinkedList_T* LL_New( PTR_TYPE contents );
LinkedList_T* LL_Last(LinkedList_T* list);
LinkedList_T* LL_Get(LinkedList_T* list, int index);
void LL_Add( LinkedList_T* list, PTR_TYPE contents );
void LL_Insert( LinkedList_T* list, int index, PTR_TYPE contents);
void LL_Delete( LinkedList_T* list, int index );
void LL_Free( LinkedList_T* list);

#endif
