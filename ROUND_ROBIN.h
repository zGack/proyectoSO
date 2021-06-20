#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include "process.h"
#include "algorithm.h"

#ifndef ROUNDR_H_
#define ROUNDR_H_

using namespace std;

class ROUNDR : public Algorithm {
  protected:
    vector <Process*> prcs;
    int n_prcs;

  public:
    ROUNDR(vector <Process*> prcs, int n_prcs, int c_s);
    void execute();
    void calculateWT();
    void calculateTAT();
    void calculateRT();

};
#endif
