#include "Cifrado.h"

class Cesar : public Cifrado
{
public:
  Cesar(){};
  ~Cesar(){};
  int decrypt(string encryptWord);
};

int Cesar::decrypt(string encryptWord)
{
  int offset = 0;
  string tempWord, line;
  ifstream dictionary("diccionario.txt");
  if (dictionary.is_open())
  {
    while(offset <= 25)
    {
      for (int i = 0; i < encryptWord.length(); i++)
      {
        tempWord[i] = ((encryptWord[i]+offset) % 26);
      }
      while (getline (dictionary,line))
      {
        if(tempWord.compare(line))
        {
          return offset;
        }
      }
      dictionary.close();
    }
  }
  else
  {
    cout << "Unable to open file";
    return -1;
  }
};
