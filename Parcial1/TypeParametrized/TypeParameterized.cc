#include "TypeParameterized.h"

//compile  g++ -isystem ../googletest/googletest/include/ -std=c++11 -pthread Fixture/Functions.h Fixture/valueParametrized_test.cc gtest_main.a -o Prueba 

typedef testing::Types<Child1, Child2> implementations;

INSTANTIATE_TYPED_TEST_CASE_P(MiPrueba, TypeParameterized, implementations);
