/*
 * interface.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: zhizhouli
 */
#include <vector>
#include <stdlib.h>
#include "io.h"
#include "interface.h"
namespace grid {
interface::interface(string interface_name)
{
	name = interface_name;
	en = true;
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
	pin.set_interface(this);
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

string interface::get_name()
{
	return name;
}

string interface::to_verilog_head()
{
	list<io>::iterator i;
	string buffer = "";
	if (!en)
		return buffer;
	for (i = io_pin_list.begin(); i != io_pin_list.end(); ++i) {
		buffer += (*i).to_verilog_head() + "_" + name + ",\n";
	}
	return buffer;
}

string interface::to_verilog_body()
{
	list<io>::iterator i;
	string buffer = "";
	if (!en)
		return buffer;
	for (i = io_pin_list.begin(); i != io_pin_list.end(); ++i) {
		if (i->get_connector() != NULL && (i->get_interface() != NULL)) {
			if(i->is_input()) {
				buffer += "assign " + (*i).get_full_name() + " = "
						+ i->get_connector()->get_full_name() + ";\n";
			}
			else if(i->is_oupput()) {
				buffer += "assign " + i->get_connector()->get_full_name() + " = "
						+ (*i).get_full_name() + ";\n";
			}
			else if(i->is_inout() && i->get_connector()->is_inout()) {  //bug
				buffer += "assign " + (*i).get_full_name() + " = "
						+ i->get_connector()->get_full_name() + ";\n";
			}
		}
	}
	return buffer;
}

string interface::to_c_body()
{
	list<io>::iterator iterator;
	string buffer = "";
	string pin_name;
	if (!en)
		return buffer;
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

void interface::enable()
{
	en = true;
}

void interface::disable()
{
	en = false;
}

} /* namespace grid */
