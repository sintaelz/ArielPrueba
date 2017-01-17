#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

class Cifrado
{
public:
  Cifrado(){};
  ~Cifrado(){};
  virtual int decrypt(string encryptWord) = 0;
};
