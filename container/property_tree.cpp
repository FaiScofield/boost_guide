// Copyright (c) 2015
// Author: Chrono Law
#include <iostream>
using namespace std;

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
using namespace boost::property_tree;

//////////////////////////////////////////
void case1()
{
    ptree pt;
    read_xml("conf.xml", pt);

    pt.get<string>("conf.theme");
    pt.get<int>("conf.clock_style");
    pt.get("conf.no_prop", 100); // 读取no_prop节点，若不存在则返回默认值整数100

    cout << pt.get<string>("conf.theme") << endl;
    cout << pt.get<int>("conf.clock_style") << endl;
    cout << pt.get<long>("conf.gui")<< endl;
    cout << pt.get("conf.no_prop", 100)<< endl;

    auto child = pt.get_child("conf.urls");
    for (auto& x : child)
        cout <<  x.second.get_value<string>() << ",";
    cout << endl;

    for(auto& x : pt.get_child("conf.urls"))
        cout <<  x.second.data() << ",";

    cout << endl;

}

//////////////////////////////////////////
void case2()
{
    ptree pt;
    read_xml("conf.xml", pt);

    pt.put("conf.theme", "Matrix Reloaded");
    pt.put("conf.clock_style", 12);
    pt.put("conf.gui", 0);
//    pt.put("conf.urls.url", "http://www.url4.org"); // put 修改
    pt.add("conf.urls.url", "http://www.url4.org");   // add 添加

    write_xml(cout , pt);
}

//////////////////////////////////////////
void case3()
{
    ptree pt;
    read_xml("conf.xml", pt);
    cout << pt.get<string>("conf.<xmlcomment>") << endl;
    cout << pt.get<string>("conf.clock_style.<xmlattr>.name") << endl;
    cout << pt.get<long>("conf.theme.<xmlattr>.id")<< endl;
    cout << pt.get<string>("conf.urls.<xmlcomment>")<< endl;

}
//////////////////////////////////////////
#include <boost/property_tree/json_parser.hpp>
void case4()
{
    ptree pt;
    read_json("conf.json", pt);

    cout << pt.get<string>("conf.theme") << endl;
    cout << pt.get<int>("conf.clock_style") << endl;
    cout << pt.get<long>("conf.gui")<< endl;
    cout << pt.get("conf.no_prop", 100)<< endl;

    for (auto x : pt.get_child("conf.urls"))
    {   cout <<  x.second.data() << ",";    } // .second是自身的值，

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
