#include <stdio.h>
#include <covstream.h>

typedef CovStream::iterator cs_iterator;
typedef CovStream::token    token;

int main()
{
  CovStream s(stdin);

  fprintf(stderr, "file size is %ld\n", s.file_size());

  cs_iterator scan = s.begin();
  cs_iterator end  = s.end();

  while(scan != end)
  {
    token tok = CovStream::parse_token(scan,end);

    scan = tok.second;

    for(iterator i = tok.first; i != tok.second; ++i)
    {
      char c = *i;

      if(c == '\n')
	printf("\\n");
      else
	printf("%c", c);
    }

    printf("\n");

  }




}
