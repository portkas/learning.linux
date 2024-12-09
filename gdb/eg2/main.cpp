#include "stdio.h"
#include <iostream>
#include "stdlib.h"
using namespace std;
class base
{
public:
    base();
    virtual void test();
private:
    const char *basePStr;
};
class dumpTest : public base
{
public:
    void test();
    // dumpTest() : childPStr(new char[10]){}
private:
    char *childPStr;
};
base::base()
{
    basePStr = "test_info";
}
void base::test()
{
    cout<<basePStr<<endl;
}
void dumpTest::test()
{
    cout<<"dumpTest"<<endl;
    delete childPStr;
}

int main()
{
    dumpTest dump;
    dump.test();
    return 0;
}