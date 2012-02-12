#include "unity.h"

// File to Test
#include "linked_list.c"

void setUp(void)
{

}

void tearDown(void)
{

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
void test_LL_Last(void)
{
// Setup
// Expected Function Calls
// Function to Test
// Asserts
}

//-----------------------------------------------------------------------------
void test_LL_Get(void)
{
// Setup
// Expected Function Calls
// Function to Test
// Asserts
}

//-----------------------------------------------------------------------------
void test_LL_Add(void)
{
// Setup
// Expected Function Calls
// Function to Test
// Asserts
}

//-----------------------------------------------------------------------------
void test_LL_Insert(void)
{
// Setup
// Expected Function Calls
// Function to Test
// Asserts
}

//-----------------------------------------------------------------------------
void test_Delete(void)
{
// Setup
// Expected Function Calls
// Function to Test
// Asserts
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

