#include <iostream>
#include <algorithm>
#include <vector>
#include "process.h"
#include "algorithm.h"

#ifndef FCFS_H_
#define FCFS_H_

using namespace std;

class FCFS : public Algorithm{
  protected:
    vector <Process*> prcs;
    int n_prcs;

  public:
    FCFS(vector <Process*> prcs, int n_prcs, int c_s);
    void execute();
    void calculateWT();
    void calculateTAT();
    void calculateRT();
};

#endif
