 // COVTOOL -- test coverage analysis tool.
 // Copyright (C) 2002, Lowell Boggs Jr.
 // mailto:lowell.boggs@attbi.com
 
 // This file contains free software.  You can redistribute it
 // and/or modify it under the terms of the GNU General Public License
 // as published by the Free Software Foundation; either version 2, or
 // (at your option) any later version.
 
 // This source code is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.
 
 // Write to the Free Software Foundation, 59 Temple Place - Suite 330,
 // Boston, MA  02111-1307, USA for a copy of the GNU General Public License.
 //
 
 
 //
 // This is the instrumentor for the covtool.exe program.  It parses a
 // C++ source file that has already been through the C preprocessor and
 // adds additional function calls and data declarations such that when your
 // program runs it will make function calls that will create a database
 // indicating which lines of code in your program were executed and which
 // were not.  See covtoolhelper.c for implementations of the datastructures
 // and functions injected by this program.
 //
 // The parser only recognizes the big picture parts of the C++ language.
 // It is a recursive descent parser that knows about namespaces, classes,
 // structs, unions, enums, variable declarations, functions, statements, etc.
 // It does not know about expressions -- a statement is either one of
 // the structured statements (if, while, do, for, switch, case) or it is
 // a sequence of tokens ending in ;.
 //
 // The parser injects a call to CvT_record_line() before the beginning of
 // every executable statement -- and one extra at the beginning of every
 // function.  See function 'instrument_line()' below.
 //
 // Also, you can instruct the parser to skip all files beginning with a
 // given prefix.  Normally the prefix will be just '/' because you will
 // probably want to ignore the C++ source header files -- since they will
 // detract from your code test coverage numbers and you don't want to have to
 // write full tests for them.  See the -skip option.
 //
 #include <fstream>
 #include <covstream.h>
 #include <ctype.h>
 #include <map>
 #include <set>
 #include <string>
 #include <list>
 #include <vector>
 #include <stdlib.h>
 
 // the following block must not be separated, it defines the
 // version string
 char const*
 #include "covtool_version"
 ;
 // do not separate this from the #include of covtool_version!
 
 typedef CovStream::iterator iterator;
 typedef CovStream::token    token;
 
 int line_number=1;
 int depth=0;
 
 char const *parse_state[1000];
 
 
 #ifdef DEBUGGING
     static char buffer[256];
     static char *current_token = buffer;
   #define DEBUG_FLUSH()  cout.flush()
 #else
   #define DEBUG_FLUSH()
 #endif
 
 token get_token(iterator start, iterator end);
 
 // the names of runtime objects injected during instrumentation
 
 char const *rt_file_name_table    = "__CvT__file_name____";
 char const *rt_record_line        = "__CvT__record_line____";
 char const *rt_logged_lines_table = "__CvT__logged_lines___";
 char const *rt_instrumented_lines = "__CvT__instrumented_lines___";
 
 char const *rt_module_info        =
 "struct __CvT__module_info____                                   \n"
 "{                                                               \n"
 "    char const **file;                                          \n"
 "    int files;                                                  \n"
 "    void const **str;   // string version of file names above   \n"
 "    int *  line;  // pairs of ints stored here                  \n"
 "                  // the first is the index into file           \n"
 "                  // the second is the line number in that file \n"
 "    int lines;    // count of PAIRS not ints at line            \n"
 "                                                                \n"
 "    int struct_size;    // validates this struct                \n"
 "    int * inst;   // counts of instrumented lines per file      \n"
 "                                                                \n"
 "    void construct();                                           \n"
 "                                                                \n"
 "    __CvT__module_info____(char const **f, int fs,              \n"
 "                           int   *l, int ls,                    \n"
 "                           int *i                               \n"
 "                          )                                     \n"
 "    : file(f), files(fs), str(0), line(l), lines(ls),           \n"
 "      struct_size(sizeof(__CvT__module_info____)), inst(i)      \n"
 "    {                                                           \n"
 "      construct();                                              \n"
 "    }                                                           \n"
 "                                                                \n"
 "    ~__CvT__module_info____();                                  \n"
 "                                                                \n"
 "};\n";
 
 
 // The instrument time variables keeping track of files, lines, etc
 
 typedef map<string,int>          Files_t;
 typedef Files_t::iterator        Files_Iterator_t;
 typedef list<Files_t::iterator>  Ordered_Files_t;
 typedef set< pair<int,int> >     Logged_Lines_t;
 
 bool                             instrumenting=false;
 bool                             skipping=false;
 string                           skip_prefix;  // one for the moment
 list<string>                     skip_prefixes;
 Files_t                          files;
 Ordered_Files_t                  files_in_order;
 token                            current_file_name;
 string                           current_file_string;
 int                              current_file_number;
 Logged_Lines_t                   logged_lines;
 
 bool is_skipped(token filename)
