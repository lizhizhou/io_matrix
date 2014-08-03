/*
 * main.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: zhizhouli
 */
#include <iostream>
#include <fstream>
#include <sstream>
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
	string get_name();
	int hash();
	io(string io_name, direction d, int w = 1);
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
	stringstream s;
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
	if (width > 1) {
		s << (width - 1);
		buffer = buffer + " " + "[0:"+ s.str() + "]";
	}
	buffer += " " + name;
	return buffer;
}

string io::get_name()
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
	interface(interface template_interface, string interface_name);
	void add_io_pin(io pin);
	io* operator()(string io_name);
	io* operator[](int index);
	int hash();
};

interface::interface(string interface_name)
{
	name = interface_name;
}

interface::interface(interface template_interface, string interface_name)
{
	list<io>::iterator iterator;
	for (iterator = template_interface.io_pin_list.begin(); iterator != template_interface.io_pin_list.end(); ++iterator) {
		add_io_pin(*iterator);
	}
	name = interface_name;
}

void interface::add_io_pin(io pin)
{
	io_pin_list.push_back(pin);
}

io* interface::operator()(string io_name)
{
	list<io>::iterator i;
	for (i = io_pin_list.begin(); i != io_pin_list.end(); ++i) {
		if ((*i).get_name() == io_name)
			return &(*i);
	}
	return NULL;
}

io* interface::operator[](int index)
{
	list<io>::iterator i;
	int j = 0;
	if (index > (int)io_pin_list.size())
		return NULL;
	for (i = io_pin_list.begin(); i != io_pin_list.end(); ++i, ++j) {
		if (j == index)
			return &(*i);
	}
	return NULL;
}

string interface::to_verilog_name()
{
	list<io>::iterator i;
	string buffer = "";
	for (i = io_pin_list.begin(); i != io_pin_list.end(); ++i) {
		buffer += (*i).to_verilog_name() + "_" + name + ",\n";
	}
	return buffer;
}

string interface::to_c_name()
{
	list<io>::iterator iterator;
	string buffer = "";
	string pin_name;
	buffer = buffer + "int" + " enable_" + name + "(void)\n";
	buffer = buffer + "{\n";
	for (iterator = io_pin_list.begin(); iterator != io_pin_list.end(); ++iterator) {
		pin_name = (*iterator).get_name() + "_" + name;
		buffer = buffer + "if ("+ pin_name +" == 0) {\n" + pin_name + " = 1;\n" + "} else {\n" + "return 0;\n"+"}\n";
	}
	buffer = buffer + "return 1;\n" + "}\n";
	buffer = buffer + "int" + " disable_" + name + "(void)\n";
	buffer = buffer + "{\n";
	for (iterator = io_pin_list.begin(); iterator != io_pin_list.end(); ++iterator) {
		pin_name = (*iterator).get_name() + "_" + name;
		buffer = buffer + "if ("+ pin_name +" == 1) {\n" + pin_name + " = 0;\n" + "} else {\n" + "return 0;\n"+"}\n";
	}
	buffer = buffer + "return 1;\n" + "}\n";
	return buffer;
}

//todo: change to array
class combination_bitmap
{
private:
	list<bool> bitmap;
	list< list<bool> > bitmap_list;
	void add_one_bitmap(list< list<bool> >* bitmap_list, list<bool>* bitmap, size_t i, size_t n);
public:
	combination_bitmap(size_t n);
	list< list<bool> > get_bitmap_list();
	double to_value();
};

void combination_bitmap::add_one_bitmap(list< list<bool> >* bitmap_list, list<bool>* bitmap, size_t i, size_t n)
{
	if(i == n) {
		bitmap_list->push_back(*bitmap);
		return;
	}
	i++;
	bitmap->push_back(true);
	add_one_bitmap(bitmap_list, bitmap, i, n);
	bitmap->pop_back();
	bitmap->push_back(false);
	add_one_bitmap(bitmap_list, bitmap, i, n);
	bitmap->pop_back();
}

combination_bitmap::combination_bitmap(size_t n)
{
	add_one_bitmap(&bitmap_list, &bitmap, 1, n);
}

list< list<bool> > combination_bitmap::get_bitmap_list()
{
	return bitmap_list;
}

int main()
{
	interface pio26a =  interface("PIO26_A");
	pio26a.add_io_pin(io("PIN_1", INOUT));
	pio26a.add_io_pin(io("PIN_2", INOUT));
	pio26a.add_io_pin(io("PIN_3", INOUT));
	pio26a.add_io_pin(io("PIN_4", INOUT));
	pio26a.add_io_pin(io("PIN_5", INOUT));
	pio26a.add_io_pin(io("PIN_6", INOUT));

	interface pio26b =  interface("PIO26_B");
	pio26b.add_io_pin(io("PIN", INOUT, 26));

	interface step_motor_0 =  interface("step_motor_0");
	step_motor_0.add_io_pin(io("AX", OUTPUT));
	step_motor_0.add_io_pin(io("AY", OUTPUT));
	step_motor_0.add_io_pin(io("BX", OUTPUT));
	step_motor_0.add_io_pin(io("BY", OUTPUT));
	step_motor_0.add_io_pin(io("AE", OUTPUT));
	step_motor_0.add_io_pin(io("BE", OUTPUT));
	interface step_motor_1 =  interface(step_motor_0, "step_motor_1");
	interface brush_motor_0 =  interface("brush_motor_0");

	list<interface>::iterator iterator;
	list<interface> left_side, right_side;
	right_side.push_back(pio26a);
	right_side.push_back(pio26b);

	left_side.push_back(step_motor_0);
	left_side.push_back(step_motor_1);
	left_side.push_back(brush_motor_0);

	list< list<bool> > bitmap_list = combination_bitmap(6).get_bitmap_list();
	for (list< list<bool> >::iterator j = bitmap_list.begin(); j != bitmap_list.end(); j++)
	{
		list<bool> bitmap = *j;
		for (list<bool>::iterator i = bitmap.begin(); i != bitmap.end(); i++)
		{
			cout << (int)(*i);
		}
		cout << endl;
	}

	stringstream s;
	int hash = 100;
	s << hash;
	string filename = "maxtrix"+ s.str() + ".v";
	ofstream verilog_file (filename.c_str());
	verilog_file << "module " << "maxtrix" << "(" << endl;
	for (iterator = left_side.begin(); iterator != left_side.end(); ++iterator) {
		verilog_file << (*iterator).to_verilog_name() << endl;
	}

	for (iterator = right_side.begin(); iterator != right_side.end(); ++iterator) {
		verilog_file << (*iterator).to_verilog_name() << endl;
	}
	verilog_file << "input clock";
	verilog_file << ");" << endl;
	verilog_file << "endmodule" << endl;

	filename = "grid.h";
	ofstream h_file (filename.c_str());

	for (iterator = left_side.begin(); iterator != left_side.end(); ++iterator) {
		h_file << (*iterator).to_c_name() << endl;
	}

	filename = "grid.c";
	ofstream c_file (filename.c_str());

	for (iterator = right_side.begin(); iterator != right_side.end(); ++iterator) {
		c_file << (*iterator).to_c_name() << endl;
	}

	cout << step_motor_0("AX")->get_name();
	cout << step_motor_0[0]->get_name();


	return 0;
}



