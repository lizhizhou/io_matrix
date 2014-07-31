/*
 * main.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: zhizhouli
 */
#include <iostream>
#include <string>
#include <list>
#include <stdlib.h>
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
	direction dir;
	int width;
	class io* connector;
public:
	string to_verilog_name();
	string to_c_name();
	int hash();
	io(string io_name, direction d, int w);
};

io::io(string io_name, direction d, int w)
{
	name = io_name;
    dir = d;
    width = w;
}

string io::to_verilog_name()
{
	string buffer = "";
	switch (dir)
	{
		case INPUT:
		buffer += "input";
		break;
		case OUTPUT:
		buffer += "output";
		break;
		case INOUT:
		buffer += "inout";
		break;
		default:
		break;
	}
	if (width > 1)
		buffer = buffer + "[0:"+  + "]";
	buffer += name;
	return buffer;
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
	io_pin_list.push_back(pin);
}

string interface::to_verilog_name()
{
	list<io>::iterator iterator;
	string buffer = "";
	for (iterator = io_pin_list.begin(); iterator != io_pin_list.end(); ++iterator) {
		buffer += (*iterator).to_verilog_name() + "_" +name + "\n";
	}
	return buffer;
}

string interface::to_c_name()
{
	return name;
}

int main()
{
	interface pio26a =  interface("PIO26A");
	pio26a.add_io_pin(io("PIN_1", INOUT, 1));
	pio26a.add_io_pin(io("PIN_2", INOUT, 1));
	pio26a.add_io_pin(io("PIN_3", INOUT, 1));
	pio26a.add_io_pin(io("PIN_4", INOUT, 1));
	pio26a.add_io_pin(io("PIN_5", INOUT, 1));
	pio26a.add_io_pin(io("PIN_6", INOUT, 1));
	interface pio26b =  interface("PIO26B");
	pio26b.add_io_pin(io("PIN", INOUT, 26));
	list<interface> left_side, right_side;
	right_side.push_back(pio26a);
	right_side.push_back(pio26b);
	cout << pio26a.to_verilog_name() << endl;
	cout << pio26b.to_verilog_name() << endl;
	return 0;
}