+{
+  list<string>::iterator il;
 
+  for(il = skip_prefixes.begin(); il != skip_prefixes.end(); ++il)
   {
+    string const &skipped_path = *il;
 
+    iterator               ifl = filename.first;
+    string::const_iterator ipn  = skipped_path.begin();
 
+    while(*ifl == *ipn              &&
          ifl != filename.second    &&
          ipn != skipped_path.end()
         )
     {
+      ++ifl;
+      ++ipn;
     }
 
+    if(ipn == skipped_path.end())
     {
+      return true;
     }
   }
 
+  return false;
 
 }
 
 
 void record_current_file_name() // records 'current_file_name'
+{
 
+  iterator i = current_file_name.first;
 
+  current_file_string.resize(0);
 
+  while(i != current_file_name.second)
   {
+    current_file_string += *i++;
   }
 
   // cerr << "filename string is '" << current_file_string << endl;
 
+  Files_Iterator_t tmp = files.find(current_file_string);
 
+  if(tmp == files.end())
   {
     // file not already added
 
     //cerr << "it is new!" << endl;
 
+    current_file_number = files.size();
 
+    map<string,int>::value_type v(current_file_string, current_file_number);
 
+    Files_Iterator_t tmp = files.insert(v).first;
 
+    files_in_order.push_back(tmp);
 
   }
   else
   {
     // cerr << "it is old!" << endl;
+    current_file_number = tmp->second;
   }
 
 
 }
 
 
 void instrument_beginning()
+{
+  if(!instrumenting)
+    return;
 
+  cout << "# 1 \"Instrumentation code beginning\"" << endl;
 
+  cout << rt_module_info << endl;
 
+  cout << "static __CvT__module_info____* __CvT_miT;" << endl;
 
+  cout << "extern void "
        << rt_record_line
        << "(__CvT__module_info____ const*, int,int);"
        << endl;
 
+  cout.flush();
 }
 
 void instrument_ending()
+{
+  if(!instrumenting)
+    return;
 
+  cout << "# 1 \"Instrumentation code ending\"" << endl;
 
+  cout << "static char const *" << rt_file_name_table << "[]={" << endl;
 
+  int instrumented_files = files_in_order.size();
 
+  if(instrumented_files == 0)
-    instrumented_files=1;
 
+  vector<int> instrumented_lines(instrumented_files,0);
 
+  Ordered_Files_t::iterator first, last;
 
+  for(first = files_in_order.begin(),
       last  = files_in_order.end();
       first != last;
       ++first
      )
   {
+    Files_Iterator_t i = *first;
 
+    cout << CovStream::fullname(i->first) << "," << endl;
   }
 
+  cout << "0};" << endl;
 
+  Logged_Lines_t::iterator ll_first, ll_last;
 
+  ll_first = logged_lines.begin();
+  ll_last  = logged_lines.end();
 
+  cout << "static int " << rt_logged_lines_table << "[] = {" << endl;
 
+  while(ll_first != ll_last)
   {
+    Logged_Lines_t::value_type const &r = *ll_first++;
 
+    ++instrumented_lines[r.first];  // for each ref, increment the
        			    // count of instrumented lines
        			    // associated with the corresponding
        			    // file
        
+    cout << r.first << "," << r.second << "," << endl;
 
   }
 
+  cout << "0};" << endl;
 
+  cout << "static int " << rt_instrumented_lines << "[]={" << endl;
   {
+    vector<int>::iterator i;
 
+    for(i=instrumented_lines.begin();
        i != instrumented_lines.end();
        ++i
        )
     {
+      cout << *i << "," << endl;
     }
   }
+  cout << "0};" << endl;
 
+  cout << "static __CvT__module_info____"
        << endl
        << "__CvT_miTBODY("
        << endl
        << "              "
        <<  rt_file_name_table
        <<    ","
        << endl
        <<     "              sizeof("
        <<     rt_file_name_table
        <<     ")/sizeof(char*) -1,"
        << endl << "              "
        <<  rt_logged_lines_table
        <<    ","
        <<    endl
        <<    "              (sizeof("
        <<    rt_logged_lines_table
        <<    ")/sizeof(int) -1) / 2"
        << endl
        << "              ," << rt_instrumented_lines
        << ");"
        << endl;
 
+  cout <<
    "static __CvT__module_info____* __CvT_miTINIT = __CvT_miT = &__CvT_miTBODY;"
    << endl;
 
 
+  cerr.flush();  // not sure why this needed but without these
+  cout.flush();  // too lines, icov.exe crashes in static destruction.
        	 // Could be a bug in my code that will get fixed
        	 // later, or could be a subtle issues in the
        	 // destruction of objects in the covtoolhelper.c
        
 }
 
 void instrument_line()
