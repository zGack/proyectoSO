#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "process.h"
#include "FCFS.h"
#include "PRIORITY_NONP.h"
#include "SJF.h"

using namespace std;

typedef struct p_args {
  Process *processes;
  int n_prcs;
  int context_switch;
} args;

void *fcfsTHREAD(void *tmp) {
  args *prcs = (args *) tmp;
  FCFS fcfs_sche(prcs->processes, prcs->n_prcs, prcs->context_switch);
  fcfs_sche.execute();

  pthread_exit(0);
}

void *sjfTHREAD(void *tmp) {
  args *prcs = (args *) tmp;
  SJF sjf_sche(prcs->processes, prcs->n_prcs, prcs->context_switch);
  sjf_sche.execute();

  pthread_exit(0);
}

void *priorityTHREAD(void *tmp) {
  args *prcs = (args *) tmp;
  PRIORITY prio_sche(prcs->processes, prcs->n_prcs, prcs->context_switch);
  prio_sche.execute();

  pthread_exit(0);
}

int main() {
  int i, n_prcs, context_switch;
  pthread_t fcsf_th, sjf_th, prio_th;
  Process *prcs;

  //printf("Number of process: ");
  cin >> n_prcs;

  prcs = (Process *)malloc(n_prcs * sizeof(Process));

  //printf("Context switch units: ",&context_switch);
  cin >> context_switch;

  for (i = 0;i < n_prcs; i++) {
    prcs[i].p_id = i + 1;
    //printf("\nP[%d] BURST: ",i+1);
    cin >> prcs[i].burst_time >> prcs[i].arrival_time >> prcs[i].priority;
    //printf("BT: %d AT: %d PRIORITY %d\n", prcs[i].burst_time, prcs[i].arrival_time, prcs[i].priority);
    prcs[i].completation_time = -1;
    //printf("P[%d] ARRIVAL TIME: ",i+1);
  }

  args tmp[3];
  tmp[0].processes = prcs;
  tmp[0].n_prcs = n_prcs;
  tmp[0].context_switch = context_switch;
  tmp[1] = tmp[0];
  tmp[2] = tmp[0];

  if (pthread_create(&fcsf_th, NULL, &fcfsTHREAD, &tmp[0]) != 0) {
    printf("FCFS THREAD CREATION ERROR");
    return -1;
  }

  pthread_join(fcsf_th, NULL);

  if (pthread_create(&sjf_th, NULL, &sjfTHREAD, &tmp[1]) != 0) {
    printf("SJF THREAD CREATION ERROR");
    return -1;
  }

  pthread_join(sjf_th, NULL);

  if (pthread_create(&prio_th, NULL, &priorityTHREAD, &tmp[2]) != 0) {
    printf("PRIORITY THREAD CREATION ERROR");
    return -1;
  }

  pthread_join(prio_th, NULL);

  //initializate scheduling algorithms
  /*FCFS fcfs_sche(prcs, n_prcs, context_switch);
  PRIORITY prio_sche(prcs, n_prcs, context_switch);
  SJF sjf_sche(prcs, n_prcs, context_switch);*/

  return 0;
}
