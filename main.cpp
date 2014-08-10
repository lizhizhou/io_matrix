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
#include "io.h"
#include "interface.h"
#include "combinationbitmap.h"
using namespace std;
using namespace grid;

int main()
{
	interface pio26a =  interface("PIO26_A");
	pio26a.add_io_pin(io("PIN_0", INOUT));
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
	pio26a.add_io_pin(io("PIN_11", INOUT));
	pio26a.add_io_pin(io("PIN_12", INOUT));
	pio26a.add_io_pin(io("PIN_13", INOUT));
	pio26a.add_io_pin(io("PIN_14", INOUT));
	pio26a.add_io_pin(io("PIN_15", INOUT));
	pio26a.add_io_pin(io("PIN_16", INOUT));
	pio26a.add_io_pin(io("PIN_17", INOUT));
	pio26a.add_io_pin(io("PIN_18", INOUT));
	pio26a.add_io_pin(io("PIN_19", INOUT));
	pio26a.add_io_pin(io("PIN_20", INOUT));
	pio26a.add_io_pin(io("PIN_21", INOUT));
	pio26a.add_io_pin(io("PIN_22", INOUT));
	pio26a.add_io_pin(io("PIN_23", INOUT));
	pio26a.add_io_pin(io("PIN_24", INOUT));
	pio26a.add_io_pin(io("PIN_25", INOUT));

	interface pio26b =  interface(pio26a, "PIO26_B");
	//todo pio26b.add_io_pin(io("PIN", INOUT, 26));

	interface step_motor_0 =  interface("step_motor_0");
	step_motor_0.add_io_pin(io("AX", OUTPUT));
	step_motor_0.add_io_pin(io("AY", OUTPUT));
	step_motor_0.add_io_pin(io("BX", OUTPUT));
	step_motor_0.add_io_pin(io("BY", OUTPUT));
	step_motor_0.add_io_pin(io("AE", OUTPUT));
	step_motor_0.add_io_pin(io("BE", OUTPUT));
	interface step_motor_1 =  interface(step_motor_0, "step_motor_1");
	interface step_motor_2 =  interface(step_motor_0, "step_motor_2");
	interface step_motor_3 =  interface(step_motor_0, "step_motor_3");

	interface brush_motor_0 =  interface("brush_motor_0");
	brush_motor_0.add_io_pin(io("HX", OUTPUT));
	brush_motor_0.add_io_pin(io("HY", OUTPUT));
	interface brush_motor_1 =  interface(brush_motor_0, "brush_motor_1");
	interface brush_motor_2 =  interface(brush_motor_0, "brush_motor_2");
	interface brush_motor_3 =  interface(brush_motor_0, "brush_motor_3");
	interface brush_motor_4 =  interface(brush_motor_0, "brush_motor4");

	step_motor_0("AX") = pio26a("PIN_0");
	step_motor_0("BX") = pio26a("PIN_1");
	step_motor_0("AY") = pio26a("PIN_2");
	step_motor_0("BY") = pio26a("PIN_3");
	step_motor_0("AE") = pio26a("PIN_4");
	step_motor_0("BE") = pio26a("PIN_5");

	step_motor_1("AX") = pio26a("PIN_6");
	step_motor_1("BX") = pio26a("PIN_7");
	step_motor_1("AY") = pio26a("PIN_8");
	step_motor_1("BY") = pio26a("PIN_9");
	step_motor_1("AE") = pio26a("PIN_10");
	step_motor_1("BE") = pio26a("PIN_11");

	step_motor_2("AX") = pio26a("PIN_12");
	step_motor_2("BX") = pio26a("PIN_13");
	step_motor_2("AY") = pio26a("PIN_14");
	step_motor_2("BY") = pio26a("PIN_15");
	step_motor_2("AE") = pio26a("PIN_16");
	step_motor_2("BE") = pio26a("PIN_17");

	step_motor_3("AX") = pio26a("PIN_18");
	step_motor_3("BX") = pio26a("PIN_19");
	step_motor_3("AY") = pio26a("PIN_20");
	step_motor_3("BY") = pio26a("PIN_21");
	step_motor_3("AE") = pio26a("PIN_22");
	step_motor_3("BE") = pio26a("PIN_23");

	brush_motor_0("HX") = pio26b("PIN_0");
	brush_motor_0("HY") = pio26b("PIN_1");
	brush_motor_1("HX") = pio26b("PIN_2");
	brush_motor_1("HY") = pio26b("PIN_3");
	brush_motor_2("HX") = pio26b("PIN_4");
	brush_motor_2("HY") = pio26b("PIN_5");
	brush_motor_3("HX") = pio26b("PIN_6");
	brush_motor_3("HY") = pio26b("PIN_7");

	list<interface> left_side, right_side;
	right_side.push_back(pio26a);
	right_side.push_back(pio26b);

	left_side.push_back(step_motor_0);
	left_side.push_back(step_motor_1);
	left_side.push_back(step_motor_2);
	left_side.push_back(step_motor_3);
	left_side.push_back(brush_motor_0);
	left_side.push_back(brush_motor_1);
	left_side.push_back(brush_motor_2);
	left_side.push_back(brush_motor_3);

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
	string filename = "matrix"+ s.str() + ".v";
	ofstream verilog_file (filename.c_str());
	verilog_file << "module " << "matrix" << "(" << endl;
	for (list<interface>::iterator i = left_side.begin(); i != left_side.end(); ++i) {
		verilog_file << i->to_verilog_head() << endl;
	}

	for (list<interface>::iterator i = right_side.begin(); i != right_side.end(); ++i) {
		verilog_file << i->to_verilog_head() << endl;
	}
	verilog_file << "input clock";
	verilog_file << ");" << endl;

	for (list<interface>::iterator i = left_side.begin(); i != left_side.end(); ++i) {
		verilog_file << i->to_verilog_body();
	}

	verilog_file << "endmodule" << endl;

	filename = "grid.h";
	ofstream h_file (filename.c_str());

//	for (list<interface>::iterator i = left_side.begin(); i != left_side.end(); ++i) {
//		h_file << (*i).to_c_body() << endl;
//	}

	filename = "grid.c";
	ofstream c_file (filename.c_str());

//	for (list<interface>::iterator i = right_side.begin(); i != right_side.end(); ++i) {
//		c_file << (*i).to_c_body() << endl;
//	}

	cout << step_motor_0("AX").get_name();
	cout << step_motor_0[0].get_name();

	cout << step_motor_0("AX").get_connector()->get_name() << endl;
	return 0;
}



