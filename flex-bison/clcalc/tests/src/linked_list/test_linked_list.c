#include "unity.h"
#include <stdlib.h>

// File to Test
#include "linked_list.h"

//-----------------------------------------------------------------------------

int* num1;
int* num2;
int* num3;
LinkedList_T* node1;
LinkedList_T* node2;
LinkedList_T* node3;

//-----------------------------------------------------------------------------

void setUp(void)
{
	num1 = (int*) malloc( sizeof(int) );
	num2 = (int*) malloc( sizeof(int) );
	num3 = (int*) malloc( sizeof(int) );
	*num1 = 0;
	*num2 = 1;
	*num3 = 2;
	node1 = (LinkedList_T*) malloc( sizeof(LinkedList_T) );
	node2 = (LinkedList_T*) malloc( sizeof(LinkedList_T) );
	node3 = (LinkedList_T*) malloc( sizeof(LinkedList_T) );
	node1->next = node2;
	node1->contents = num1;
	node2->next = node3;
	node2->contents = num2;
	node3->next = NULL;
	node3->contents = num3;
}

void tearDown(void)
{
	if( num1 != NULL )  free( num1 );
	if( num2 != NULL )  free( num2 );
	if( num3 != NULL )  free( num3 );
	if( node1 != NULL ) free( node1 );
	if( node2 != NULL ) free( node2 );
	if( node3 != NULL ) free( node3 );
}

//-----------------------------------------------------------------------------
void test_LL_New_should_return_a_new_linked_list_with_the_supplied_contents(void)
{
// Setup
	int num = 42;
// Expected Function Calls
// Function to Test
	LinkedList_T* list = LL_New(&num);
// Asserts
	TEST_ASSERT_NOT_EQUAL(NULL, list);
	TEST_ASSERT_EQUAL(&num, list->contents);
	TEST_ASSERT_EQUAL(NULL, list->next);
}

//-----------------------------------------------------------------------------
void test_LL_Last_should_return_a_pointer_to_the_last_element_in_the_linked_list_for_a_NULL_list(void)
{
// Setup
// Expected Function Calls
// Function to Test
	LinkedList_T* node = LL_Last(NULL);
// Asserts
	TEST_ASSERT_EQUAL( NULL, node );
}

void test_LL_Last_should_return_a_pointer_to_the_last_element_in_the_linked_list_for_a_list_of_length_1(void)
{
// Setup
// Expected Function Calls
// Function to Test
	LinkedList_T* node = LL_Last(node3);
// Asserts
	TEST_ASSERT_EQUAL(num3,node->contents);
}

void test_LL_Last_should_return_a_pointer_to_the_last_element_in_the_linked_list_for_a_list_of_length_2(void)
{
// Setup
// Expected Function Calls
// Function to Test
	LinkedList_T* node = LL_Last(node2);
// Asserts
	TEST_ASSERT_EQUAL(num3,node->contents);
}

void test_LL_Last_should_return_a_pointer_to_the_last_element_in_the_linked_list_for_a_list_of_length_3(void)
{
// Setup
// Expected Function Calls
// Function to Test
	LinkedList_T* node = LL_Last(node1);
// Asserts
	TEST_ASSERT_EQUAL(num3,node->contents);
}

//-----------------------------------------------------------------------------
void test_LL_Get_should_return_a_pointer_to_the_item_at_the_supplied_index_within_a_list_of_size_1(void)
{
// Setup
// Expected Function Calls
// Function to Test
	LinkedList_T* node = LL_Get(node3,0);
// Asserts
	/*TEST_ASSERT_EQUAL(num3,node->contents);*/
}

void test_LL_Get_should_return_a_pointer_to_the_item_at_the_supplied_index_within_a_list_of_size_3(void)
{
// Setup
// Expected Function Calls
// Function to Test
	LinkedList_T* node = LL_Get(node1,1);
// Asserts
	TEST_ASSERT_EQUAL(num2,node->contents);
}

void test_LL_Get_should_return_NULL_if_the_supplied_index_is_out_of_range(void)
{
// Setup
// Expected Function Calls
// Function to Test
	LinkedList_T* node = LL_Get(node1,6);
// Asserts
	TEST_ASSERT_EQUAL(NULL,node);
}

void test_LL_Get_should_return_NULL_if_a_null_list_is_supplied(void)
{
// Setup
// Expected Function Calls
// Function to Test
	LinkedList_T* node = LL_Get(NULL,6);
// Asserts
	TEST_ASSERT_EQUAL(NULL,node);
}

//-----------------------------------------------------------------------------
void test_LL_Add_should_add_a_new_node_containing_the_specified_pointer_to_the_end_of_the_supplied_list(void)
{
// Setup
// Expected Function Calls
// Function to Test
	LL_Add(node1,num2);
// Asserts
	TEST_ASSERT_NOT_EQUAL( NULL, node1->next );
	TEST_ASSERT_EQUAL( num2, (node1->next)->contents );
}

//-----------------------------------------------------------------------------
void test_LL_Insert(void)
{
// Setup
// Expected Function Calls
// Function to Test
	LinkedList_T* node = LL_Insert(node1,1,num3);
// Asserts
	TEST_ASSERT_NOT_EQUAL( NULL, node );
	TEST_ASSERT_EQUAL( node, node1->next );
	TEST_ASSERT_EQUAL( num3, node->contents );
}

//-----------------------------------------------------------------------------
void test_Delete_should_remove_and_free_the_first_element_in_the_linked_list(void)
{
// Setup
// Expected Function Calls
	
// Function to Test
	LL_Delete(node1,0);
// Asserts
	/*TEST_ASSERT_EQUAL( NULL, node1 );*/
}

//-----------------------------------------------------------------------------
void test_Free(void)
{
// Setup

// Expected Function Calls

// Function to Test
	
// Asserts

}

//-----------------------------------------------------------------------------

