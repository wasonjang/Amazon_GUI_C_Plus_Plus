#include <sstream>
#include <iomanip>
#include "product.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
	Product(category, name, price, qty),
	size_(size),
	brand_(brand)
{

}

Clothing::~Clothing()
{

}

string Clothing::getsize() const
{
	return size_;
}

string Clothing::getbrand() const
{
	return brand_;
}

set<string> Clothing::keywords() const
{
	string keys;
	keys = name_ + ' ' + size_ + ' ' + brand_;
	return parseStringToWords(keys); 
}

string Clothing::displayString() const
{
	double p = price_;
	string pi;
	stringstream convert;
	convert << p;
	int q = qty_;
	string qt;
	stringstream convert2;
	convert2 << q;
	pi = convert.str();
	qt = convert2.str();
	string info;
	info = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + pi + ' ' + qt + " left.";
	return info;
}

void Clothing::dump(std::ostream& os) const
{
	os<<category_<<"\n"<<name_<<"\n"<<price_<<"\n"<<qty_<<"\n"<<size_<<"\n"<< brand_<<endl;
}