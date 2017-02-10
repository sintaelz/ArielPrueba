


Now run make tests



cd tests; make tests
make[1]: Entering directory `/home/lboggs/projects/covtool/tests'
Using ../covtool.exe for instrumentation
g++ -E  -I. -I/usr/include/g++ -I.. ../bomb.c >bomb.i
g++ -o bomb_test.o  -O2 -Wall -pedantic -I. -I/usr/include/g++ -I.. -fpermissive -c bomb_test.c
g++ -o bomb_test.exe bomb_test.o ../covlib.a
bomb_test.exe <bomb.i | sed -e 's#/\*[^/]*/##g' -e 's/ //g' >bomb.out
expand bomb.i | sed -e 's/ //g'  >bomb.j
diff -Bbhw bomb.j bomb.out
rm -f bomb.diff bomb.i bomb.j bomb.out
bomb_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
g++ -o token_test.o  -O2 -Wall -pedantic -I. -I/usr/include/g++ -I.. -fpermissive -c token_test.c
g++ -o token_test.exe token_test.o ../covlib.a
token_test.exe <token_test.in >token_test.out
file size is 68
diff token_test.expect token_test.out
rm -f token_test.out
token_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
../covtool.exe <covtest.in >covtest.out
diff covtest.expect covtest.out
rm -f covtest.out
covtest passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
g++ "-D__extension__=" "-D__attribute__(X)=" -E  -I. -I/usr/include/g++ -I.. simple.c >simple.i
../covtool.exe -instrument -skip / <simple.i >simple_test.c
g++ -g -o simple_test.exe simple_test.c ../covtoolhelper.o
simple_test.exe
rm simple_test.exe simple.i simple_test.c
simple_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
g++ "-D__extension__=" "-D__attribute__(X)=" -E  -I. -I/usr/include/g++ -I.. hard.c >hard.i
../covtool.exe -instrument <hard.i >hard_test.c
g++ -g -o hard_test.exe hard_test.c ../covtoolhelper.o
hard_test.exe
crapjunk
rm hard_test.exe hard.i hard_test.c
hard_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
../covmerge.exe aggregation_test.in >aggregation_test.out
diff aggregation_test.expect aggregation_test.out
aggregation_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
../covmerge.exe data_base_1.covdb data_base_2.covdb data_base_3.covdb \
	     >merge_test.out
diff -Bbhw merge_test.expect merge_test.out
rm merge_test.out
merge_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
./all_hdrs ../covtool.exe
Sorry, all hdrs test can't be run -- you don't have /usr/include/g++
all_headers_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
if [ `uname` = 'Linux' ] ; then \
	   make -C astyle INSTRUMENTATION=1 tests ;\
	 fi
make[2]: Entering directory `/home/lboggs/projects/covtool/tests/astyle'
../../cov++ -skip /usr -EXT .cpp .c++ -Wno-sign-compare -O2 -c ASResource.cpp
../../cov++ -skip /usr -EXT .cpp .c++ -Wno-sign-compare -O2 -c ASBeautifier.cpp
../../cov++ -skip /usr -EXT .cpp .c++ -Wno-sign-compare -O2 -c ASFormatter.cpp
../../cov++ -skip /usr -EXT .cpp .c++ -Wno-sign-compare -O2 -c astyle_main.cpp
astyle_main.cpp: In function 
    bool parseOptions(astyle::
        ASFormatter&, const ITER&, const ITER&, const std::string&):

astyle_main.cpp:169: warning: there are no arguments to 
    parseOption that depend on a template parameter, so a declaration of 
    parseOption must be available

astyle_main.cpp:178: warning: there are no arguments to 
    parseOption that depend on a template parameter, so a declaration of 
    parseOption must be available

astyle_main.cpp:183: warning: there are no arguments to 
    parseOption that depend on a template parameter, so a declaration of 
    parseOption must be available

astyle_main.cpp:188: warning: there are no arguments to 
    parseOption that depend on a template parameter, so a declaration of 
    parseOption must be available
