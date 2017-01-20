#include "Cifrado.h"
#include "gtest/gtest.h"

//compile  g++ -isystem ../googletest/googletest/include/ -std=c++11 -pthread Fixture/Functions.h Fixture/valueParametrized_test.cc gtest_main.a -o Prueba

template <class instanceType>
class FixTyped : public testing::Test
{
public:
  FixTyped()
  {
    instance2Test = new instanceType;
  }
  ~FixTyped()
  {
    delete instance2Test;
    instance2Test = NULL;
  }
protected:
  Base* instance2Test;
};

typedef testing::Types<Child1, Child2> implementations; //Los tipos que vamos a andar testeando

TYPED_TEST_CASE(FixTyped, implementations);

TYPED_TEST(FixTyped, testName)
{
  EXPECT_EQ(1, this->instance2Test->doSomething());
}
