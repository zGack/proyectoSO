#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include "process.h"
#include "algorithm.h"

#ifndef SJF2_H_
#define SJF2_H_
#define QUANTUM 1

using namespace std;

class SJF2 : public Algorithm{
  protected:
    vector <Process*> prcs;
    int n_prcs;

  public:
    SJF2(vector <Process*> prcs, int n_prcs, int c_s);
    void execute();
    void calculateWT();
    void calculateTAT();
    void calculateRT();

};
#endif
