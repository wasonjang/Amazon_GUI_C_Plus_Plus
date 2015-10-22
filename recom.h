#ifndef RECOM_H		
#define RECOM_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QRadioButton>
#include "datastore.h"

class RECOM : public QWidget{
	Q_OBJECT

public:

	RECOM(DDataStore* &ds, Product* &p, User* &user);
	~RECOM();


private slots:
void add();
void quittitle();

private:
	QVBoxLayout* overallLayout;
	QLabel* title;
	QHBoxLayout* buttons;
	QPushButton* buy;
	QPushButton* quit;
	QListWidget* display;
	DDataStore* database;
	Product* p;
	User* user;
};


#endif