#include "Hierarchy.h"
#include "gtest/gtest.h"

//compile  g++ -isystem ../googletest/googletest/include/ -std=c++11 -pthread Fixture/Functions.h Fixture/valueParametrized_test.cc gtest_main.a -o Prueba

template <class T>
Base* factoryMethod()
{
  return new T;
};

template <>
Base* factoryMethod<Child3>()
{
  return new Child3(10);
};

template <class T>
class FixTypedWithConst : public testing::Test
{
protected:
  Base* instance2Test;
public:
  FixTypedWithConst() : instance2Test(factoryMethod<T>()){}
  virtual ~FixTypedWithConst()
  {
    delete instance2Test;
    instance2Test = NULL;
  }
};

typedef testing::Types<Child1, Child2, Child3> implementations; //Los tipos que vamos a andar testeando

TYPED_TEST_CASE(FixTypedWithConst, implementations);

TYPED_TEST(FixTypedWithConst, testName)
{
  EXPECT_EQ(1, this->instance2Test->doSomething());
}
