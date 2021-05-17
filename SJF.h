#include <iostream>
#include <algorithm>
#include <vector>
#include "process.h"
#include "algorithm.h"

using namespace std;

#ifndef SJF_H_
#define SJF_H_

class SJF : public Algorithm{  
  private:
    vector <Process*> prcs;
    int n_prcs,
        tCambios[2000],
        nCambios[2000],
        cambios = 0,
        chan;

  public:
    SJF(vector <Process*> prcs, int n_prcs, int ctx);
    void execute();
    void calculateWT();
    void calculateTAT();
    void calculateRT();
    void printGanttSJF(vector <Process*> p, int n_prcs);
};

#endif
