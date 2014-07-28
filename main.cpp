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

enum io_direction {
	INPUT,
	OUTPUT,
	INOUT
};

class io
{
	string name;
	io_direction directory;
};

class device
{
	string name;
	list<io> io_pin_list;
};



int main()
{
	cout << "lizhizhou";
	return 0;
}



