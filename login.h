#ifndef LOGIN_H		
#define LOGIN_H
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
#include "info.h"
#include "recom.h"

class Login : public QWidget{
	Q_OBJECT

public:
	Login(DDataStore* &ds);
	~Login();


private slots:
	void closethis();
	void checkyoself();
	void newcrewintown();

private:
	QVBoxLayout* overallLayout;
	QHBoxLayout* username;
	QLabel* name;
	QLineEdit* namebar;
	QHBoxLayout* password;
	QLabel* riddle;
	QLineEdit* riddlebar;
	QHBoxLayout* buttons;
	QPushButton* logg;
	QPushButton* newuser;
	QPushButton* quit;
	RECOM* recommendation;
	Info* information;
	MainWindow* mainwindow;
	DDataStore* database;







};


#endif