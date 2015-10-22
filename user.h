#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <map>
/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User{
 public:
  User();
  User(std::string name, int age, double balance, int type, int password);
  virtual ~User();

  int getAge() const;
  double getBalance() const;
  std::string getName() const;
  void deductAmount(double amt);
  void basic(User* &u, double &number);
  std::map<User*, double> getBasic();
  int getPass() const;
  virtual void dump(std::ostream& os);
 private:
  std::string name_;
  int age_;
  double balance_;
  int type_;
  int password_;
  std::map<User*, double>bsim;
};
#endif
