// Copyright (c) 2015
// Author: Chrono Law
#include <iostream>
#include <assert.h>
using namespace std;

#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    tribool tb(true);
    tribool tb2(!tb);

    if (tb)
    {   cout << "true" << endl; }

    tb2 = indeterminate;
    assert(indeterminate(tb2));
    cout << "tb2 = " << tb2 << endl;

    if (tb2 == indeterminate)                   // 与indeterminate值比较，无意义
    {   cout << "indeterminate" << endl;    }   // 这句语句不会执行

    if (indeterminate(tb2))
    {   cout << "indeterminate" << endl;    }

    cout << (tb2 || true )<< endl;
    cout << (tb2 && false )<< endl;

}

//////////////////////////////////////////
void case2()
{
    tribool tb(indeterminate);

    if (tb)
        cout << "never reach here" << endl;
    if (!tb)
        cout << "never reach here" << endl;

    if (indeterminate(tb))
        cout << "indeterminate" << endl;
}

//////////////////////////////////////////
BOOST_TRIBOOL_THIRD_STATE(unknown)

namespace tmp_ns
{
        BOOST_TRIBOOL_THIRD_STATE(unknown)
};


void case3()
{
    tribool tb(tmp_ns::unknown);
    assert(unknown(tb));
    assert(unknown(tb || false));

}

//////////////////////////////////////////
#include <boost/optional.hpp>
using namespace boost;

void case4()
{
    optional<bool> b;

    if (!b) // b未初始化，既不是true，也不是false
    {   cout << "indeterminate" << endl;    }

    b = false;
    if (b)
    {   cout << "b=" << *b << endl; }

    if (!b)
    {   cout << "false" << endl;    }

    if (b && !*b)
    {   cout << "real false" << endl;    }

}

//////////////////////////////////////////

int main()
{
    std::cout << "\n********** Case 1 **********\n";
    case1();
    std::cout << "\n********** Case 2 **********\n";
    case2();
    std::cout << "\n********** Case 3 **********\n";
    case3();
    std::cout << "\n********** Case 4 **********\n";
    case4();
}
