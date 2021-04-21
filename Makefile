compile:
	g++ -o main scheduling.cpp FCFS.cpp

test_run:
	./main < in

run:
	./main 

clear:
	rm -f ./main
