// Copyright (c) 2015
// Author: Chrono Law

#include <boost/array.hpp>
#include <iostream>

using namespace boost;
using namespace std;

//////////////////////////////////////////
void case1()
{
    cout << "Case 1:\n";

    boost::array<int, 10> ar;   // 注意也有std::array

    ar[0] = 1;
    ar.back() = 10;
    assert(ar[ar.max_size() - 1] == 10);

    ar.assign(777);
    for (auto x : ar)
    {   cout << x << ",";   }
    cout << endl;

    int *p = ar.c_array();
    *(p + 5) = 253;
    cout << ar[5] << endl;

    ar.at(8) = 666;
    std::sort(ar.begin(), ar.end());
    for (auto x : ar)
    {   cout << x << ",";   }
    cout << endl;
}

//////////////////////////////////////////
#include <boost/assign.hpp>

void case2()
{
    cout << "Case 2:\n";
    boost::array<string, 3> ar = {"alice", "bob", "carl"};

    int a[10] = {0};
    boost::array<int, 10> ar1 = {0};
    assert(std::equal(ar1.begin(), ar1.end(), a));

    boost::array<string, 3> ar2 = {"racer"};
    assert(ar2.at(1).empty());

    using namespace boost::assign;
    boost::array<int, 3> arr(list_of(2)(4)(6)) ;

    for (auto i = 0u; i< arr.size(); ++i)
    {   cout << arr[i] << ",";}

}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
}
