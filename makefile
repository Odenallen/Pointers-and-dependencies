


for_each:
	clear
	g++ foreach.cpp -o foreach && valgrind ./foreach 
smart_ptr:
	clear
	g++ smartptr.cpp -o ptr && valgrind ./ptr 

circdep:
	clear
	g++ circdep.cpp -o circdep && valgrind ./circdep


Deleter:
	g++ deleter.cpp -o del && valgrind ./del 