all::   test1  test2
tests:: run_test1 run_test2

test1:
	../cov++ -skip /usr -c -Ddefine1 -Ddefine2 "-DI_STRING=\" a b c \"" -I.. test1.c
	../cov++ -o test1 test1.o
	
run_test1: test1
	test1 >test1.out
	diff test1.expect test1.out
	../covannotate.exe test1.c *.covexp
	@echo "test1 passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"

test2:
	cp test1.c test2.cxx
	../cov++  -EXT .cxx .cpp -skip /usr -c -Ddefine1 -Ddefine2 "-DI_STRING=\" a b c \"" -I.. test2.cxx
	../cov++ -o test2 test2.o

run_test2: test2
	test2 >test2.out
	diff test1.expect test2.out
	../covannotate.exe test2.cxx *.covexp
	@echo "test2 passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"

clean::
	rm -fr test1.o test1.c++ *.covexp merge*.db test1 test2 test2.o  test2.cxx *.out *.cpp
	
junk.i: junk.c ../covtool.exe
	g++ -E "-D__extension__=" "-D__attribute__(x)=" junk.c >$@ 
