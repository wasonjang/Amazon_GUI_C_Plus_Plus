#include "main_window.h"
#include "login.h"
#include <QApplication>
#include "popup.h"
#include "popreview.h"
using namespace std;
int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please specify a database file" << endl;
  }

  DDataStore* ds = new DDataStore;



  DBParser parser;

  parser.addProductParser(new ProductBookParser);
  parser.addProductParser(new ProductClothingParser);
  parser.addProductParser(new ProductMovieParser);

  // Now parse the database to populate the DataStore
  if( parser.parse(argv[1], *ds) ){
    cerr << "Error parsing!" << endl;
    return 1;
  }
	QApplication app(argc, argv);

  ds->basicCalc();
  
	Login L(ds);

	L.show();

	return app.exec();
  delete ds;
}