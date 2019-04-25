// Copyright (c) 2015
// Author: Chrono Law
#include <iostream>
#include <set>
#include <boost/core/ignore_unused.hpp>
#include <boost/smart_ptr.hpp>
using namespace boost;

//////////////////////////////////////////

class sample
{
private:
    class impl;
    shared_ptr<impl> p;
public:
    sample();
    void print();
};

class sample::impl
{
public:
    void print()
    {   std::cout << "impl print" << std::endl;}
};

sample::sample():p(new impl){}

void sample::print()
{   p->print();}

void case1()
{
    sample s;
    s.print();
}

//////////////////////////////////////////

class abstract
{
public:
    virtual void f() = 0;
    virtual void g() = 0;
protected: // 这里子类可以调用它的析构函数
    virtual ~abstract() = default;
};

class impl:public abstract
{
public:
    impl() = default;
    virtual ~impl() = default;
public:
    virtual void f()
    {   std::cout << "class impl f" << std::endl; }
    virtual void g()
    {   std::cout << "class impl g" << std::endl; }
};

shared_ptr<abstract> create()
//{   return shared_ptr<abstract>(new impl);}
{   return make_shared<impl>();}

void case2()
{
    auto p = create();
    p->f();
    p->g();

    abstract *q = p.get();
    boost::ignore_unused(q);
    //delete q; // 错误使用，因为无法访问abstract的保护析构函数
}

//////////////////////////////////////////

class socket_t {};

socket_t* open_socket()
{
    std::cout << "open_socket" << std::endl;
    return new socket_t;
}

void close_socket(socket_t * s)
{
    std::cout << "close_socket" << std::endl;
    // 其他操作，释放资源
    // ....
}

void case3()
{
    socket_t *s = open_socket();
    shared_ptr<socket_t> p(s, close_socket);
    //shared_ptr<socket_t> p(s, &close_socket);
}

//////////////////////////////////////////

bool case4()
{
    auto p = make_shared<int>(776);

    assert(p);  // 隐式转换
    if(p)       // 隐式转换
    {
        std::cout << "explicit cast" << std::endl;
    }

    //return !!p;
    return static_cast<bool>(p);    // 返回值必须显示转换
}

//////////////////////////////////////////

void any_func(void* p)
{   std::cout << "some operate" << std::endl;}

void case5()
{
    shared_ptr<void> p(nullptr, any_func);
}

//////////////////////////////////////////

void case6()
{
    auto p1 = make_shared<std::pair<int, int>>(0,1);

    shared_ptr<int> p2(p1, &p1->second);        // 别名构造

    assert(p1.use_count() == 2 &&               // 原引用计数增加
           p1.use_count() == p2.use_count());   // 两者引用计数相同
    assert((void*)p1.get() != (void*)p2.get()); // 但指向的内容不同
    assert(&p1->second == p2.get());            // 指向的是另外的指针
}

//////////////////////////////////////////
#include <boost/smart_ptr/owner_less.hpp>

void case7()
{
    typedef shared_ptr<int> int_ptr;
    typedef owner_less<int_ptr> int_ptr_less;

    int_ptr p1(new int(10));
    int n = 20;
    int_ptr p2(p1, &n); // 别名构造

    assert(!int_ptr_less()(p1, p2) &&   // 两者即不小于
           !int_ptr_less()(p2, p1));    // 也不大于，即等价

    typedef std::set<int_ptr> int_set;

    int_set s;
    s.insert(p1);
    s.insert(p2);
    assert(s.size() == 1);  // 因为p1,p2等价，所以集合s里只有一个元素
}

int main()
{
    std::cout << "\n********** Case 1 桥接模式 **********\n";
    case1();
    std::cout << "\n********** Case 2 工厂模式 **********\n";
    case2();
    std::cout << "\n********** Case 3 定制删除器 **********\n";
    case3();
    std::cout << "\n********** Case 4 显示转型 **********\n";
    case4();
    std::cout << "\n********** Case 5 指针转型 **********\n";
    case5();
    std::cout << "\n********** Case 6 别名构造 **********\n";
    case6();
    std::cout << "\n********** Case 7 弱序关系 **********\n";
    case7();
}
