//Primer Ejercicios
#include <iostream>
#include "first.h"

using namespace std;

int recursive(int num){
  if(num <= 1)
    return 1;

  return (num * recursive(num-1));
}
