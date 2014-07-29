/*
 * main.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: zhizhouli
 */
#include <iostream>
#include <string>
#include <list>
using namespace std;

enum io_direction {
	INPUT,
	OUTPUT,
	INOUT
};

class io
{
private:
	string name;
	io_direction directory;
	int width;
public:
	string to_verilog_name();
	string to_c_name();
	int hash();
};

string io::to_verilog_name()
{
	return name;
}

string io::to_c_name()
{
	return name;
}

class interface
{
private:
	string name;
	list<io> io_pin_list;
public:
	string to_verilog_name();
	string to_c_name();
	int hash();
};

string interface::to_verilog_name()
{
	return name;
}

string interface::to_c_name()
{
	return name;
}

int main()
{
	cout << "lizhizhou";
	return 0;
}



