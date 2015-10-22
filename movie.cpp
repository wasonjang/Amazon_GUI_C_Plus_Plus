#include <sstream>
#include <iomanip>
#include "product.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):
	Product(category, name, price, qty),
	genre_(genre),
	rating_(rating)
{

}

Movie::~Movie()
{

}

string Movie::getrating() const
{
	return rating_;
}

string Movie::getgenre() const
{
	return genre_;
}

set<string> Movie::keywords() const
{
	string keys;
	keys = name_ + ' ' + rating_;
	set<string>T;
	T = parseStringToWords(keys);
	string g = genre_;
	g = convToLower(g);
	T.insert(g);
	return T; 
}

string Movie::displayString() const
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
	info = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + pi + ' ' + qt + " left.";
	return info;
}

void Movie::dump(std::ostream& os) const
{
	os<<category_<<"\n"<<name_<<"\n"<<price_<<"\n"<<qty_<<"\n"<<genre_<<"\n"<< rating_<<endl;
}