#include "popreview.h"
using namespace std;

PopReview::PopReview(DDataStore* &ds, User* &u, Product* &p)
{
	this->ds = ds;
	currentproduct = p;
	currentuser = u;

	setWindowTitle("Add a Review");
	overallLayout = new QVBoxLayout();
	shape = new QLabel("Rating(1-5)");
	number = new QLabel("Date(YYYY-MM-DD)");
	letter = new QLabel("Your Review");
	star = new QLineEdit();
	date = new QLineEdit();
	words = new QTextEdit();
	overallLayout->addWidget(shape);
	overallLayout->addWidget(star);
	overallLayout->addWidget(number);
	overallLayout->addWidget(date);
	overallLayout->addWidget(letter);
	overallLayout->addWidget(words);
	warnings = new QLabel(" ");
	overallLayout->addWidget(warnings);
	buttons = new QHBoxLayout();
	overallLayout->addLayout(buttons);
	submit = new QPushButton("Submit");
	connect(submit, SIGNAL(clicked()), this, SLOT(review()));	
	quit = new QPushButton("Quit");
	connect(quit, SIGNAL(clicked()), this, SLOT(close()));
	buttons->addWidget(submit);
	buttons->addWidget(quit);
	setLayout(overallLayout);
}
PopReview::~PopReview()
{
	delete warnings;
	delete quit;
	delete submit;
	delete words;
	delete date;
	delete star;
	delete letter;
	delete number;
	delete shape;
	delete buttons;
	delete overallLayout;
}
void PopReview::productchange(Product* c)
{
	currentproduct = c;
}

void PopReview::review()
{
	if(currentproduct == NULL)
	{
		warnings->setText("No product selected.");
		return;
	}
	if(star->text().isEmpty() == true)
	{
		warnings->setText("Please enter a rating.");
		return;
	}
	if(date->text().isEmpty() == true)
	{
		warnings->setText("Please enter a date.");
		return;
	}
	if(words->toPlainText().isEmpty() == true)
	{
		warnings->setText("Please enter a review.");
		return;
	}
	string pron = currentproduct->getName();
	int nombre = star->text().toInt();
	string months = date->text().toStdString();
	string paragraph  = words->toPlainText().toStdString();
	string rater = currentuser->getName();
	Review* newreview = new Review(pron, nombre, rater, months, paragraph);
	ds->addReview(newreview);
	warnings->setText("Review added. Refresh the review.");
}