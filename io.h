/*
 * io.h
 *
 *  Created on: Aug 9, 2014
 *      Author: zhizhouli
 */

#ifndef IO_H_
#define IO_H_
#include <string>
using namespace std;
namespace grid {
enum direction {
	INPUT  = 1,
	OUTPUT = 2,
	INOUT  = 3
};

class io
{
private:
	class interface* inf;
	string name;
	direction dir;
	int width;
	class io* connector;
public:
	string to_verilog_head();
	string to_verilog_body();
	string get_name();
	string get_full_name();
	int hash();
	io(string io_name, direction d, int w = 1);
	io& operator=(class io& c);
	void set_interface(class interface* interface);
	class interface* get_interface();
	io* get_connector();
};

} /* namespace grid */
#endif /* IO_H_ */
