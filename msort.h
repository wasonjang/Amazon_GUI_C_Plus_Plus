#ifndef msort_H
#define msort_H
#include <vector>
#include <cmath>
#include "product.h"
#include "review.h"
#include "datastore.h"

void alphabetsort(std::vector<Product*> &p);
void reviewsort(std::vector<Review*> &r);
void starsort(std::vector<Product*> &p, DDataStore* &ds);
template <class T, class Comparator>
void mergehelper(std::vector<T>left, std::vector<T>right, std::vector<T>& myArray, Comparator comp )
{
	int mcount = 0;
	int lcount = 0;
	int rcount = 0;
	while(lcount < left.size() && rcount <right.size())
	{
		if(comp(left[lcount],right[rcount]) == 1)
		{
			myArray[mcount] = left[lcount];
			lcount++;;
		}
		else
		{
			myArray[mcount] = right[rcount];
			rcount++;;
		}
		mcount++;
	}
	if(left.size()>0)
	{
		for(unsigned int i=lcount; i<left.size(); i++)
		{
			myArray[mcount] = left[i];
			mcount++;
		}
	}
	else if(right.size()>0)
	{
		for(unsigned int i=rcount; i<right.size(); i++)
		{
			myArray[mcount] = right[i];
			mcount++;
		}
	}
}

template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, Comparator comp)
{
	std::vector<T>left;
	std::vector<T>right;
	int middle = floor(myArray.size()/2);
	if(myArray.size() <= 1)
	{
		return;
	}
	else
	{
		for(int i = 0; i<middle; i++)
		{
			left.push_back(myArray[i]);
		}
		for(int j = middle; j<myArray.size(); j++)
		{
			right.push_back(myArray[j]);
		}
		mergeSort(left, comp);
		mergeSort(right,comp);
		mergehelper(left,right,myArray,comp);

	}

}









#endif