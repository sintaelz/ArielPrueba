template <class T>
bool isEven(T value)
{
  if(value % 2 == 0)
    return true;
  return false;
};

template <class T>
bool isOdd(T value)
{
  if(value % 2 != 0)
    return true;
  return false;
};
