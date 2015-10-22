#include "info.h"
using namespace std;

Info::Info(DDataStore* &ds, string &name, long long &password)
{
	setWindowTitle("Information");
	pass = password;
	user = name;
	database = ds; 
	overallLayout = new QVBoxLayout();

	agebox = new QHBoxLayout();
	overallLayout->addLayout(agebox);

	age = new QLabel("Age:");
	agebox->addWidget(age);

	agebar = new QLineEdit();
	agebox->addWidget(agebar);

	moneybox = new QHBoxLayout();
	overallLayout->addLayout(moneybox);

	money = new QLabel("Credit Amount:");
	moneybox->addWidget(money);

	moneybar = new QLineEdit();
	moneybox->addWidget(moneybar);

	enter = new QPushButton("Enter");
	overallLayout->addWidget(enter);
	connect(enter, SIGNAL(clicked()), this, SLOT(creation()));
	setLayout(overallLayout);	
}
Info::~Info()
{

}

void Info::creation()
{
	if(agebar->text().isEmpty() == true)
	{
		QMessageBox::warning(this,"Age is empty", "Please enter a Age");
		return;
	}
	if(moneybar->text().isEmpty() == true)
	{
		QMessageBox::warning(this,"Credit Amount is empty", "Please enter a Credit Amount");
		return;
	}
	int year;
	double card;
	year = agebar->text().toInt();
	card = moneybar->text().toDouble();
	User* newuser = new User(user, year, card, 0, pass);
	database->addUser(newuser);
	this->close();
}
