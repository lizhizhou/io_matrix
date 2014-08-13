/*
 * combinationbitmap.h
 *
 *  Created on: Aug 9, 2014
 *      Author: zhizhouli
 */

#ifndef COMBINATIONBITMAP_H_
#define COMBINATIONBITMAP_H_
#include <vector>
using namespace std;
namespace grid {

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

} /* namespace grid */
#endif /* COMBINATIONBITMAP_H_ */
