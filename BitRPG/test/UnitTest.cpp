/*
 *  BitRPG
 *  UnitTest.cpp
 */

#include "UnitTest.h"

#include <assert.h>
#include <string.h>


void UnitTest::assertTrue(bool condition)
{
	assert(condition);
}


void UnitTest::assertFalse(bool condition)
{
	assert(!condition);
}


void UnitTest::assertEquals(int expected, int actual)
{
	assert(expected == actual);
}


void UnitTest::assertEquals(double expected, double actual, double delta)
{
	double difference = actual - expected;
	
	assert(-delta <= difference && difference <= delta);
}


void UnitTest::assertEquals(const char *expected, const char *actual)
{
	assert(strcmp(expected, actual) == 0);
}
