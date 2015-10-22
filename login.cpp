#include "login.h"
#include "cmath"
#include "heap.h"
using namespace std;

struct Compare
{
  bool operator()(const pair<User*, double> m1, const pair<User*,double> m2) const
  {
    double f1;
    double f2;
    f1 = m1.second;
    f2 = m2.second;
    if(f1 < f2)
    {
      return true;
    }
    return false;


  }
};

Login::Login(DDataStore* &ds)
{
	database = ds;
	setWindowTitle("Amazon");
	overallLayout = new QVBoxLayout();

	username = new QHBoxLayout();
	overallLayout->addLayout(username);

	name = new QLabel("Username:");
	username->addWidget(name);

	namebar = new QLineEdit();
	username->addWidget(namebar);

	password = new QHBoxLayout();
	overallLayout->addLayout(password);

	riddle = new QLabel("Password:");
	password->addWidget(riddle);

	riddlebar = new QLineEdit();
	password->addWidget(riddlebar);

	buttons = new QHBoxLayout();
	overallLayout->addLayout(buttons);

	logg = new QPushButton("Login");
	buttons->addWidget(logg);
	connect(logg, SIGNAL(clicked()), this, SLOT(checkyoself()));

	newuser = new QPushButton("New User");
	buttons->addWidget(newuser);
	connect(newuser, SIGNAL(clicked()), this, SLOT(newcrewintown()));

	quit = new QPushButton("Quit");
	overallLayout->addWidget(quit);
	connect(quit, SIGNAL(clicked()), this, SLOT(closethis()));
	setLayout(overallLayout);	
}

Login::~Login()
{


}

