/*
 * combinationbitmap_test.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: zhizhouli
 */

#include "combinationbitmap.h"
#include <iostream>
namespace grid {
void combinationbitmap_unit_test()
{
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
}
} /* namespace grid */
