#include "popup.h"
using namespace std;

PopUp::PopUp(DDataStore* &ds, QString &name, User* &u)
{
	setWindowTitle("Shopping Cart");
	currentitem = -1;
	this->ds = ds;
	this->u = u;
	this->username = name.toStdString();
	QString money = QString::number(u->getBalance());
	overallLayout = new QVBoxLayout();
	cash = new QHBoxLayout();
	overallLayout->addLayout(cash);
	amount = new QLabel("Current Credit:");
	number = new QLabel(money);
	cash->addWidget(amount);
	cash->addWidget(number);
	incart = new QListWidget();
	vector<Product*>usercart = ds->viewcart(username);
	for(unsigned int i = 0; i< usercart.size(); i++)
	{
		Product* p = usercart[i];
		incart->addItem(QString::fromStdString(p->displayString()));
	}
	connect(incart, SIGNAL(currentRowChanged(int)), this, SLOT(itemchange(int)));
	overallLayout->addWidget(incart);
	buttons = new QHBoxLayout();
	overallLayout->addLayout(buttons);
	buy = new QPushButton("Buy-Cart");
	connect(buy, SIGNAL(clicked()), this, SLOT(purchase()));
	REMOVE = new QPushButton("Remove");
	connect(REMOVE, SIGNAL(clicked()), this, SLOT(removeitem()));
	buttons->addWidget(buy);
	buttons->addWidget(REMOVE);
	quitbutton = new QPushButton("Quit");
	connect(quitbutton, SIGNAL(clicked()), this, SLOT(close()));
	overallLayout->addWidget(quitbutton);
	setLayout(overallLayout);

}
PopUp::~PopUp()
{
	delete buy;
	delete REMOVE;
	delete quitbutton;
	delete incart;
	delete amount;
	delete number;
	delete buttons;
	delete cash;
	delete overallLayout;
}
void PopUp::removeitem()
{
	if(ds->viewcart(username).size() == 0)
	{
		currentitem = -1;
		return;
	}
	if(currentitem < 0)
	{
		return;
	}
	ds->removeitem(username, currentitem);
	incart->clear();
	vector<Product*>usercart = ds->viewcart(username);
	for(unsigned int i = 0; i< usercart.size(); i++)
	{
		Product* p = usercart[i];
		incart->addItem(QString::fromStdString(p->displayString()));
	}
}
void PopUp::itemchange(int index)
{
	if(ds->viewcart(username).size() == 0)
	{
		currentitem = -1;
		return;
	}
	currentitem = index;
}
void PopUp::purchase()
{
	ds->buycart(username);
	QString nowmoney = QString::number(u->getBalance());
	number->setText(nowmoney);
	incart->clear();
	vector<Product*>nowcart = ds->viewcart(username);
	for(unsigned int i = 0; i< nowcart.size(); i++)
	{
		Product* p = nowcart[i];
		incart->addItem(QString::fromStdString(p->displayString()));
	}
}
void PopUp::refresh()
{
	incart->clear();
	vector<Product*>usercart = ds->viewcart(username);
	for(unsigned int i = 0; i< usercart.size(); i++)
	{
		Product* p = usercart[i];
		incart->addItem(QString::fromStdString(p->displayString()));
	}
}	