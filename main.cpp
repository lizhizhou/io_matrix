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

enum direction {
	INPUT  = 1,
	OUTPUT = 2,
	INOUT  = 3
};

class io
{
private:
	string name;
	direction d;
	int width;
	class io* connector;
public:
	string to_verilog_name();
	string to_c_name();
	int hash();
	io(string io_name, direction dir);
};

io::io(string io_name, direction dir)
{
	name = io_name;
    d = dir;
}

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
	interface(string interface_name);
	void add_io_pin(io pin);
	int hash();
};

interface::interface(string interface_name)
{
	name = interface_name;
}

void interface::add_io_pin(io pin)
{
	io_pin_list.push_front(pin);
}

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
	interface pio26a =  interface("PIO26A");
	pio26a.add_io_pin(io("PIN_1", INOUT));
	pio26a.add_io_pin(io("PIN_2", INOUT));
	pio26a.add_io_pin(io("PIN_3", INOUT));
	pio26a.add_io_pin(io("PIN_4", INOUT));
	pio26a.add_io_pin(io("PIN_5", INOUT));
	pio26a.add_io_pin(io("PIN_6", INOUT));
	interface pio26b =  interface("PIO26B");
	list<interface> left_side, right_side;
	right_side.push_front(pio26a);
	right_side.push_front(pio26b);
	return 0;
}