+{
+  if(!instrumenting)
+    return;
 
+  if(skipping)
-    return;
 
+  pair<int,int> line_ref(current_file_number, line_number);
 
+  Logged_Lines_t::iterator i = logged_lines.find(line_ref);
 
+  if(i == logged_lines.end())
   {
+    logged_lines.insert(line_ref);
 
+    cout << rt_record_line
         << "(__CvT_miT,"
         << current_file_number
         << ","
         << line_number
         << ");" ;
   }
 
 }
 
 token process_declaration(token t, iterator end);
 
 int main(int argc, char **argv)
-{
 #ifdef COVTOOL_INST
-  extern void CvT_StartRecording____();
-  CvT_StartRecording____();
 
 #endif
 
+  --argc;
+  ++argv;
 
+  string dash_instrument("-instrument");
+  string dash_skip("-skip");
+  string dash_v("-v");
 
+  while(argc)
   {
+    if(dash_v == *argv)
     {
-      cout << covtool_version << endl;
-      exit(1);
     }
     else
+    if(dash_instrument == *argv)
     {
+      instrumenting = true;
     }
     else
+    if(dash_skip == *argv)
     {
+      --argc;
+      ++argv;
 
+      skip_prefixes.push_back(string("\"") + *argv);
 
     }
     else
     {
-      cerr << "covtool:  invalid command line parameter '" << *argv << endl;
-      exit(1);
     }
 
+    if(argc)
     {
+      --argc;
+      ++argv;
     }
   }
 
+  instrument_beginning();
 
+  CovStream s(stdin);
 
+  iterator end  = s.end();
 
+  parse_state[0] = "file";
 
+  token t = get_token(s.begin(), s.end());
 
+  do
   {
+    t = process_declaration(t, end);
   }
   while(t.first != end);
 
 
+  cout << endl;
 
+  instrument_ending();
 
 
 }
 
 void output_token(iterator start, iterator end);
 
 token get_token(iterator start, iterator end)
+{
   //
   // parse tokens and handle default behaviors thereof.
   // All parsing algorithms, except main(), assume that
   // the first token to be parsed has already been gathered
   // and is presented as the first thing to look at.  It will
   // not have been copied to stdout yet though.
   //
 
+  token t(start,start);
 
+  static int first_time=1;
 
+  if(first_time)
   {
+    first_time = 0;
 
+    if(!instrumenting)
     {
+      cout << "/*"
           << parse_state[depth]
           << "\t"
           << 1
           << "\t:"
           << depth
           << "\t*/";
        
       DEBUG_FLUSH();
     }
   }
 
+  for(;;)
   {
 
+    t = CovStream::parse_token(t.second,end);
 
 
 #ifdef DEBUGGING
 
     // so I can the stupid token in the debugger!
 
 
     {
        char *scan = buffer;
        iterator input = t.first;
        
        while(input != t.second)
          *scan++ = *input++;
        
        *scan = 0;
        
     }
 
 
 #endif
 
 
+    if(t.first == end)
+      break;
 
+    if(*t.first == '\n')
     {
+      ++line_number;
 
+      if(!instrumenting)
       {
+       cout << endl
             << "/*"
             << parse_state[depth]
             << "\t"
             << line_number
             << "\t:"
             << depth
             << "\t*/";
        
        DEBUG_FLUSH();
       }
       else
+       cout << endl;
     }
     else
+    if(*t.first == '#')
     {
+      output_token(t.first, t.second);    // the #
 
+      t = CovStream::parse_token(t.second,end);  // the line number
 
+      if(t.first == end)
-       break;  // wierd stuff at end of file
        
        
        
+      output_token(t.first, t.second);
 
+      if( isdigit(*t.first) )
       {
        // this is a line number pragma
        
+       char buffer[256];
        
+       iterator scan = t.first;
        
+       char *cp = buffer;
        
+       while(scan != t.second)
+         *cp++ = *scan++;
        
+       *cp=0;
        
+       sscanf(buffer, "%d", &line_number);
        
+       t = CovStream::parse_token(t.second, end);  // the filename
        
+       if(t.first != end && *t.first != '\n')
+         output_token(t.first, t.second);
        
+       current_file_name = t;
        
+       record_current_file_name();
        
+       skipping = is_skipped(t);
        
        
+       while(t.first != end && *t.first != '\n')
        {
+         t = CovStream::parse_token(t.second, end);
        
+         if(t.first != end && *t.first != '\n')
+           output_token(t.first, t.second);
        }
 
+       if(!instrumenting)
        {
+         cout << endl
               << "/*"
               << parse_state[depth]
               << "\t"
               << line_number
               << "\t:"
               << depth
               << "\t*/";
          DEBUG_FLUSH();
        }
        else
+         cout << endl;
        
       }
       else
       {
        // #pragma or other such nonesene
        
+       do
        {
+         t = get_token(t.second, end);
+         output_token(t.first, t.second);
        }
        while(t.first != end && *t.first != ';');
        
       }
 
     }
     else
     {
+      break;
     }
 
   }
 
 
+  return t;
 
 }
 
 void output_token(iterator start, iterator end)
