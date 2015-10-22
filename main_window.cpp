#include "main_window.h"
#include "msort.h"
using namespace std;

MainWindow::MainWindow(DDataStore* &ds, User* &u, RECOM* &recom)
{
	setWindowTitle("Amazon");
	this -> recom = recom;
	up = NULL;
	r = NULL;
	currentproduct =NULL;
	this->ds = ds;
	currentuser = u;
	//overall
	overallLayout = new QHBoxLayout();

	//options
	options = new QVBoxLayout();
	overallLayout->addLayout(options);
	//search bar
	searchsection = new QHBoxLayout();
	options->addLayout(searchsection);
	//search label
	search = new QLabel("Terms:");
	searchsection->addWidget(search);
	//search bar
	searchbar = new QLineEdit();
	searchsection->addWidget(searchbar);
	//radio buttons for search option;
	radio = new QHBoxLayout();
	options->addLayout(radio);
	//and button;
	et = new QLabel("AND");
	radio->addWidget(et);
	AND = new QRadioButton();
	radio->addWidget(AND);
	//or button;
	ou = new QLabel("OR");
	radio->addWidget(ou);
	OR = new QRadioButton();
	radio->addWidget(OR);
	//go
	go = new QPushButton("Go");
	connect(go, SIGNAL(clicked()), this, SLOT(searching()));
	options->addWidget(go);
	//sort options
	sortsection = new QHBoxLayout();
	options->addLayout(sortsection);
	sort = new QLabel("Sort by:");
	sortsection->addWidget(sort);
	alphabet = new QPushButton("Alphabet");
	rates = new QPushButton("Average Rating");
	alphabet->setCheckable(true);
	rates->setCheckable(true);
	connect(rates, SIGNAL(clicked()), this, SLOT(sortrates())); 
	connect(alphabet, SIGNAL(clicked()), this, SLOT(sortalpha()));
	sortsection->addWidget(alphabet);
	sortsection->addWidget(rates);
	//user list
	userlist = new QHBoxLayout();
	options->addLayout(userlist);
	userlabel = new QLabel("Current User:");
	userlist->addWidget(userlabel);
	customers = new QComboBox();
	customers->addItem(QString::fromStdString(currentuser->getName()));
	userlist->addWidget(customers);
	//Cartoptions
	cartsection = new QHBoxLayout();
	options->addLayout(cartsection);
	add = new QPushButton("Add-to-Cart");
	connect(add, SIGNAL(clicked()), this, SLOT(addtocart()));
	view = new QPushButton("View-Cart");
	connect(view, SIGNAL(clicked()), this, SLOT(newWindow()));
	cartsection->addWidget(add);
	cartsection->addWidget(view);
	//addreview
	newreview = new QPushButton("Add Review");
	connect(newreview, SIGNAL(clicked()), this, SLOT(newReviewWindow()));
	options->addWidget(newreview);
	refreshbutton = new QPushButton("Refresh Review");
	connect(refreshbutton, SIGNAL(clicked()), this, SLOT(refreshreview()));
	options->addWidget(refreshbutton);
	newdata = new QHBoxLayout();
	options->addLayout(newdata);
	data = new QLabel("New Database File:");
	newdata->addWidget(data);
	whatisit = new QLineEdit();
	newdata->addWidget(whatisit);
	save = new QPushButton("Save");
	connect(save, SIGNAL(clicked()), this, SLOT(savefile()));
	options->addWidget(save);
	//quit button;
	quitbutton = new QPushButton("Quit");
	connect(quitbutton, SIGNAL(clicked()), this, SLOT(closewindows()));
	options->addWidget(quitbutton);
	//stretch
	options->addStretch();
	//display search result
	sectiontwo = new QVBoxLayout();
	overallLayout->addLayout(sectiontwo);
	stuff = new QLabel("Products");
	sectiontwo->addWidget(stuff);
	result = new QListWidget();
	connect(result, SIGNAL(currentRowChanged(int)), this, SLOT(currentitemchange(int)));
	sectiontwo->addWidget(result);

	//review box
	sectionthree = new QVBoxLayout();
	overallLayout->addLayout(sectionthree);
	label = new QLabel("Reviews");
	sectionthree->addWidget(label);
	reviewcontainer = new QListWidget();
	sectionthree->addWidget(reviewcontainer);
	setLayout(overallLayout);	
}
MainWindow::~MainWindow()
{
	if(r != NULL)
	{
		for(unsigned int i =0; i<apple.size(); i++)
		{
			delete apple[i];
		}
	}
	if(up != NULL)
	{
		for(unsigned int i =0; i<windows.size(); i++)
		{
			delete windows[i];
		}
	}
	delete refreshbutton;
	delete reviewcontainer;
	delete label;
	delete sectionthree;
	delete result;
	delete stuff;
	delete sectiontwo;
	delete save;
	delete quitbutton;
	delete view;
	delete add;
	delete cartsection;
	delete customers;
	delete userlabel;
	delete userlist;
	delete rates;
	delete alphabet;
	delete sort;
	delete sortsection;
	delete go;
	delete ou;
	delete et;
	delete OR;
	delete AND;
	delete radio;
	delete searchbar;
	delete search;
	delete searchsection;
	delete options;
	delete overallLayout;
}
void MainWindow::sortalpha()
{
	rates->setChecked(false);
	alphabetsort(hits);
	result->clear();
	for(unsigned int i = 0; i<hits.size(); i++)
	{
		QString display;
		display += QString::number(i+1);
		display += ". ";
		display += QString::fromStdString(hits[i]->displayString());
		result->addItem(display);
	}	
	alphabet->setChecked(false);
}
void MainWindow::sortrates()
{
	alphabet->setChecked(false);
	starsort(hits, ds);
	result->clear();
	for(unsigned int i = 0; i<hits.size(); i++)
	{
		QString display;
		display += QString::number(i+1);
		display += ". ";
		display += QString::fromStdString(hits[i]->displayString());
		result->addItem(display);
	}	
	rates->setChecked(false);
}
void MainWindow::searching()
{
	if(AND->isChecked() == false && OR->isChecked()==false)
	{
		return;
	}
	if(searchbar->text().isEmpty())
	{
		return;
	}
	reviewcontainer->clear();
	result->clear();
	vector<string> terms;
	string line;
	line = searchbar->text().toStdString();
	stringstream ss(line);
	string term;
	if(AND->isChecked() == true)
	{
		while(ss >> term)
		{
			term = convToLower(term);
			terms.push_back(term);
		}
		hits = ds->search(terms, 0);
		for(unsigned int i = 0; i<hits.size(); i++)
		{
			QString display;
			display += QString::number(i+1);
			display += ". ";
			display += QString::fromStdString(hits[i]->displayString());
			result->addItem(display);
		}
		searchbar->clear();

	}
	else
	{
		while(ss >> term)
		{
			term = convToLower(term);
			terms.push_back(term);
		}
		hits = ds->search(terms, 1);
		for(unsigned int i = 0; i<hits.size(); i++)
		{
			QString display;
			display += QString::number(i+1);
			display += ". ";
			display += QString::fromStdString(hits[i]->displayString());
			result->addItem(display);
		}
		searchbar->clear();
	}
}
void MainWindow::currentitemchange(int currentindex)
{
	if(currentindex < 0)
	{
		return;
	}
	reviewcontainer->clear();
	currentproduct = hits[currentindex];
	string theproductname; 
	theproductname = currentproduct->getName();
	opinions = ds->getReview(theproductname);
	reviewsort(opinions);
	for(unsigned int i = 0; i<opinions.size(); i++)
	{
		QString display;
		display += QString::number(opinions[i]->rating);
		display += " Stars ";
		display += "By ";
		display += QString::fromStdString(opinions[i]->rater);
		display += " On ";
		display += QString::fromStdString(opinions[i]->date);
		display += "\n";
		display += QString::fromStdString(opinions[i]->reviewText);
		reviewcontainer->addItem(display);
	}
	if (r != NULL)
	{
		r->productchange(currentproduct);
	}

}
void MainWindow::addtocart()
{
	if(currentproduct == NULL)
	{
		return;
	}
	string thename = currentuser->getName();
	ds->addcart(thename, currentproduct);
	if(up != NULL)
	{
		for(unsigned int i =0; i<windows.size(); i++)
		{
			windows[i]->refresh();
		}
	}
}
void MainWindow::closewindows()
{

	QMessageBox msgBox;
	msgBox.setWindowTitle("Quitting Amazon");
	msgBox.setText("Are You Sure???");
	msgBox.setInformativeText("Really Really Sure?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Yes)
	{
		if(r != NULL)
		{
			for(unsigned int i =0; i<apple.size(); i++)
			{
				apple[i]->close();
			}
		}
		if(up != NULL)
		{
			for(unsigned int i =0; i<windows.size(); i++)
			{
				windows[i]->close();
			}
		}
		recom->close();
		this->close();
	}
	else if(userAnswer == QMessageBox::No)
	{
		return;
	}
}

void MainWindow::newReviewWindow()
{

	r = new PopReview(ds, currentuser, currentproduct);
	apple.push_back(r);
	r->show();
}
void MainWindow::newWindow()
{
	QString name;
	name = QString::fromStdString(currentuser->getName());
	up = new PopUp(ds, name, currentuser);
	windows.push_back(up);
	up->show();
}
void MainWindow::savefile()
{
	string filename;
	filename = whatisit->text().toStdString();
	char const *p = filename.c_str();
	ofstream ofile(p);
	ds->dump(ofile);
	ofile.close();
	QMessageBox msgBox;
	msgBox.setWindowTitle("File Saved");
	msgBox.setText("Database saved");
	msgBox.exec();
}
void MainWindow::refreshreview()
{
	if(currentproduct == NULL)
	{
		return;
	}
	string theproductname; 
	theproductname = currentproduct->getName();
	opinions = ds->getReview(theproductname);
	reviewsort(opinions);
	reviewcontainer->clear();
	for(unsigned int i = 0; i<opinions.size(); i++)
	{
		QString display;
		display += QString::number(opinions[i]->rating);
		display += " Stars ";
		display += " On ";
		display += QString::fromStdString(opinions[i]->date);
		display += "\n";
		display += QString::fromStdString(opinions[i]->reviewText);
		reviewcontainer->addItem(display);
	}

}