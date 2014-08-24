/*
 * combinationbitmap.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: zhizhouli
 */

#include "combinationbitmap.h"
namespace grid {

void combination_bitmap::add_one_bitmap(vector< vector<bool> >* bitmap_list, vector<bool>* bitmap, size_t i, size_t n)
{
	if(i == n) {
		bitmap_list->push_back(*bitmap);
		return;
	}
	i++;
	height++;
	bitmap->push_back(true);
	add_one_bitmap(bitmap_list, bitmap, i, n);
	bitmap->pop_back();
	bitmap->push_back(false);
	add_one_bitmap(bitmap_list, bitmap, i, n);
	bitmap->pop_back();
}

combination_bitmap::combination_bitmap(size_t n)
{
	width = n;
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


double combination_bitmap::to_value()
{
	static double t = 0;
	t++;
	return t;
}


} /* namespace grid */
