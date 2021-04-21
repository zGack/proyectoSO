#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "FCFS.h"

using namespace std;

int main() {
  int i, n_prcs;
  Process *prcs;

  //printf("Number of process: ");
  cin >> n_prcs;

  prcs = (Process *)malloc(n_prcs * sizeof(Process));

  for (i = 0;i < n_prcs; i++) {
    prcs[i].p_id = i + 1;
    //printf("\nP[%d] BURST: ",i+1);
    cin >> prcs[i].burst_time >> prcs[i].arrival_time;
    //printf("P[%d] ARRIVAL TIME: ",i+1);
  }

  //initializate scheduling algorithms
  FCFS fcfs_sche(prcs, n_prcs);

  fcfs_sche.execute();

  return 0;
}
