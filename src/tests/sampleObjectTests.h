
#include <gperftools/heap-checker.h>

class MySampleObject
{
    public:
        MySampleObject(int i, short s)
        {
            m_i = new int;
            m_s = new short;
            *m_i = i;
            *m_s = s;
        }

        ~MySampleObject()
        {
            delete m_i;
            delete m_s;
        }

        int *m_i;
        short *m_s;
};

TEST(sampleObjectTest, createSingleMySampleObject)
{ 
	std::cout << "sampleObjectTest::createSingleMySampleObject" << std::endl;
    HeapLeakChecker heap_checker("test_foo");
    {
	    MySampleObject* pTestedObj = new MySampleObject(12, 17);
        delete pTestedObj;
    }
    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
}