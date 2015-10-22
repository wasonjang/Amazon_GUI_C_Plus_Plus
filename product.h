#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Product{
 public:
  Product(const std::string category, const std::string name, double price, int qty);
  virtual ~Product();

  /**
   * Returns the appropriate keywords that this product should be associated with
   */
  virtual std::set<std::string> keywords() const = 0;

  /**
   * Allows for a more detailed search beyond simple keywords
   */
  virtual bool isMatch(std::vector<std::string>& searchTerms) const;

  /**
   * Returns a string to display the product info for hits of the search 
   */
  virtual std::string displayString() const = 0;

  /**
   * Outputs the product info in the database format
   */
  virtual void dump(std::ostream& os) const;

  /**
   * Accessors and mutators
   */
  double getPrice() const;
  std::string getName() const;
  int getQty() const;
  void subtractQty(int num);
 
 protected:
  std::string name_;
  double price_;
  int qty_;
  std::string category_;
};
class Book : public Product
{
  public:
  Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author);
  virtual ~Book();
  virtual std::set<std::string> keywords() const;
  virtual std::string displayString() const;
  virtual void dump(std::ostream& os) const;
  std::string getisbn() const;
  std::string getauthor() const;

  private:
    std::string isbn_;
    std::string author_;
};

class Clothing : public Product
{
  public:

  Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
  virtual ~Clothing();
  virtual std::set<std::string> keywords() const;
  virtual std::string displayString() const;
  virtual void dump(std::ostream& os) const;
  std::string getsize() const;
  std::string getbrand() const;

  private:
    std::string size_;
    std::string brand_;
};

class Movie : public Product
{
  public:

  Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
  virtual ~Movie();
  virtual std::set<std::string> keywords() const;
  virtual std::string displayString() const;
  virtual void dump(std::ostream& os) const;
  std::string getgenre() const;
  std::string getrating() const;

  private:
    std::string genre_;
    std::string rating_; 
};

#endif
