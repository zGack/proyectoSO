compile:
	g++ -o main scheduling.cpp FCFS.cpp algorithm.cpp

test_run:
	./main < in

run:
	./main 

clear:
	rm -f ./main
