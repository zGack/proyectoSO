#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "FCFS.h"
#include "PRIORITY_NONP.h"

using namespace std;

int main() {
  int i, n_prcs, context_switch;
  Process *prcs;

  //printf("Number of process: ");
  cin >> n_prcs;

  prcs = (Process *)malloc(n_prcs * sizeof(Process));

  //printf("Context switch units: ",&context_switch);
  cin >> context_switch;
  printf("Context switch units: %d\n", context_switch);

  for (i = 0;i < n_prcs; i++) {
    prcs[i].p_id = i + 1;
    //printf("\nP[%d] BURST: ",i+1);
    cin >> prcs[i].burst_time >> prcs[i].arrival_time >> prcs[i].priority;
    //printf("BT: %d AT: %d PRIORITY %d\n", prcs[i].burst_time, prcs[i].arrival_time, prcs[i].priority);
    prcs[i].completation_time = -1;
    //printf("P[%d] ARRIVAL TIME: ",i+1);
  }

  //initializate scheduling algorithms
  FCFS fcfs_sche(prcs, n_prcs, context_switch);
  fcfs_sche.execute();
  PRIORITY prio_sche(prcs, n_prcs, context_switch);
  //prio_sche.execute();

  return 0;
}
