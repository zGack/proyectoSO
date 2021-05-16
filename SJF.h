#include <iostream>
#include <algorithm>
#include "process.h"
#include "algorithm.h"

using namespace std;

#ifndef SJF_H_
#define SJF_H_

class SJF : public Algorithm{  
  private:
    Process *prcs;
    int n_prcs,
        total_waiting_time = 0,
        total_response_time = 0,
        total_turnaround_time = 0,
        tCambios[2000],
        nCambios[2000],
        cambios = 0,
        chan;

  public:
    SJF(Process prcs[], int n_prcs, int ctx);
    void execute();
    void calculateWT();
    void calculateTAT();
    void calculateRT();
    static bool compareArrival(Process p1, Process p2);
    static bool comparePID(Process p1, Process p2);
    void printGanttSJF(Process p[], int n_prcs);
};

#endif