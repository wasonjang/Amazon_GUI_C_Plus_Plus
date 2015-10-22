#include <sstream>
#include <iomanip>
#include "datastore.h"
#include <cmath>

using namespace std;

DDataStore::~DDataStore()
{
	for(unsigned int i = 0; i<users.size(); i++)
	{
		delete users[i];
	}
	for(unsigned int j = 0; j<products.size(); j++)
	{
		delete products[j];
	}
	for(unsigned int k = 0; k<reviews.size(); k++)
	{
		delete reviews[k];
	}
}

void DDataStore::addReview(Review* r)
{
	reviews.push_back(r);
	string name = r->prodName;
	map<string, vector<Review*> >::iterator it = texts.find(name);
	if(it != texts.end())
	{
		it->second.push_back(r);
	}
	else
	{
		vector<Review*>brandnew;
		brandnew.push_back(r);
		texts.insert( pair<string, vector<Review*> > (name, brandnew));
	}
	string whorated = r->rater;
	Product* temp;
	for(vector<Product*>::iterator lt = products.begin(); lt != products.end(); ++lt)
	{
		if((*lt)->getName() == name)
		{
			temp = (*lt);
		}
	}
	map<string, set<Product*> >::iterator tt = reviewsheet.find(whorated);
	tt->second.insert(temp);
	map<string, map<string, Review*> >::iterator at = peoplereview.find(whorated);
	at->second.insert(pair<string, Review*> (name, r));
}
void DDataStore::basicCalc()
{
	for(vector<User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		for(map<string, set<Product*> >::iterator lt = reviewsheet.begin(); lt != reviewsheet.end(); ++lt)
		{
			if((*it)->getName() != lt->first)
			{
				map<string, set<Product*> >::iterator tt = reviewsheet.find((*it)->getName());
				set<Product*>A;
				set<Product*>B;
				A = tt->second;
				B = lt->second;
				set<Product*>final;
				final = setIntersection(A,B);
				User* two = findthatperson(lt->first);
				if(final.empty())
				{
					double number = 1.0;
					(*it)->basic(two, number);
				}
				else
				{
					double number = 0.0;
					double size = final.size();
					for(set<Product*>::iterator z = final.begin(); z != final.end(); ++z)
					{
						map<string, map<string, Review*> >::iterator at = peoplereview.find((*it)->getName());
						map<string, map<string, Review*> >::iterator st = peoplereview.find(lt->first);
						map<string, Review*>areview = at->second;
						map<string, Review*>breview = st->second;
						string name; 
						name = (*z)->getName();
						map<string, Review*>::iterator qt=areview.find(name);
						map<string, Review*>::iterator wt=breview.find(name);
						double arating;
						double brating;
						arating = qt->second->rating;
						brating = wt->second->rating;
						double equal;
						equal = abs(arating-brating);
						equal = equal/4;
						number += equal;
					}
					double average;
					average = number/size;
					(*it)->basic(two, average);
				}
			}
		}
	}
}
std::map<User*, std::map<User*, double> > DDataStore::makeGraph()
{
	for(vector<User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		graph.insert(pair<User*, std::map<User*, double> >((*it), (*it)->getBasic()));
	}
	return graph;
}
std::map<User*,int> DDataStore::whoratedthis(std::string item, std::string curr)
{
	map<User*, int>fresult;
	map<string, vector<Review*> >::iterator it = texts.find(item);
	vector<Review*>list;
	list = it->second;
	for(unsigned int i = 0; i<list.size(); i++)
	{
		string who;
		int stars;
		who = list[i]->rater;
		stars = list[i]->rating;
		if(who != curr)
		{
			User* whoagain;
			whoagain = findthatperson(who);
			fresult.insert(pair<User*, int>(whoagain, stars));
		}
	}
	return fresult;

}
std::set<Product*> DDataStore::notRated(std::string person)
{
	set<Product*>rated;
	set<Product*>unrated;
	map<string, set<Product*> >::iterator it = reviewsheet.find(person);
	rated = it->second;
	for(unsigned int i = 0; i<products.size(); i++)
	{
		set<Product*>::iterator lt = rated.find(products[i]);
		if(lt == rated.end())
		{
			unrated.insert(products[i]);
		}
	}
	return unrated;
}
void DDataStore::addProduct(Product* p)
{
	products.push_back(p);
	set<string>T = p->keywords();
	for(set<string>::iterator at = T.begin(); at != T.end(); ++ at)
	{

		pair<string, set<Product*> >value;
		value = keymaptree.find((*at));
		if(value.first.size() == 0)
		{
			set<Product*>brandnew;
			brandnew.insert(p);
			pair<string,set<Product*> >newstuff((*at), brandnew);
			keymaptree.insert(newstuff);
		}
		else
		{
			value.second.insert(p);
			keymaptree.insert(value);	
		}
	}
}
bool DDataStore::doyouexist(string u)
{
	for(vector<User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if((*it)->getName() == u)
		{
			return true;
		}
	}
	return false;
}
User* DDataStore::findthatperson(string u)
{
	User* temp;
	for(vector<User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if((*it)->getName() == u)
		{
			temp = *it;
		}
	}
	return temp;

}
void DDataStore::addUser(User* u)
{
	users.push_back(u);
	vector<Product*>brandnew;
	carts.insert( pair<string,vector<Product*> >(u->getName(), brandnew));
	set<Product*>stuff;
	reviewsheet.insert( pair<string,set<Product*> >(u->getName(), stuff));
	map<string, Review*>thing;
	peoplereview.insert( pair<string, map<string, Review*> >(u->getName(), thing));
}

