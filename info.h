#ifndef INFO_H		
#define INFO_H
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
#include "main_window.h"

class Info : public QWidget{
	Q_OBJECT

public:

	Info(DDataStore* &ds, std::string &name, long long &password);
	~Info();


private slots:
	void creation();

private:
	QVBoxLayout* overallLayout;
	QHBoxLayout* agebox;
	QLabel* age;
	QLineEdit* agebar;
	QHBoxLayout* moneybox;
	QLabel* money;
	QLineEdit* moneybar;
	QPushButton* enter;
	long long pass;
	std::string user;
	DDataStore* database;

};


#endif