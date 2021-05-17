compile:
	g++ -pthread -o main scheduling.cpp FCFS.cpp algorithm.cpp PRIORITY_NONP.cpp SJF_NONP.cpp

test_run:
	./main < in

run:
	./main 

clear:
	rm -f ./main

