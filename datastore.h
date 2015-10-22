#ifndef DATASTORE_H
#define DATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "util.h"
#include "review.h"
#include <map>
#include "splay.h"
/** 
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */
class DataStore {
 public:
  virtual ~DataStore() { }

  /**
   * Adds a product to the data store
   */
  virtual void addProduct(Product* p) = 0;
 
  /**
   * Adds a user to the data store
   */
  virtual void addUser(User* u) = 0;

  /**
   * Performs a search of products whose keywords match the given "terms"
   *  type 0 = AND search (intersection of results for each term) while
   *  type 1 = OR search (union of results for each term)
   */
  virtual std::vector<Product*> search(std::vector<std::string>& terms, int type) = 0;

  virtual void addReview(Review* r) = 0;

  /**
   * Reproduce the database file from the current Products and User values
   */
  virtual void dump(std::ostream& ofile) = 0;

};

class DDataStore : public DataStore
{
  public:
    virtual ~DDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    User* findthatperson(std::string u);
    bool doyouexist(std::string u);
    std::map<User*,int>whoratedthis(std::string item, std::string curr);
    void addReview(Review* r);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    std::vector<Product*> viewcart(std::string user);
    void buycart(std::string user);
    void removeitem(std::string user, int pos);
    double averagereview(std::string productname);
    void addcart(std::string user, Product* p);
    std::map<User*, std::map<User*, double> > makeGraph();
    void basicCalc();
    std::set<Product*> notRated(std::string person);
    std::vector<User*>users;
    std::vector<Review*> getReview(std::string user);
  private:
    SplayTree <std::string, std::set<Product*> >keymaptree;
    std::vector<Review*>reviews;
    std::vector<Product*>products;
    std::map< std::string, std::vector<Review*> > texts;
    std::map< std::string, std::vector<Product*> >carts;
    std::map< std::string, std::set<Product*> > reviewsheet;
    std::map< std::string, std::map<std::string, Review*> > peoplereview;
    std::map<User*, std::map<User*, double> >graph;
};

#endif
