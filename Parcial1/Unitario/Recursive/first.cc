//Primer Ejercicios
#include <iostream>
#include "first.h"

using namespace std;

int recursive(int num){
  int res;

  if(num <= 1)
    return 1;

  res = num * recursive(num-1);
  return res;
}
