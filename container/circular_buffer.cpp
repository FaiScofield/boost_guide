// Copyright (c) 2015
// Author: Chrono Law
#include <iostream>
using namespace std;

#include <boost/assign.hpp>
#include <boost/circular_buffer.hpp>
using namespace boost;

template<typename T>
void print(T& cb)
{
    for (auto& x: cb)
    {   cout << x << ", ";   }
    cout << endl;
}

//////////////////////////////////////////
void case1()
{
    cout << "\n********** Case 1 **********\n";
    circular_buffer<int> cb(5);
    assert(cb.empty());

    cb.push_back(1);
    cb.push_front(2);
    assert(cb.front() == 2);
    cb.insert(cb.begin(), 3);


    print(cb);

    cb.pop_front();
    assert(cb.size() == 2);
    cb.push_back(); // 在后端添加0末元素
    assert(cb[0] = 2);

    print(cb);

    //using namespace boost::assign;
    circular_buffer<int> cb1 = (assign::list_of(1),2,3);
    circular_buffer<int> cb2 = (assign::list_of(3),4,5);
    circular_buffer<int> cb3 = cb1;

    assert(cb1 < cb2);
    assert(cb1 == cb3);

}

//////////////////////////////////////////
void case2()
{
    cout << "\n********** Case 2 **********\n";
    circular_buffer<int> cb = (assign::list_of(1),2,3); // 容器大小为3
    print(cb);

    cb.push_back(4);
    print(cb);

    cb.push_back(5);
    print(cb);

    cb.pop_front();
    print(cb);

}

//////////////////////////////////////////
void case3()
{
    cout << "\n********** Case 3 **********\n";
    circular_buffer<int> cb =(assign::list_of(1),2,3,4,5);

    assert(cb.full());
    print(cb);

    int *p = cb.linearize(); // 将缓冲区线性化成一个连续的普通数组
    assert(p[0]== 1 && p[3] == 4);
    assert(cb.is_linearized());

    cb.rotate(cb.begin()+ 2); // 从指定位置旋转整个缓冲区
    print(cb);

}

//////////////////////////////////////////
void case4()
{
    cout << "\n********** Case 4 **********\n";
    using namespace boost::assign;

    circular_buffer_space_optimized<int> cb(10); // 在需要时才分配空间，元素减少时会自动释放内存
    push_back(cb)(1),2,3,4;

    assert(cb.size() == 4);
    assert(cb.capacity() == 10);

    cb.resize(30, 10);
    assert(cb.size() == cb.capacity());

    print(cb);

}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
}