+{
+  while(start != end) cout << *start++;
+  cout << " ";
 
   DEBUG_FLUSH();
 
 }
 
 bool compare_token(iterator first, iterator last, char const *s)
+{
+  while(first != last && *s && *first == *s)
   {
+    ++first;
+    ++s;
   }
 
+  if(first == last && *s == 0)
+    return true;
 
+  return false;
 
 }
 
 token process_class     (token start, iterator end, char const *scope="class");
 token process_enum      (token start, iterator end);
 token process_template  (token start, iterator end);
 token process_typedef   (token start, iterator end);
 token process_function  (token start, iterator end);
 
 token process_parenthetical(token t, iterator end);
 token process_statement    (token t, iterator end);
 
 token process_declaration(token t, iterator end)
+{
   //
   // process C++ declarations by copying them to stdout
   // and add instrumentation as needed.
 
+  if(t.first == end || *t.first == ';' || *t.first == '}')
+    output_token(t.first,t.second);
   else
   {
 
+    if(compare_token(t.first, t.second, "extern"))
     {
+      token save = t;
 
+      t = get_token(t.second, end);
 
+      if(t.first != end && *t.first == '"')
       {
+       output_token(save.first, save.second);
+       output_token(t.first, t.second);
        
+       t = get_token(t.second, end);
        
+       if(t.first != end)
        {
+         if(*t.first == '{')
          {
+            ++depth; parse_state[depth]="extrn";
        
+            output_token(t.first, t.second);
        
+            t = get_token(t.second, end);
+            do
             {
+              t = process_declaration(t, end);
             }
             while(t.first != end && *t.first != '}');
        
+            output_token(t.first, t.second);
        
+            --depth;
        
+            t = get_token(t.second, end);
        
+            return t;
        
        
          }
          else
          {
+           return process_declaration(t,end);
          }
        }
       }
       else
       {
+       output_token(save.first, save.second);
+       return process_declaration(t,end);
       }
 
 
     }
     else
+    if(compare_token(t.first, t.second, "struct") ||
        compare_token(t.first, t.second, "class")  ||
        compare_token(t.first, t.second, "union")  ||
        compare_token(t.first, t.second, "namespace")
       )
     {
+      char const *id="class";
 
+      if(*t.first == 's')
+       id = "strct";
       else
+      if(*t.first == 'u')
+       id = "union";
       else
+      if(*t.first == 'n')
+       id = "namsp";
 
+      return process_class(t, end,id);
     }
     else
+    if(compare_token(t.first, t.second, "enum") )
     {
+      return process_enum(t, end);
     }
     else
+    if(
        compare_token(t.first, t.second, "public")    ||
        compare_token(t.first, t.second, "private")   ||
        compare_token(t.first, t.second, "protected")
       )
     {
       // eat the class section separators
 
+      output_token(t.first, t.second);
+      t = get_token(t.second, end);
+      output_token(t.first, t.second);
+      return get_token(t.second, end);
     }
     else
+    if(compare_token(t.first, t.second, "template") )
     {
+      return process_template(t, end);
     }
     else
+    if(compare_token(t.first, t.second, "namespace") )
     {
-      return process_class(t, end, "namsp");
     }
     else
+    if(compare_token(t.first, t.second, "catch") )
     {
+      output_token(t.first, t.second);
+      t = get_token(t.second, end);
 
+      t = process_parenthetical(t, end);
 
+      return process_statement(t,end);
 
     }
     else
+    if(compare_token(t.first, t.second, "typedef") ||
        compare_token(t.first, t.second, "using")
       )
     {
+      return process_typedef(t, end);
     }
     else
+    if(isalnum(*t.first) || *t.first == '_')
     {
+      return process_function(t,end);
     }
     else
     {
+      output_token(t.first,t.second);
     }
   }
 
+  return get_token(t.second, end);
 }
 
 token process_class(token t, iterator end, char const *scope)
