/*
 * interface.h
 *
 *  Created on: Aug 9, 2014
 *      Author: zhizhouli
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <list>
#include <string>
#include "io.h"
using namespace std;
namespace grid {

class interface
{
private:
	string name;
	list<io> io_pin_list;
	bool en;
public:
	string to_verilog_head();
	string to_verilog_body();
	string to_c_body();
	string get_name();
	interface(string interface_name);
	interface(interface template_interface, string interface_name);
	void add_io_pin(io pin);
	io& operator()(string io_name);
	io& operator[](int index);
	size_t io_number();
	void enable();
	void disable();
	int hash();
};

} /* namespace grid */
#endif /* INTERFACE_H_ */
