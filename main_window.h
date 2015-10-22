#ifndef MAIN_WINDOW_H		
#define MAIN_WINDOW_H
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
#include "popup.h"
#include "popreview.h"
#include "recom.h"




class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(DDataStore* &ds, User* &u, RECOM* &recom);
	~MainWindow();
private slots:
	void savefile();
	void refreshreview();
	void newWindow();
	void newReviewWindow();
	void closewindows();
	void searching();
	void addtocart();
	void currentitemchange(int currentindex);
	void sortalpha();
	void sortrates();
private:
	RECOM* recom;
	PopReview* r;
	PopUp* up;
	DDataStore* ds;
	std::vector<Product*> hits;
	Product* currentproduct;
	User* currentuser;
	std::vector<PopUp*> windows;
	std::vector<PopReview*> apple;
	std::vector<Review*> opinions;
	// // UI

	// Layouts
	QHBoxLayout* overallLayout;

	//first section with options
	QVBoxLayout* options;
	//search bar section
	QHBoxLayout* searchsection;
	QLabel* search;
	QLineEdit* searchbar;
	//radio button section
	QHBoxLayout* radio;
	QRadioButton* AND;
	QRadioButton* OR;
	QLabel* et;
	QLabel* ou;
	//go button
	QPushButton* go;
	//sort optiions
	QHBoxLayout* sortsection;
	QLabel* sort;
	QPushButton* alphabet;
	QPushButton* rates;
	//users
	QHBoxLayout* userlist;
	QLabel* userlabel;
	QComboBox* customers;
	//cartsection
	QHBoxLayout* cartsection;
	QPushButton* add;
	QPushButton* view;
	//addreview
	QPushButton* newreview;
	QHBoxLayout* newdata;
	QLabel* data;
	QLineEdit* whatisit;
	QPushButton* save;
	//quitbutton
	QPushButton* quitbutton;
	//display item
	QVBoxLayout* sectiontwo;
	QLabel* stuff;
	QListWidget* result;
	//review box
	QPushButton* refreshbutton;
	QVBoxLayout* sectionthree;
	QLabel* label;
	QListWidget* reviewcontainer;

};
#endif