../../cov++ -skip /usr -EXT .cpp .c++ -Wno-sign-compare -O2 -o astyle  ASResource.o ASBeautifier.o ASFormatter.o astyle_main.o
for f in *.cpp *.h ; do astyle <$f ; done >test.out
diff -uBbhw test.expect test.out
astyle function test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
../../covmerge.exe *.covexp >merged.db
for f in *.cpp *.h ; do ../../covannotate.exe $f merged.db >$f.out ; if [ $? != 0 ] ; then exit 1; fi ; done
No instrumented lines found for  /home/lboggs/projects/covtool/tests/astyle/ASResource.cpp
No instrumented lines found for  /home/lboggs/projects/covtool/tests/astyle/astyle.h
No instrumented lines found for  /home/lboggs/projects/covtool/tests/astyle/compiler_defines.h
grep totals: merged.db >totals.out
diff -uBbhw totals.expect totals.out
for f in *.cpp *.h ; do diff -Bbhwu $f.expect $f.out ; if [ $? != 0 ] ; then exit 1; fi ; done
astyle instrumentation test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
make[2]: Leaving directory `/home/lboggs/projects/covtool/tests/astyle'
make[1]: Leaving directory `/home/lboggs/projects/covtool/tests'
cd tests; make icov_test
make[1]: Entering directory `/home/lboggs/projects/covtool/tests'
g++ "-D__extension__=" "-D__attribute__(X)=" -E  -I. -I/usr/include/g++ -I.. ../covtool.c >../covtool.i
g++ -E  -I. -I/usr/include/g++ -I.. -DCOVTOOL_INST ../covtool.c >covtool.j
../covtool.exe -instrument -skip / <covtool.j >icov.c
g++ -g -o icov.exe icov.c ../covlib.a ../covtoolhelper.o
make COVTOOL=icov.exe tests
make[2]: Entering directory `/home/lboggs/projects/covtool/tests'
Using icov.exe for instrumentation
g++ -E  -I. -I/usr/include/g++ -I.. ../bomb.c >bomb.i
bomb_test.exe <bomb.i | sed -e 's#/\*[^/]*/##g' -e 's/ //g' >bomb.out
expand bomb.i | sed -e 's/ //g'  >bomb.j
diff -Bbhw bomb.j bomb.out
rm -f bomb.diff bomb.i bomb.j bomb.out
bomb_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
token_test.exe <token_test.in >token_test.out
file size is 68
diff token_test.expect token_test.out
rm -f token_test.out
token_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
icov.exe <covtest.in >covtest.out
diff covtest.expect covtest.out
rm -f covtest.out
covtest passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
g++ "-D__extension__=" "-D__attribute__(X)=" -E  -I. -I/usr/include/g++ -I.. simple.c >simple.i
icov.exe -instrument -skip / <simple.i >simple_test.c
g++ -g -o simple_test.exe simple_test.c ../covtoolhelper.o
simple_test.exe
rm simple_test.exe simple.i simple_test.c
simple_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
g++ "-D__extension__=" "-D__attribute__(X)=" -E  -I. -I/usr/include/g++ -I.. hard.c >hard.i
icov.exe -instrument <hard.i >hard_test.c
g++ -g -o hard_test.exe hard_test.c ../covtoolhelper.o
hard_test.exe
crapjunk
rm hard_test.exe hard.i hard_test.c
hard_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
../covmerge.exe aggregation_test.in >aggregation_test.out
diff aggregation_test.expect aggregation_test.out
aggregation_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
../covmerge.exe data_base_1.covdb data_base_2.covdb data_base_3.covdb \
	     >merge_test.out
diff -Bbhw merge_test.expect merge_test.out
rm merge_test.out
merge_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
./all_hdrs icov.exe
Sorry, all hdrs test can't be run -- you don't have /usr/include/g++
all_headers_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
if [ `uname` = 'Linux' ] ; then \
	   make -C astyle INSTRUMENTATION=1 tests ;\
	 fi
make[3]: Entering directory `/home/lboggs/projects/covtool/tests/astyle'
for f in *.cpp *.h ; do astyle <$f ; done >test.out
diff -uBbhw test.expect test.out
astyle function test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
../../covmerge.exe *.covexp >merged.db
for f in *.cpp *.h ; do ../../covannotate.exe $f merged.db >$f.out ; if [ $? != 0 ] ; then exit 1; fi ; done
No instrumented lines found for  /home/lboggs/projects/covtool/tests/astyle/ASResource.cpp
No instrumented lines found for  /home/lboggs/projects/covtool/tests/astyle/astyle.h
No instrumented lines found for  /home/lboggs/projects/covtool/tests/astyle/compiler_defines.h
grep totals: merged.db >totals.out
diff -uBbhw totals.expect totals.out
for f in *.cpp *.h ; do diff -Bbhwu $f.expect $f.out ; if [ $? != 0 ] ; then exit 1; fi ; done
astyle instrumentation test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
make[3]: Leaving directory `/home/lboggs/projects/covtool/tests/astyle'
make[2]: Leaving directory `/home/lboggs/projects/covtool/tests'
icov_test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
make[1]: Leaving directory `/home/lboggs/projects/covtool/tests'
cd cov++_test; make tests
make[1]: Entering directory `/home/lboggs/projects/covtool/cov++_test'
../cov++ -skip /usr -c -Ddefine1 -Ddefine2 "-DI_STRING=\" a b c \"" -I.. test1.c
../cov++ -o test1 test1.o
test1 >test1.out
diff test1.expect test1.out
../covannotate.exe test1.c *.covexp
 #if defined(define1) && defined(define2)
 
 #include <read_database.h>
 
 int main()
+{
+  cout << "test1 is running";
+  cout << I_STRING << endl;
 
 
 }
 
 #endif
 
test1 passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
cp test1.c test2.cxx
../cov++  -EXT .cxx .cpp -skip /usr -c -Ddefine1 -Ddefine2 "-DI_STRING=\" a b c \"" -I.. test2.cxx
../cov++ -o test2 test2.o
test2 >test2.out
diff test1.expect test2.out
../covannotate.exe test2.cxx *.covexp
 #if defined(define1) && defined(define2)
 
 #include <read_database.h>
 
 int main()
+{
+  cout << "test1 is running";
+  cout << I_STRING << endl;
 
 
 }
 
 #endif
 
test2 passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
make[1]: Leaving directory `/home/lboggs/projects/covtool/cov++_test'



Now run 'make install' as root



