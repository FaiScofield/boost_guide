// Copyright (c) 2015
// Author: Chrono Law
#include <iostream>
//using namespace std;

#include <boost/smart_ptr.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    shared_ptr<int> sp(new int(10));
    assert(sp.use_count() == 1);

    weak_ptr<int> wp(sp);
    assert(wp.use_count() == 1);

    if (!wp.expired())
    {
        shared_ptr<int> sp2 = wp.lock();
        *sp2 = 100;
        assert(wp.use_count() == 2);
    }

    assert(wp.use_count() == 1);
    sp.reset();
    assert(wp.expired());
    assert(!wp.lock());
}

//////////////////////////////////////////

class self_shared:
    public enable_shared_from_this<self_shared>
{
public:
    self_shared(int n):x(n){}
    int x;
    void print()
    {   std::cout << "self_shared:" << x << std::endl;    }
};

void case2()
{
    auto sp = make_shared<self_shared>(313);
    sp->print();

    auto p = sp->shared_from_this();

    p->x = 1000;
    p->print();
}

//////////////////////////////////////////

class node
{
public:
    ~node()
    {     std::cout << "deleted" << std::endl;}

    typedef weak_ptr<node> ptr_type;
    //typedef shared_ptr<node> ptr_type;
    ptr_type next;
};

void case3()
{
    auto p1 = make_shared<node>();
    auto p2 = make_shared<node>();

    p1->next = p2;  // 形成列表循环
    p2->next = p1;

    assert(p1.use_count() == 1);    // 如果next是shared_ptr<node>,这里的计数就是2
    assert(p2.use_count() == 1);    // 退出作用域时，shared_ptr无法正确析构，会导致内存泄露

    if(!p1->next.expired())         // 检查弱引用是否有效
    {
        auto p3 = p1->next.lock();  // 调用lock()获得强引用
    }                               // 退出作用域，shared_ptr可以正确析构
}

//////////////////////////////////////////
#include <boost/smart_ptr/enable_shared_from_raw.hpp>

class raw_shared:
    public enable_shared_from_raw
{
public:
    raw_shared()
    {   std::cout << "raw_shared ctor" << std::endl;    }
    ~raw_shared()
    {   std::cout << "raw_shared dtor" << std::endl;    }
};

void case4()
{
    raw_shared x;
    assert(weak_from_raw(&x).use_count() == 1);
    auto px = shared_from_raw(&x);
    assert(px.use_count() == 2);

    auto p = new raw_shared;

    auto wp = weak_from_raw(p);
    assert(wp.use_count() == 1);

    decltype(shared_from_raw(p)) spx(p);

    auto sp = shared_from_raw(p);
    //std::cout << sp.use_count() << std::endl;
    assert(sp.use_count() == 2);

    //decltype(sp) spx(p);

    auto sp2 = sp;
    auto wp2 = weak_from_raw(p);
    assert(wp2.use_count() == 3);
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
