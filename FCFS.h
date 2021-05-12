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
    FCFS(Process prcs[], int n_prcs, int c_s);
    void execute();
    void calculateWT();
    void calculateTAT();
    void calculateRT();
};

#endif
