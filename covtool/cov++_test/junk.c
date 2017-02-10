#if 1
#include <stdlib.h>
#include <iostream>



static int total = 0;


int main()
{
   int i;

   for(i=0; i < 99; ++i)
   {
     ++total;

     if(total >= 90)
       break;
   }

   if(total > 90) 
     std::cout << "total = " << std::endl;  // will not print!

   ++total;
}
#endif

