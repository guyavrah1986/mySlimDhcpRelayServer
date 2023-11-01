#include <iostream>
#include <gtest/gtest.h>

// Local include files for the different objects we wish to test
// Each header file listed here contains GTest unit tests for some objects
#include "cpp11ThreadWrapperTest.h"

using namespace std;

TEST(SquareRootTest, PositiveNos)
{ 
	cout << "SquareRootTest - PositiveNos" << endl;
}
 
int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	cout << "main - start of unit tests" << endl;
	return RUN_ALL_TESTS();
}
