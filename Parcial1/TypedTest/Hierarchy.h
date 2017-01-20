#include <iostream>
using namespace std;

class Base
{
public:
  virtual int doSomething() = 0;
};

class Child1 : public Base
{
public:
  int doSomething()
  {
    cout << "Im child 1" << endl;
    return 1;
  }
};

class Child2 : public Base
{
public:
  int doSomething()
  {
    cout << "Im child 2" << endl;
    return 1;
  }
};

class Child3 : public Base
{
protected:
  int value;
public:
  Child3(int value) : value(value){};

  int doSomething()
  {
    cout << "Im child 3 with a value of " << value << endl;
    return 1;
  }
};
