#include "recom.h"
using namespace std;

RECOM::RECOM(DDataStore* &ds, Product* &p, User* &user)
{
	setWindowTitle("Product Recommendation");
	this->user = user;
	database = ds;
	this->p = p;
	overallLayout = new QVBoxLayout();
	if(p == NULL)
	{
		title = new QLabel("No more products to recommend");
	}
	else
	{
		title = new QLabel("Here is the recommended product");
	}
	overallLayout->addWidget(title);
	display = new QListWidget();
	overallLayout->addWidget(display);
	QString item;
	if(p != NULL)
	{
		item = QString::fromStdString(p->displayString());
	}
	else
	{
		item = ("There are no more products to recommend :(");
	}
	display -> addItem(item);	
	buttons = new QHBoxLayout();
	overallLayout->addLayout(buttons);
	buy = new QPushButton("Add to Cart");
	quit = new QPushButton("Quit");
	buttons->addWidget(buy);
	connect(buy, SIGNAL(clicked()), this, SLOT(add()));
	buttons->addWidget(quit);
	connect(quit, SIGNAL(clicked()), this, SLOT(quittitle()));
	setLayout(overallLayout);

}


RECOM::~RECOM()
{

}
void RECOM::quittitle()
{
	this->close();
}
void RECOM::add()
{
	database->addcart(user->getName(), p);
}