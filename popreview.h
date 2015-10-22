#ifndef POPREVIEW_H
#define POPREVIEW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRegExpValidator>
#include <QIntValidator>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"

class MainWindow;

class PopReview : public QWidget
{
	Q_OBJECT

public:
	PopReview(DDataStore* &ds, User* &u, Product* &p);
	~PopReview();
	void productchange(Product* c);

private slots:
	void review();
private:
	User* currentuser;
	DDataStore* ds;
	Product* currentproduct;
	QVBoxLayout* overallLayout;
	QLabel* shape;
	QLabel* number;
	QLabel* letter;
	QLineEdit* star;
	QLineEdit* date;
	QTextEdit* words;
	QHBoxLayout* buttons;
	QPushButton* submit;
	QPushButton* quit;
	QLabel* warnings;

};
#endif