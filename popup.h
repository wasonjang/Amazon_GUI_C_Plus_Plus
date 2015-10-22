#ifndef POPUP_H
#define POPUP_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
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
class PopUp : public QWidget
{
	Q_OBJECT

public:
	PopUp(DDataStore* &ds, QString &name, User* &u);
	~PopUp();
	void refresh();

private slots:
	void purchase();
	void removeitem();
	void itemchange(int index);
private:
	int currentitem;
	User* u;
	DDataStore* ds;
	std::string username;
	QVBoxLayout* overallLayout;
	QHBoxLayout* cash;
	QLabel* amount;
	QLabel* number;
	QHBoxLayout* buttons;
	QPushButton* buy;
	QPushButton* REMOVE;
	QPushButton* quitbutton;
	QListWidget* incart;
};

#endif