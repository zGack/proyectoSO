#include <iostream>
#include <algorithm>
#include "process.h"
#include "algorithm.h"

#ifndef FCFS_H_
#define FCFS_H_

class FCFS : public Algorithm{
  protected:
    Process *prcs;
    int n_prcs;

  public:
    FCFS(Process prcs[], int n_prcs);
    void execute();
    void calculateWT();
    void calculateTAT();
    void calculateRT();
    static bool compareArrival(Process p1, Process p2);
    static bool comparePID(Process p1, Process p2);
};

#endif
