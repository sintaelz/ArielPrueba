#include <iostream>
#include <stdio.h>
using namespace std;

class Base
{
public:
  int arr[5] = {1,5,3,4,2};
  int size = 5;
  virtual int* sortSmallBig() = 0;
};

class bubbleSort : public Base
{
public:
  int* sortSmallBig()
  {
    int j = 0;
    int tmp = 0;
    for(int i=0;i<size;i++)
    {
      j = i;
    for(int k = i;k<size;k++){
      if(arr[j]>arr[k]){
        j = k;
      }
    }
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    }
    return arr;
  }
};
