#include <iostream>
#include <algorithm>
#include <vector>
#include "process.h"
#include "algorithm.h"

using namespace std;

#ifndef PRR_H_
#define PRR_H_
#define QUANTUM 4

class PRR : public Algorithm{  
  private:
    vector <Process*> prcs;
    int n_prcs,
        context_switch;

  public:
    PRR(vector <Process*> prcs, int n_prcs, int ctx);
    void execute();
    void printGanttSJF(vector <Process*> p, int n_prcs);
};

#endif
