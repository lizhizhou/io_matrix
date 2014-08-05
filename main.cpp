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
#include <vector>
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
	io& operator=(class io& c);
	io* get_connector();
};

io::io(string io_name, direction d, int w)
{
	name = io_name;
    dir = d;
    width = w;
    connector = NULL;
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

io& io::operator=(class io& c)
{
	this->connector = &c;
	c.connector = this;
	return *this;
}

io* io::get_connector()
{
	return connector;
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
	io& operator()(string io_name);
	io& operator[](int index);
	size_t io_number();
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

io& interface::operator()(string io_name)
{
	list<io>::iterator i;
	for (i = io_pin_list.begin(); i != io_pin_list.end(); ++i) {
		if ((*i).get_name() == io_name)
			return (*i);
	}
	return *((io*)NULL);
}

io& interface::operator[](int index)
{
	list<io>::iterator i;
	int j = 0;
	if (index > (int)io_pin_list.size())
		return *((io*)NULL);
	for (i = io_pin_list.begin(); i != io_pin_list.end(); ++i, ++j) {
		if (j == index)
			return (*i);
	}
	return *((io*)NULL);
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

size_t interface::io_number()
{
	return io_pin_list.size();
}

class combination_bitmap
{
private:
	vector<bool> bitmap;
	vector< vector<bool> > bitmap_list;
	void add_one_bitmap(vector< vector<bool> >* bitmap_list, vector<bool>* bitmap, size_t i, size_t n);
public:
	combination_bitmap(size_t n);
	vector< vector<bool> > get_bitmap_list();
	vector<bool> operator[](int i);
	double to_value();
};

void combination_bitmap::add_one_bitmap(vector< vector<bool> >* bitmap_list, vector<bool>* bitmap, size_t i, size_t n)
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

vector< vector<bool> > combination_bitmap::get_bitmap_list()
{
	return bitmap_list;
}

vector<bool> combination_bitmap::operator[](int i)
{
	return bitmap_list[i];
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
	pio26a.add_io_pin(io("PIN_7", INOUT));
	pio26a.add_io_pin(io("PIN_8", INOUT));
	pio26a.add_io_pin(io("PIN_9", INOUT));
	pio26a.add_io_pin(io("PIN_10", INOUT));

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
	brush_motor_0.add_io_pin(io("HX", OUTPUT));
	brush_motor_0.add_io_pin(io("HY", OUTPUT));
	interface brush_motor_1 =  interface(brush_motor_0, "brush_motor_1");

	list<interface>::iterator i;
	list<interface> left_side, right_side;
	right_side.push_back(pio26a);
	right_side.push_back(pio26b);

	left_side.push_back(step_motor_0);
	left_side.push_back(step_motor_1);
	left_side.push_back(brush_motor_0);
	left_side.push_back(brush_motor_1);

	vector< vector<bool> > bitmap_list = combination_bitmap(10).get_bitmap_list();
	for (vector< vector<bool> >::iterator j = bitmap_list.begin(); j != bitmap_list.end(); j++)
	{
		vector<bool> bitmap = *j;
		for (vector<bool>::iterator i = bitmap.begin(); i != bitmap.end(); i++)
		{
			cout << (int)(*i);
		}
		cout << endl;
	}
	cout << bitmap_list[1][2] << endl;

	stringstream s;
	int hash = 100;
	s << hash;
	string filename = "maxtrix"+ s.str() + ".v";
	ofstream verilog_file (filename.c_str());
	verilog_file << "module " << "maxtrix" << "(" << endl;
	for (i = left_side.begin(); i != left_side.end(); ++i) {
		verilog_file << (*i).to_verilog_name() << endl;
	}

	for (i = right_side.begin(); i != right_side.end(); ++i) {
		verilog_file << (*i).to_verilog_name() << endl;
	}
	verilog_file << "input clock";
	verilog_file << ");" << endl;

	list<io>::iterator j;
//	for (i = left_side.begin(); i != left_side.end(); ++i) {
//		for(j = i->)
//	}

	verilog_file << "endmodule" << endl;

	filename = "grid.h";
	ofstream h_file (filename.c_str());

	for (i = left_side.begin(); i != left_side.end(); ++i) {
		h_file << (*i).to_c_name() << endl;
	}

	filename = "grid.c";
	ofstream c_file (filename.c_str());

	for (i = right_side.begin(); i != right_side.end(); ++i) {
		c_file << (*i).to_c_name() << endl;
	}

	cout << step_motor_0("AX").get_name();
	cout << step_motor_0[0].get_name();

	step_motor_0("AX") = pio26a("PIN_0");
	step_motor_0("BX") = pio26a("PIN_1");
	step_motor_0[2] = pio26a[2];

	cout << step_motor_0("AX").get_connector()->get_name() << endl;
	return 0;
}



