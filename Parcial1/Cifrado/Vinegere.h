#include "Cifrado.h"

class Vinegere : public Cifrado
{
public:
  Vinegere(){};
  ~Vinegere(){};
  int decrypt(string encryptWord);
};
