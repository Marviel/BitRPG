/*
 *  BitRPG
 *  SanityTest.cpp
 */

#include "SanityTest.h"

#include <string>

using namespace std;


void SanityTest::check()
{
	// Check the conditional asserts
	
	assertTrue(2 + 2 == 4);
	assertFalse(2 + 3 == 6);
	
	// Check the primitive equality asserts
	
	assertEquals("ANSI", "ANSI");
	assertEquals(3, 3);
	assertEquals(3.0, 2.99, 0.1);
	
	/*
	// Check the class equality assert
	
	string expectedString("C++");
	string actualString("C++");
	assertEquals(expectedString, actualString);
	 */
}