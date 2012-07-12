/*
 *  BitRPG
 *  UnitTest.h
 */


#ifndef BitRPG_UnitTest_h
#define BitRPG_UnitTest_h

class UnitTest
{
public:
	virtual void check() =0;
	
	// Static functions
	static void assertTrue(bool condition);
	static void assertFalse(bool condition);
	
	static void assertEquals(int expected, int actual);
	static void assertEquals(double expected, double actual, double delta);
	static void assertEquals(const char *expected, const char *actual);
};

#endif
