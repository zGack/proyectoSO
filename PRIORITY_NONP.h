#include <iostream>
#include <queue>
#include <algorithm>
#include "process.h"
#include "algorithm.h"

#ifndef PRIORITY_H_
#define PRIORITY_H_
#define QUANTUM 1

class PRIORITY : public Algorithm{
  protected:
    Process *prcs;
    int n_prcs;

  public:
    PRIORITY(Process prcs[], int n_prcs, int c_s);
    void execute();
    void calculateWT();
    void calculateTAT();
    void calculateRT();

};
#endif
