/*
 * io.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: zhizhouli
 */
#include <sstream>
#include "interface.h"
#include "io.h"
namespace grid {
io::io(string io_name, direction d, int w)
{
	name = io_name;
    dir = d;
    width = w;
    connector = NULL;
    inf = NULL;
}

string io::to_verilog_head()
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

string io::to_verilog_body()
{
	return name;
}

string io::get_name()
{
	return name;
}

string io::get_full_name()
{
	if (inf != NULL)
		return name+ '_' + inf->get_name();
	else
		return name;
}

io& io::operator=(class io& c)
{
	this->connector = &c;
	c.connector = this;
	return *this;
}

void io::set_interface(class interface* interface)
{
	inf = interface;
}

class interface* io::get_interface()
{
	return inf;
}

io* io::get_connector()
{
	return connector;
}

bool io::is_input()
{
	return (dir == INPUT? true:false);
}
bool io::is_oupput()
{
	return (dir == OUTPUT? true:false);
}
bool io::is_inout()
{
	return (dir == INOUT? true:false);
}

} /* namespace grid */
