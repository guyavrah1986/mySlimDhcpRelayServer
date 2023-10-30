#include <iostream>

#include "include/cpp11ThreadWrapper.h"

using namespace std;

SampleObj1::SampleObj1(int i) : m_i(i)
{
	cout << "SampleObj1::SampleObj1 - setting m_i to:" << m_i << endl;
}

SampleObj1::~SampleObj1()
{
	cout << "SampleObj1::~SampleObj1" << endl;
}
