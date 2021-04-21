#include <iostream>
#include <algorithm>
#include "process.h"

#ifndef FCFS_H_
#define FCFS_H_

class FCFS {
  private:
    Process *prcs;
    int n_prcs,
        total_waiting_time = 0,
        total_response_time = 0,
        total_turnaround_time = 0;

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
