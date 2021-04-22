#include <iostream>
#include "process.h"

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

class Algorithm {
  protected:
    int total_turnaround_time = 0,
        total_waiting_time = 0,
        total_response_time = 0;

  public:
    void printGantt(Process p[], int n_prcs);
};

#endif
