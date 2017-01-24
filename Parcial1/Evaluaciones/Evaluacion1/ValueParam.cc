#include "gtest/gtest.h"
#include "Ordenamiento.h"

//compile  g++ -isystem ../googletest/googletest/include/ -std=c++11 -pthread Fixture/Functions.h Fixture/valueParametrized_test.cc gtest_main.a -o Prueba

class FixValParam : public testing::TestWithParam<int*>
{
protected:
  Base* instance2Test;
public:
  void SetUp()
  {
    instance2Test = GetParam();
  }
  void TearDown()
  {
    delete instance2Test;
    instance2Test = NULL;
  }
};

TEST_P(FixValParam, sortSmallBig)
{
  int res[5] = {1,2,3,4,5};
  this->instance2Test->sortSmallBig();
  for (int i = 0; i < 5; i++)
  {
    EXPECT_EQ(res[i], this->instance2Test->arr[i]);
  }
}

int array[] = {1,2,3,4,5};
INSTANTIATE_TEST_CASE_P(UsingValuesIn, FixValParam, testing::ValuesIn(array));
