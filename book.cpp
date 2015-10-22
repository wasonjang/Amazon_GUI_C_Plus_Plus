#include <sstream>
#include <iomanip>
#include "product.h"
#include "util.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) :
	Product(category, name, price, qty),
	isbn_(isbn),
	author_(author)
{

}

Book::~Book()
{

}

string Book::getisbn() const
{
	return isbn_;
}

string Book::getauthor() const
{
	return author_;
}

set<string> Book::keywords() const
{
	string keys;
	keys = name_ + ' ' + author_;
	set<string>T;
	T = parseStringToWords(keys); 
	T.insert(isbn_);
	return T;
}

string Book::displayString() const
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
	info = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + pi + ' ' + qt + " left.";
	return info;
}

void Book::dump(std::ostream& os) const
{
	os<<category_<<"\n"<<name_<<"\n"<<price_<<"\n"<<qty_<<"\n"<<isbn_<<"\n"<< author_<<endl;
}