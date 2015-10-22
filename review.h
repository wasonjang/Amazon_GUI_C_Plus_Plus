#ifndef REVIEW_H
#define REVIEW_H
#include <string>

/**
 * Models a review for the product identified by prodName
 */
struct Review
{
  Review() :  prodName(), rating(), rater(), date(), reviewText()
  { }
  Review(std::string& prod, 
	 int& rate, std::string& r,
	 std::string& d, 
	 std::string& review_text) :
    prodName(prod), 
    rating(rate), 
    rater(r),
    date(d), 
    reviewText(review_text)
  { }
  
  std::string prodName;
  int rating;
  std::string rater;
  std::string date;
  std::string reviewText;
};

#endif
