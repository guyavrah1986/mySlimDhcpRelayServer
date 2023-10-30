#include <iostream>
#include <gtest/gtest.h>

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
