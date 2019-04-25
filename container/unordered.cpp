// Copyright (c) 2015
// Author: Chrono Law
#include <iostream>
using namespace std;

#include <boost/assign.hpp>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
using namespace boost;


//////////////////////////////////////////
void case1()
{
    cout << "\n********** Case 1 **********\n";
    unordered_set<int> s = {1, 2, 3, 4, 5};

    for (auto x : s)
    {   cout << x << " ";   }
    cout << endl;
    cout << "size: " << s.size() << endl;

    s.clear();
    cout << "empty? " << s.empty() << endl;

    s.insert(8);
    s.insert(45);
    cout << "size: " << s.size() << endl;
    cout << "find 8: " << *s.find(8) << endl;

    s.erase(45);

//    using namespace boost::assign;
    unordered_set<int> us1 = boost::assign::list_of(1)(2)(3);
    unordered_set<int> us2 = boost::assign::list_of(3)(2)(1);
    assert(us1 == us2 );

}

//////////////////////////////////////////
void case2()
{
    cout << "\n********** Case 2 **********\n";

    typedef complex<double> complex_t;
    unordered_set<complex_t> s;

    s.emplace(1.0, 2.0);
    s.emplace(3.0, 4.0);

    for(auto& x : s)
    {    cout << x << ",";}
    cout << endl;

    s.emplace_hint(s.begin(), 5.0, 6.0);    // 在容器前端插入，不能保证位置
    for(auto& x : s)
    {    cout << x << ",";}

}


//////////////////////////////////////////
void case3()
{
    cout << "\n********** Case 3 **********\n";

    using namespace boost::assign;

    unordered_map<int, string> um =
        map_list_of(1,"one")(2, "two")(3, "three");

    um.insert(make_pair(10,"ten"));
    cout << um[10] << endl;     // 用operater[]访问键值为10的元素
    um[11] = "eleven";
    um[15] = "fifteen";

    auto p = um.begin();
    for (; p != um.end(); ++p)
    {   cout << p->first << "-" << p->second << ",";    }
    cout << endl;

    um.erase(11);
    cout << "size: " << um.size() << endl;

    unordered_map<int, string> um1 = map_list_of(1,"11")(2,"22");
    unordered_map<int, string> um2 = map_list_of(1,"one")(2,"two");
    assert(um1 != um2);

}

//////////////////////////////////////////
void case4()
{
    cout << "\n********** Case 4 **********\n";

    typedef complex<double> complex_t;
    typedef unordered_map<int, complex_t> um_t;
    um_t s;

    s.emplace(boost::unordered::piecewise_construct,    // piecewise_construct 分段构造pair
        make_tuple(1),make_tuple(1.0, 2.0));
    s.emplace(boost::unordered::piecewise_construct,
        make_tuple(3),make_tuple(3.0, 4.0));

    for(auto& x: s) {
        cout << x.first << "<->" << x.second << ",";
    }
    cout << endl;

    s.emplace_hint(s.begin(), boost::unordered::piecewise_construct, // 在前端放置元素
                   make_tuple(5), make_tuple(5.0, 6.0));
    for(auto& x: s) {
        cout << x.first << "<->" << x.second << ",";
    }

}

//////////////////////////////////////////
void case5()
{
    cout << "\n********** Case 5 **********\n";

    using namespace boost::assign;

    unordered_set<int> us = (list_of(1), 2, 3, 4);
    cout << us.bucket_count() << endl;      // 返回桶的数量

    cout << "size: " << endl;
    for (size_t i = 0; i < us.bucket_count(); ++i) {
        cout << us.bucket_size(i) << ",";   // 访问每个桶
    }
    cout << endl;

}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
}