+{
+  output_token(t.first, t.second);   // class, struct, union, etc
 
   // scan until the '{' or the ';'
 
+  while(t.first != end)
   {
+    t = get_token(t.second,end);
 
+    if(t.first == end || *t.first == ';' || *t.first == '{')
+      break;
 
+    output_token(t.first, t.second);
   }
 
+  if(t.first != end && *t.first != ';')
   {
     // process class body. Output the { and get the next token
 
+    output_token(t.first, t.second);
+    ++depth; parse_state[depth] = scope;  // usually class but maybe namespace
 
+    t = get_token(t.second,end);
 
+    while(t.first != end && *t.first != '}')
     {
 
+      t = process_declaration(t, end);  // prints the trailing '}' if any
 
     }
 
+    output_token(t.first, t.second);
+    --depth;
+    t = get_token(t.second, end);
 
 
   }
 
 
+  return t;
 
 }
 
 
 token process_enum(token t, iterator end)
+{
+  output_token(t.first, t.second);
 
+  while(t.first != end)
   {
+    t = get_token(t.second,end);
 
+    output_token(t.first, t.second);
 
+    if(t.first == end)
-      break;
 
+    if(*t.first == ';' )
-      return get_token(t.second, end);
 
+    if(*t.first == '{' )
+      break;
 
   }
 
+  if(t.first != end)
   {
+    ++depth; parse_state[depth]="enum";
 
+    while(t.first != end)
     {
+      t = get_token(t.second,end);
 
+      output_token(t.first, t.second);
 
+      if(t.first == end || *t.first == '}')
       {
+       t = get_token(t.second, end);
+       break;
       }
     }
+    --depth;
   }
 
 
+  return t;
 
 }
 
 
 token process_template(token t, iterator end)
+{
+  output_token(t.first, t.second);
 
+  int angledepth = 0;
 
+  while(t.first != end)
   {
+    t = get_token(t.second,end);
 
+    output_token(t.first, t.second);
 
+    if(t.first == end)
-      break;
 
+    if(compare_token(t.first, t.second, "<>"))
+      return process_declaration(get_token(t.second, end), end);
 
+    if(*t.first == '<')
+      ++angledepth;
     else
+    if(*t.first == '>')
     {
+      if(angledepth == 1)
       {
+       token t =  process_declaration(get_token(t.second, end), end);
        
+       return t;
       }
+      --angledepth;
     }
 
   }
 
-  return token(end,end);
 
 }
 
 token process_till_semicolon(token t, iterator end)
 //
 // consume tokens until a semicolon is encountered -- return the
 // token after the semicolon.  Do not walk past '}' -- I forgeet
 // why -- but handle nested {} pairs.
 //
+{
+  int braces=0;
 
+  do
   {
+    t = get_token(t.second, end);
 
+    if(t.first == end)
-      return t;
 
+    if(*t.first == '{')
+      ++braces;
     else
+    if(*t.first == '}')
+      if(braces == 0)
-       return t;
       else
+       --braces;
 
+    output_token(t.first, t.second);
   }
   while(t.first != end && *t.first != ';');
 
+  return get_token(t.second, end);
 
 }
 
 token process_typedef(token t, iterator end)
