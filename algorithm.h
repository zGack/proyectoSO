#include <iostream>
#include <vector>
#include "process.h"

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

using namespace std;

class Algorithm {
  protected:
    int context_switch;
    double total_turnaround_time = 0,
        total_waiting_time = 0,
        total_response_time = 0;

  public:
    void printGantt(Process p[], int n_prcs);
    void printGanttV2(vector <Process*> p, int n_prcs);
    static bool compareArrival(Process *p1, Process *p2);
    static bool comparePID(Process *p1, Process *p2);
    static bool comparePriority(Process *p1, Process *p2);
    static bool compareST(Process *p1, Process *p2);
};

#endif
