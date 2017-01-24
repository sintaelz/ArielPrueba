#include "TypeParameterized.h"

//compile  g++ -isystem ../googletest/googletest/include/ -std=c++11 -pthread Fixture/Functions.h Fixture/valueParametrized_test.cc gtest_main.a -o Prueba

typedef testing::Types<bubbleSort> implementations;

INSTANTIATE_TYPED_TEST_CASE_P(MiPrueba, TypeParameterized, implementations);
