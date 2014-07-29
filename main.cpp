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

class direction {
private:
	static const int INPUT  = 1;
	static const int OUTPUT = 2;
	static const int INOUT  = 3;
	int direction;
public:
	string to_string();
	void input();
	void output();
	void inout();
};

string direction::to_string()
{
	switch(direction) {
	case 1:
		return "input";
	case 2:
		return "ouput";
	case 3:
		return "inout";
	default:
		return "undefine";
	}
}
void direction::input()
{
	direction = INPUT;
}
void direction::output()
{
	direction = OUTPUT;
}
void direction::inout()
{
	direction = INOUT;
}

class io
{
private:
	string name;
	direction directory;
	int width;
	class io* connector;
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



