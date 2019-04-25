// Copyright (c) 2015
// Author: Chrono Law
#include <iostream>
using namespace std;

#include <boost/format.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    cout << format("%s:%d+%d=%d\n") %"sum" % 1 % 2 % (1+2);

    format fmt("(%1% + %2%) * %2% = %3%\n");    //注意这里的用法格式，%N%是占位符
    fmt % 2 % 5 ;
    fmt % ((2+5)*5);
    cout << fmt.str();
}

//////////////////////////////////////////

/* %-8.3f, 左对齐浮点数，总宽度8，小数位数3
 * % 10s, 10位字符串，不足位用空格填充
 * %05X, 宽对为5的大写16进制数，不足用0填充
 */
void case2()
{
    format fmt("%05d\n%-8.3f\n% 10s\n%05X\n");
    cout << fmt %62 % 2.236 % "123456789" % 48;

    format fmt2("%|05d|\n%|-8.3f|\n%| 10s|\n%|05X|\n");
    cout << fmt2 %62 % 2.236 % "123456789" % 48;

    const format fmt3("%10d %020.8f %010X %10.5e\n");
    cout << format(fmt3) %62 % 2.236 % 255 % 0.618; // 拷贝对象格式化，速度比直接使用快
}

//////////////////////////////////////////
#include <iomanip>
using namespace boost;
using boost::io::group;

void case3()
{
    format fmt("%1% %2% %3% %2% %1% \n");
    cout << fmt %1 % 2 % 3;

    fmt.bind_arg(2, 10);    // 固定第2个参数值
    cout << fmt %1 %3;

    fmt.clear();            // clear()不取消bind_arg()的固定参数

    cout << fmt % group(showbase, oct, 111) % 333;  // 指定输入/输出流中第一个参数显示为八进制，第三个参数为333

    fmt.clear_binds();      // clear_binds()可以取消bind_arg()的固定参数

    // 设置第一个格式化项，16进制，宽度为8，右对齐，不足位用*填充
    fmt.modify_item(1, group(hex, right, showbase, setw(8), setfill('*')));
    cout << fmt % 49 % 20 % 100;
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
}

