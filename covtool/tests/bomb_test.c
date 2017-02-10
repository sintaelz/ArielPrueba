#include <iostream>
#include <fstream>
using namespace std;
#include <covstream.h>

#define cs_iterator         CovStream::iterator
#define token               CovStream::token

token process_declaration(cs_iterator start, cs_iterator end);

int main()
{
  CovStream s(stdin);

  cs_iterator scan = s.begin();
  cs_iterator end  = s.end();

  while(scan != end)
  {
    token tok = process_declaration(scan,end);

    scan=tok.second;
  }

  cout << endl;

}

int line_number=1;

token Lex(cs_iterator start, cs_iterator end)
{
  //
  // parse tokens and handle default behaviors thereof
  //

  static int first_time=1;

  if(first_time)  first_time=0, cout << "/*1*/";


  token t = CovStream::parse_token(start,end);

  while(t.first != end && *t.first == '\n')
  {
    ++line_number;
    cout << endl << "/*" << line_number << "*/";
    t = CovStream::parse_token(t.second,end);

  }


  return t;

}

token process_declaration(cs_iterator start, cs_iterator end)
{
  //
  // process C++ declarations by copying them to stdout
  //

  token t = Lex(start,end);

  for(cs_iterator i = t.first; i != t.second; cout << *i++);
  cout << " ";

  return t;
}