void DDataStore::dump(std::ostream& ofile)
{
	ofile<<"<products>"<<endl;
	for(vector<Product*>::iterator it = products.begin(); it != products.end(); ++it)
	{
		(*it)->dump(ofile);
	}
	ofile<<"</products>"<<endl;
	ofile<<"<users>"<<endl;
	for(vector<User*>::iterator lt = users.begin(); lt != users.end(); ++lt)
	{
		(*lt)->dump(ofile);
	}
	ofile<<"</users>"<<endl;
	ofile<<"<reviews>"<<endl;
	for(vector<Review*>::iterator jt = reviews.begin(); jt != reviews.end(); ++jt)
	{
		ofile<<(*jt)->prodName<<endl;
		ofile<<(*jt)->rating<<" "<<(*jt)->rater<<" "<<(*jt)->date<<" "<<(*jt)->reviewText<<endl;
	}
	ofile<<"</reviews>"<<endl;
}
double DDataStore::averagereview(std::string productname)
{
	double staraverage = 0.0;
	map<string, vector<Review*> >::iterator it = texts.find(productname);
	if(it == texts.end())
	{
		staraverage = 0;
	}
	else
	{
		vector<Review*> s;
		s = it->second;
		for(unsigned int i=0; i<s.size(); i++)
		{
			staraverage += s[i]->rating;
		}
		staraverage = staraverage/s.size();
	}
	return staraverage;
}
std::vector<Review*> DDataStore::getReview(std::string productname)
{
	vector<Review*>found;
	map<string, vector<Review*> >::iterator it = texts.find(productname);
	found = it->second;
	return found;
}

std::vector<Product*> DDataStore::viewcart(std::string user)
{
	vector<Product*>found;
	map<string, vector<Product*> >::iterator it = carts.find(user);
	if(it == carts.end())
	{
		cout<<"ERROR: Invalid UserName"<<endl;
	}
	found = it->second;
	return found;
}

void DDataStore::addcart(std::string user, Product* p)
{
	map<string, vector<Product*> >::iterator it = carts.find(user);
	if(it != carts.end())
	{
		it->second.push_back(p);
	}
	else
	{
		cout<<"ERROR: Invalid UserName"<<endl;
		return;
	}
}

void DDataStore::buycart(std::string user)
{
	User* temp = NULL;
	for(vector<User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if((*it)->getName() == user)
		{
			temp = *it;
		}
		else if(it == users.end())
		{
			cout<<"ERROR: Invalid UserName"<<endl;
		}
	}
	map<string, vector<Product*> >::iterator lt = carts.find(user);
	for(vector<Product*>::iterator et = lt->second.begin(); et != lt->second.end();)
	{
		if(temp->getBalance() < (*et)->getPrice() || (*et)->getQty() == 0)
		{
			++et;
		}
		else
		{
			temp->deductAmount((*et)->getPrice());
			(*et)->subtractQty(1);
			et = lt->second.erase(et);
		}
	} 

}
void DDataStore::removeitem(std::string user, int pos)
{
	map<string, vector<Product*> >::iterator lt = carts.find(user);
	lt->second.erase(lt->second.begin()+pos);
}

std::vector<Product*> DDataStore::search(std::vector<std::string>& terms, int type)
{
	set<Product*>result;
	if(type == 0)
	{
		pair<string,set<Product*> >value;
		value = keymaptree.find(terms[0]);
		if(value.first.size() != 0)
		{
			result = value.second;
		}
		for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it)
		{
			pair<string, set<Product*> >other;
			other = keymaptree.find((*it));
			if(other.first.size() != 0)
			{
			result = setIntersection(result, other.second);
			}
		}

	}
	else if(type == 1)
	{
		for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it)
		{
			pair<string, set<Product*> >value;
			value = keymaptree.find((*it));
			if(value.first.size() != 0)
			{
				result = setUnion(result, value.second);
			}
		}

	}
	vector<Product*>finalresult;
	for(set<Product*>::iterator at = result.begin(); at != result.end(); ++at)
	{
		finalresult.push_back((*at));
	}
	return finalresult;
}

