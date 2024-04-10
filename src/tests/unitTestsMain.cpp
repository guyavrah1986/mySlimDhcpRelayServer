#include <iostream>
#include <gtest/gtest.h>

// Local include files for the different objects we wish to test
// Each header file listed here contains GTest unit tests for some objects
#include "cpp11ThreadWrapperTest.h"
#include "sampleObjectTests.h"
#include "dataBaseManagerTest.h"

using namespace std;

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	cout << "main - START of unit tests" << endl;
	int unitTestRetCode = RUN_ALL_TESTS();
	cout << "main - END of unit tests" << endl;
	return unitTestRetCode;
}