+{
   // process typedef, namespace, and using statements at file scope
 
+  output_token(t.first, t.second);
 
+  t = get_token(t.second, end);
 
+  if( compare_token(t.first, t.second, "struct") ||
       compare_token(t.first, t.second, "class")  ||
       compare_token(t.first, t.second, "union")
     )
     {
+      return process_class(t,end);
     }
 
+  output_token(t.first, t.second);
 
+  return process_till_semicolon(t, end);
 
 }
 
 
 
 token process_function(token t, iterator end)
+{
   // process function and variable declarations
 
   // copy the type info out and scarf the variable name
   // up to the ()'s.
 
+  output_token(t.first, t.second);
 
+  do
   {
     // handle various wierd syntax cases including a pointer to a
     // function declaration type (*name)(parms)
     // so we have to handle multiple () groups before the 'const' or '='
     // or { that defines what this darn thing is.
 
+    t = get_token(t.second, end);
 
+    if(t.first != end && compare_token(t.first, t.second, "operator") )
     {
       // oops, operators can be '=' and that will screw up the
       // logic of detecting that this is a variable assignment not a
       // function body.
 
+      output_token(t.first, t.second);
 
+      t = get_token(t.second, end);
 
       // we now have the operator being defined but we don't
       // want it to be processed either
 
+      output_token(t.first, t.second);
 
+      t = get_token(t.second, end); // get the paren after the operator
 
 
     }
 
 
+    if(t.first != end && *t.first == '(')
     {
+      t = process_parenthetical(t, end);
 
+      if(t.first != end &&
         compare_token(t.first, t.second, "const")
        )
       {
+       output_token(t.first, t.second);
+       t = get_token(t.second, end);
       }
 
+      if(t.first != end &&
         compare_token(t.first, t.second, "try")
        )
       {
+       output_token(t.first, t.second);
+       t = get_token(t.second, end);
       }
 
 
     }
 
+    output_token(t.first, t.second);
   }
   while(t.first != end   &&
        *t.first != ';'  &&
        *t.first != '='  &&
        *t.first != '{'
        );
 
+  if(t.first == end || *t.first == ';')
+    return get_token(t.second, end);
 
+  if(*t.first == '=' )
+    return  process_till_semicolon(t, end);
 
   // must be a '{'
 
 
+  ++depth; parse_state[depth] = "func";
 
+  instrument_line();
 
 
+  t = get_token(t.second, end);
 
+  while(t.first != end && *t.first != '}')
   {
+    t = process_statement(t, end);
   }
 
+  output_token(t.first, t.second);
 
+  --depth;
 
+  return get_token(t.second, end);
 
 }
 
 token process_if(token t, iterator end);
 token process_while(token t, iterator end);
 token process_do(token t, iterator end);
 token process_for(token t, iterator end);
 token process_switch(token t, iterator end);
 token process_try(token t, iterator end);
 
 token process_statement(token t, iterator end)
+{
+  if(t.first == end)
   {
-    return t;
   }
 
+  if(*t.first == ';')
   {
+    output_token(t.first, t.second);
+    return get_token(t.second, end);
   }
   else
+  if(*t.first == '{')
   {
+    ++depth; parse_state[depth] = "block";
 
+    output_token(t.first, t.second);
+    t = get_token(t.second,end);
 
+    while( t.first != end && *t.first != '}' )
     {
+      t = process_statement(t,end);
     }
 
+    output_token(t.first, t.second);
 
+    --depth;
 
+    return get_token(t.second, end);
 
   }
   else
+  if(compare_token(t.first, t.second, "if") )
   {
+    instrument_line();
+    return process_if(t, end);
   }
   else
+  if(compare_token(t.first, t.second, "case") )
   {
+    output_token(t.first, t.second);  // case
 
+    do
     {
+      t = get_token(t.second, end);
 
+      output_token(t.first, t.second);  // label
     }
     while(t.first != end && !compare_token(t.first,t.second,":"));
 
+    return process_statement(get_token(t.second, end), end);
   }
   else
+  if(compare_token(t.first, t.second, "default") )
   {
+    output_token(t.first, t.second);  // default
 
+    t = get_token(t.second, end);
 
+    output_token(t.first, t.second);  // :
 
+    return process_statement(get_token(t.second, end), end);
   }
   else
+  if(compare_token(t.first, t.second, "while") )
   {
+    instrument_line();
+    return process_while(t, end);
   }
   else
+  if(compare_token(t.first, t.second, "do") )
   {
+    instrument_line();
+    return process_do(t, end);
   }
   else
+  if(compare_token(t.first, t.second, "for") )
   {
+    instrument_line();
+    return process_for(t, end);
   }
   else
+  if(compare_token(t.first, t.second, "switch") )
   {
+    instrument_line();
+    return process_switch(t, end);
   }
   else
+  if(compare_token(t.first, t.second, "enum") )
   {
-    instrument_line();
-    return process_enum(t, end);
   }
   else
+  if(compare_token(t.first, t.second, "try") )
   {
+    instrument_line();
+    return process_try(t, end);
   }
   else
+  if(compare_token(t.first, t.second, "typedef") ||
      compare_token(t.first, t.second, "using")   ||
      compare_token(t.first, t.second, "namespace")
     )
   {
+    return process_typedef(t, end);
   }
   else
+  if(compare_token(t.first, t.second, "class") ||
      compare_token(t.first, t.second, "struct")||
      compare_token(t.first, t.second, "union")
     )
   {
-    instrument_line();
-    return process_declaration(t, end);
   }
   else
   {
+    instrument_line();
 
 
 #if 0
     t = process_typedef(t, end);
 #else
+    output_token(t.first, t.second);
+    t = process_till_semicolon(t,end);
 
 #endif
 
+    return t;
   }
 }
 
 
 token process_parenthetical(token t, iterator end)
