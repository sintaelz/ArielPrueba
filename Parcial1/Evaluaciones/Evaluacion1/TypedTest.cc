#include "Ordenamiento.h"
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

typedef testing::Types<bubbleSort> implementations; //Los tipos que vamos a andar testeando

TYPED_TEST_CASE(FixTyped, implementations);

TYPED_TEST(FixTyped, testName)
{
  int res[5] = {1,2,3,4,5};
  this->instance2Test->sortSmallBig();
  for (int i = 0; i < 5; i++)
  {
    EXPECT_EQ(res[i], this->instance2Test->arr[i]);
  }
}
