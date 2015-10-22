#include "msort.h"
#include <cstdlib>
#include "product.h"
#include <vector>
using namespace std;

struct Prodcomp
{
	bool operator()(Product* a, Product* b)
	{
		return(a->getName() < b->getName());
	}
};
struct Reviewcomp
{
	bool operator()(Review* a, Review* b)
	{
		return(a->date > b->date);
	}
};
struct Starcomp
{
	DDataStore* dds;
	bool operator()(Product* a, Product* b)
	{
		string aname; 
		aname = a->getName();
		string bname; 
		bname = b->getName();
		return(dds->averagereview(aname) > dds->averagereview(bname));
	}
};
void alphabetsort(vector<Product*> &p)
{
	Prodcomp a;
	mergeSort(p,a);
}
void reviewsort(vector<Review*> &r)
{
	Reviewcomp b;
	mergeSort(r,b);
}

void starsort(vector<Product*> &s, DDataStore* &ds)
{
	Starcomp t;
	t.dds = ds;
	mergeSort(s,t);
}