void Login::newcrewintown()
{
	if(namebar->text().isEmpty() == true)
	{
		QMessageBox::warning(this,"Username is empty", "Please enter a Username");
		return;
	}
	if(riddlebar->text().isEmpty() == true)
	{
		QMessageBox::warning(this,"Password is empty", "Please enter a Password");
		return;
	}
	string theuser;
	string thepassword;
	theuser = namebar->text().toStdString();
	thepassword = riddlebar->text().toStdString();
	if(database->doyouexist(theuser) == true)
	{
		QMessageBox::warning(this,"User exists", "Please enter a valid Username");
		return;		
	}
	if(thepassword.size() > 8)
	{
		QMessageBox::warning(this,"Password length is too long", "Please enter a password no longer than 8 characters");
		return;		
	}
	for(unsigned int i = 0; i<thepassword.size(); i++)
	{
		string s;
		s = " ";
		
		if(thepassword[i] == s[0])
		{
			QMessageBox::warning(this,"Invalid Password", "Password cannot contain whitespace");
			return;		
		}
	}
	long long truepassword = 0;
	for(unsigned int i = 0; i<thepassword.size(); i++)
	{
		truepassword += ((int)thepassword[thepassword.size()-(i+1)])*((long long)pow(128,i));
	}
	long long w4;
	w4 = truepassword % 65521;
	long long w3;
	w3 = (truepassword/65521) % 65521;
	long long w2;
	w2 = ((truepassword/65521)/65521) % 65521;
	long long w1;
	w1 = (((truepassword/65521)/65521)/65521) % 65521;
	unsigned int array[4];
	array[3] = w1;
	array[2] = w2;
	array[1] = w3;
	array[0] = w4;
	long long finalpassword;
	finalpassword = (45912 * array[3] + 35511 * array[2] + 65169 * array[1] + 4625 * array[0]) % 65521;
	information = new Info(database, theuser, finalpassword);
	information->show();
}
void Login::checkyoself()
{
	if(namebar->text().isEmpty() == true)
	{
		QMessageBox::warning(this,"Username is empty", "Please enter a Username");
		return;
	}
	if(riddlebar->text().isEmpty() == true)
	{
		QMessageBox::warning(this,"Password is empty", "Please enter a Password");
		return;
	}
	string theuser;
	string thepassword;
	theuser = namebar->text().toStdString();
	thepassword = riddlebar->text().toStdString();
	if(database->doyouexist(theuser) == false)
	{
		QMessageBox::warning(this,"User does not exist", "Please enter a valid Username");
		return;		
	}
	User* u;
	u = database->findthatperson(theuser);
	long long truepassword = 0;
	for(unsigned int i = 0; i<thepassword.size(); i++)
	{
		truepassword += ((int)thepassword[thepassword.size()-(i+1)])*((long long)pow(128,i));
	}
	long long w4;
	w4 = truepassword % 65521;
	long long w3;
	w3 = (truepassword/65521) % 65521;
	long long w2;
	w2 = ((truepassword/65521)/65521) % 65521;
	long long w1;
	w1 = (((truepassword/65521)/65521)/65521) % 65521;
	unsigned int array[4];
	array[3] = w1;
	array[2] = w2;
	array[1] = w3;
	array[0] = w4;
	long long finalpassword;
	finalpassword = (45912 * array[3] + 35511 * array[2] + 65169 * array[1] + 4625 * array[0]) % 65521;
	if(u->getPass() == finalpassword)
	{
		std::map<User*, std::map<User*, double> >graph = database->makeGraph();
		std::map<User*, double>refined;
		vector<User*>list;
		list = database->users;
		for(vector<User*>::iterator it = list.begin(); it != list.end(); ++it)
		{
			if((*it) != u)
			{
				double initial;
				initial = 1000.0;
				refined.insert(pair<User*,double>((*it),initial));
			}
			else
			{
				double initial;
				initial = 0.0;
				refined.insert(pair<User*,double>((*it),initial));
			}
		} 
		Compare c;
		Heap<pair<User*, double>, Compare> PQ(2,c);
		for(map<User*, double>::iterator lt = refined.begin(); lt != refined.end(); ++lt)
		{
			pair<User*, double>node = *lt;
			PQ.push(node);
		}
		while(!PQ.empty())
		{
			pair<User*, double>v = PQ.top();
			PQ.pop();
			map<User*, map<User*, double> >::iterator tt = graph.find(v.first);
			map<User*, double>neighbors = tt->second;
			for(map<User*, double>::iterator f = neighbors.begin(); f != neighbors.end(); ++f)
			{
				double weight = f->second;
				double newdist = weight + v.second;
				map<User*, double>::iterator zz = refined.find(f->first);
				double olddist = zz->second;
				if(newdist < olddist)
				{
					zz->second = newdist;
					pair<User*,double>PQDecrease(zz->first, newdist);
					PQ.replace(PQDecrease);
				}
			}
		}
		pair<Product*, double>mostinteresting;
		mostinteresting.first = NULL;
		mostinteresting.second = -1.0;
		set<Product*>yetRated;
		yetRated = database->notRated(u->getName());
		for(set<Product*>::iterator b = yetRated.begin(); b != yetRated.end(); ++b)
		{
			double RPW = 0;
			double RP = 0;
			double W = 0;
			map<User*, int>otherpeople;
			otherpeople = database->whoratedthis((*b)->getName(),u->getName());
			for(map<User*, int>::iterator x = otherpeople.begin(); x != otherpeople.end(); ++x)
			{
				map<User*, double>::iterator y = refined.find(x->first);
				double k = 1.00 - y->second;
				W += k;
				double j = (1.00 - y->second)*x->second;
				RP += j;
			}
			if(W == 0.0)
			{
				RPW = 0.0;
			}
			else
			{
				RPW = RP/W;
			}
			if(RPW > mostinteresting.second)
			{
				mostinteresting.first = *b;
				mostinteresting.second = RPW;
			}

		}
		recommendation = new RECOM(database, mostinteresting.first, u);
		mainwindow = new MainWindow(database, u, recommendation);
		mainwindow->show();
		recommendation->show();
		this->close();
	}
	else
	{
		QMessageBox::warning(this,"Incorrect Password", "Please enter the correct Password");
		return;		
	}
}

void Login::closethis()
{
	this->close();
}