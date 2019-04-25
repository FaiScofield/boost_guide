// Copyright (c) 2015
// Author: Chrono Law
#include <iostream>
using namespace std;

#include <boost/bimap.hpp>
#include <boost/bimap/vector_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include <boost/bimap/unconstrained_set_of.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    cout << "\n********** Case 1 **********\n";
    bimap<int, string> bm;


    bm.left.insert(make_pair(1, "111"));
    bm.left.insert(make_pair(2, "222"));


    bm.right.insert(make_pair("string", 10));
    bm.right.insert(make_pair("bimap", 20));


    for (auto pos = bm.left.begin(); pos != bm.left.end(); ++pos) {
        cout << "left[" << pos->first << "]=" << pos->second << endl;
    }

    // 迭代器返回常量对象const,无法赋值
//    bm.right.begin()->second = 234;
    {
        bimap<int, string> bm;
        typedef decltype(bm)::value_type vt;
        bm.insert(vt(3, "333"));

    }
}

//////////////////////////////////////////
using namespace boost::bimaps;
// 左-有序集合，右-无序集合
bimap<int, unordered_set_of<string> > bm1;
// 左右都是有序多值集合
bimap<multiset_of<int>, multiset_of<string> > bm2;
// 左-无序集合，右-序列，只能有左视图
bimap<unordered_set_of<int>, list_of<string> > bm3;
// 左-随机访问集合，右-无约束
bimap<vector_of<int>, unconstrained_set_of<string> > bm4;

template<typename T>
void print_map(T &m)
{
    for (auto& x : m)
        cout << x.first << "<-->"<< x.second << endl;
    cout << endl;
}


void case2()
{
    cout << "\n********** Case 2 **********\n";
    bimap<unordered_multiset_of<int>, unordered_multiset_of<string> > bm;

    bm.left.insert(make_pair(1, "111"));
    bm.left.insert(make_pair(2, "222"));
    bm.left.insert(make_pair(2, "555"));

    bm.right.insert(make_pair("string", 10));
    bm.right.insert(make_pair("bimap", 20));
    bm.right.insert(make_pair("bimap", 2));

    print_map(bm.left);

    {
        bimap<set_of<int>, vector_of<string> > bm;

        bm.left.insert(make_pair(1, "111"));
        bm.left[2] = "222";
        bm.left[300] = "bimap";

//        bm.right.insert(make_pair("string", 10)); // 编译错误

        print_map(bm.left);
    }
}

//////////////////////////////////////////
bimap<tagged<int, struct id>, vector_of<string> > bm11;
bimap<multiset_of<tagged<int, struct id>>, unordered_set_of<tagged<string, struct name>> > bm12;

// 通过打标签来访问左/右视图
void case3()
{
    cout << "\n********** Case 3 **********\n";
    bimap<tagged<int, struct id>, tagged<string, struct name> > bm;

    bm.by<id>().insert(make_pair(1, "samus"));
    bm.by<id>().insert(make_pair(2, "adam"));

    bm.by<name>().insert(make_pair("link", 10));
    bm.by<name>().insert(make_pair("zelda", 11));

    print_map(bm.by<name>());
}

//////////////////////////////////////////
#include <boost/assign.hpp>
void case4()
{
    cout << "\n********** Case 4 **********\n";
    using namespace boost::bimaps;
    typedef bimap<multiset_of<int>, vector_of<string> > bm_t;

    bm_t bm = assign::list_of<bm_t::relation>(1, "111")(2, "222");
    //bm_t bm = {{1, "111"},{2, "222"}};

    assign::insert(bm.left)(3, "333")(4, "444");
    assign::push_back(bm.right)("555", 5)("666", 6);

    auto left_pos  = bm.left.find(3);
    auto right_pos = bm.project_right(left_pos);
    cout << "right:[" << right_pos->first
         << "]=" << right_pos->second;

}

//////////////////////////////////////////
#include <boost/bimap/support/lambda.hpp>
void case5()
{
    cout << "\n********** Case 5 **********\n";
    using namespace boost::bimaps;
    typedef bimap<int, string > bm_t;

    using namespace boost::assign;
    bm_t bm = assign::list_of<bm_t::relation>
        (1, "mario")(2, "peach");

    auto pos = bm.left.find(1);
    cout << "[" << pos->first
        << "]=" << pos->second << endl;
    auto pos2 = bm.right.find("peach");
    cout << "[" << pos2->first
        << "]=" << pos2->second << endl;

    //pos = bm.left.find(1);
    //bm.left.replace_key(pos, 111);
    //bm.left.replace_data(pos, "luigi");

    pos = bm.left.find(1);
    bm.left.modify_key(pos, _key = 111);
    bm.left.modify_data(pos, _data = "luigi");
    cout << "[" << pos->first
        << "]=" << pos->second << endl;
}

//////////////////////////////////////////
void case6()
{
    cout << "\n********** Case 6 **********\n";
    using namespace boost::bimaps;
    typedef bimap<set_of<tagged<int,struct id> >,
            multiset_of<tagged<string,struct name> > > bm_t;

    using namespace boost::assign;

    bm_t bm = assign::list_of<bm_t::relation>(1, "mario")(2, "peach");
        insert(bm.by<id>())(3, "wario")(4, "luigi");
        insert(bm.by<name>())("yoshi", 5)("olima", 6);

    auto right_pos = bm.by<name>().find("yoshi");
    auto left_pos  = bm.project<id>(right_pos);
    ++left_pos;
    cout << "left:[" << left_pos->get<id>()
        << "]=" << left_pos->get<name>();

}

//////////////////////////////////////////
void case7()
{
    cout << "\n********** Case 7 **********\n";
    typedef bimap<int, string> bm_t;
    bm_t bm;
    // 插入时用 left_value_type 比 make_pair() 更快，因为避免了对象的拷贝函数调用
    bm.left.insert(bm_t::left_value_type(1, "one"));
    bm.right.insert(bm_t::right_value_type("two", 222));

}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
    case6();
    case7();
}
