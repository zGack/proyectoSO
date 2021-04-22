#include <iostream>
#include "process.h"

#ifndef GANTT_H_
#define GANTT_H_

class Gantt {
  private:
    int n_prcs;

  public:
    void printGantt(Process p[]);
};

#endif