+{
   // scoop up a parenthesized expression and return the first
   // token after the trailing ).
 
+  output_token(t.first, t.second);
 
+  t = get_token(t.second, end);
 
+  int pdepth=1;
 
+  for(;;)
   {
+    if(t.first == end)
-      break;
 
 
+    if(*t.first == ')')
     {
+      --pdepth;
 
+      if(pdepth == 0)
+       break;
 
     }
     else
+    if(*t.first == '(')
     {
+      ++pdepth;
     }
 
+    output_token(t.first, t.second);
+    t = get_token(t.second, end);
 
   }
 
+  output_token(t.first, t.second);
+  return get_token(t.second, end);
 
 }
 
 
 token process_if(token t, iterator end)
+{
   //handle 'if' statements and the else clause
 
+  output_token(t.first, t.second);
 
+  t = process_parenthetical(get_token(t.second, end),end);
 
+  if(instrumenting) cout << "{";
 
+  t = process_statement(t, end);
 
+  if(instrumenting) cout << "}";
 
+  if(compare_token(t.first, t.second, "else"))
   {
+     output_token(t.first, t.second);
 
+     if(instrumenting) cout << "{";
+     t = process_statement(get_token(t.second, end), end);
+     if(instrumenting) cout << "}";
   }
 
+  return t;
 
 }
 
 token process_while(token t, iterator end)
+{
   //handle 'while' statements
 
+  output_token(t.first, t.second);
 
+  t = process_parenthetical(get_token(t.second, end),end);
 
+  if(instrumenting) cout << "{";
+  t = process_statement(t, end);
+  if(instrumenting) cout << "}";
 
+  return t;
 
 }
 
 token process_do(token t, iterator end)
+{
   //handle 'do' statements
 
+  output_token(t.first, t.second);  // print do, get first token of statement
 
+  if(instrumenting) cout << "{";
+  t = process_statement(get_token(t.second,end), end);
+  if(instrumenting) cout << "}";
 
   // t should be 'while' here
 
+  output_token(t.first, t.second);
 
+  t = process_parenthetical(get_token(t.second, end),end);
+  return t;
 
 }
 
 token process_for(token t, iterator end)
+{
   //handle for statements
 
+  output_token(t.first, t.second);
 
+  t = process_parenthetical( get_token(t.second, end), end);
 
+  if(instrumenting) cout << "{";
 
+  t =  process_statement(t, end);
 
+  if(instrumenting) cout << "}";
 
+  return t;
 
 
 
 }
 
 token process_switch(token t, iterator end)
+{
   //handle switch statements
 
+  output_token(t.first, t.second);
 
+  t = process_parenthetical( get_token(t.second, end), end);
 
+  return process_statement(t, end);
 
 }
 
 
 token process_try(token t, iterator end)
+{
+  output_token(t.first, t.second);
 
+  t = process_statement(get_token(t.second, end), end);
 
+  while(t.first != end && compare_token(t.first, t.second, "catch"))
   {
+    output_token(t.first, t.second);  // catch
 
+    t = process_parenthetical(get_token(t.second, end), end);
 
+    t = process_statement(t, end);
 
   }
 
+  return t;
 
 }
 
