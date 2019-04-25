// Copyright (c) 2015
// Author: Chrono Law
#include <iostream>
#include <exception>
#include <map>
#include <vector>
#include <boost/smart_ptr.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    shared_ptr<int> spi(new int);
    assert(spi);
    *spi = 253;
    std::cout << *spi << std::endl;

    shared_ptr<std::string>  sps(new std::string("smart"));
    assert(sps->size() == 5);

    //shared_ptr<int> dont_do_this(new int[10]); // 危险！不能正确释放内存！
}

//////////////////////////////////////////

void case2()
{
    typedef shared_ptr<std::string> sp_t;
    std::map<sp_t, int> m;

    sp_t sp(new std::string("one"));
    m[sp] = 111;    // 关联数组用法

    shared_ptr<std::exception> sp1(new std::bad_exception());

    auto sp2 = dynamic_pointer_cast<std::bad_exception>(sp1);
    auto sp3 = static_pointer_cast<std::exception>(sp2);
    assert(sp3 == sp1);
}

//////////////////////////////////////////

void case3()
{
    shared_ptr<int> sp(new int(10));
    assert(sp.unique());

    shared_ptr<int> sp2 = sp;

    assert(sp == sp2 &&
     sp.use_count() == 2);

    *sp2 = 100;
    assert(*sp == 100);

    sp.reset();
    assert(!sp);

    assert(sp2.unique());
}

//////////////////////////////////////////

class shared
{
private:
    shared_ptr<int> p;
public:
    shared(shared_ptr<int> p_):p(p_){}
    void print()
    {
        std::cout << "count:" << p.use_count()
            << " v=" <<*p << std::endl;
    }
};

void print_func(shared_ptr<int> p)
{
    std::cout << "count:" << p.use_count()
        << " v=" <<*p << std::endl;
}

void case4()
{
    shared_ptr<int> p(new int(100));
    shared s1(p), s2(p);

    s1.print();     // 3次引用
    s2.print();     // 3次引用

    *p = 20;

    // 此函数内部拷贝了一个shared_ptr对象，因此引用计数会加1
    // 但当函数退出时，拷贝自动析构，引用计数又会减1.
    print_func(p);  // 4次引用

    s1.print();     // 3次引用
}

//////////////////////////////////////////

void case5()
{
    auto sp = make_shared<std::string>("make_shared");
    auto spv = make_shared<std::vector<int> >(10, 2);

//    assert(spv->size() == 10);
    std::cout << spv->size() << std::endl;
}

//////////////////////////////////////////

void case6()
{
    typedef std::vector<shared_ptr<int> > vs;
    vs v(10);

    int i = 0;
    for (auto pos = v.begin(); pos != v.end(); ++pos)
    {
        (*pos) = make_shared<int>(++i);
        std::cout << *(*pos) << ", ";
    }
    std::cout << std::endl;

    for (auto& ptr : v)
    {
        ptr = make_shared<int>(++i);
        std::cout << *ptr << ", ";
    }
    std::cout << std::endl;

    shared_ptr<int> p = v[9];
    *p = 100;
    std::cout << *v[9] << std::endl;
}

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
    std::cout << "\n********** Case 5 **********\n";
    case5();
    std::cout << "\n********** Case 6 **********\n";
    case6();
}
