#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <pthread.h>
#include <vector>
#include "process.h"
#include "FCFS.h"
#include "PRIORITY_NONP.h"
#include "SJF.h"

using namespace std;

void fcfsTHREAD(vector <Process*> p, int n_p, int c_s) {
  FCFS fcfs_sche(p, n_p, c_s);
  fcfs_sche.execute();
}

void sjfTHREAD(vector <Process*> p, int n_p, int c_s) {
  SJF sjf_sche(p, n_p, c_s);
  sjf_sche.execute();
}

void priorityTHREAD(vector <Process *> p, int n_p, int c_s) {
  PRIORITY prio_sche(p, n_p, c_s);
  prio_sche.execute();
}

// ASSIGN UNIQUE PROCESS FOR EACH THREAD SUBROUTINE
void copyProcess(vector <Process*> th_ps, vector <Process*> *th_pd) {
  for (vector <Process*>::iterator it = th_ps.begin(); it != th_ps.end(); it++) {
    Process *prcs = new Process;
    prcs->p_id = (*it)->p_id;
    prcs->burst_time = (*it)->burst_time;
    prcs->arrival_time = (*it)->arrival_time;
    prcs->priority = (*it)->priority;
    prcs->start_time = (*it)->start_time;
    prcs->completation_time = (*it)->completation_time;
    prcs->turnaround_time = (*it)->turnaround_time;
    prcs->waiting_time = (*it)->waiting_time;
    prcs->response_time = (*it)->response_time;
    th_pd->push_back(prcs);
  }
}

int main() {
  int i, n_prcs, context_switch;
  pthread_t fcsf_th, sjf_th, prio_th;
  thread threads[3];
  vector <Process*> p_th1, p_th2, p_th3;


  //printf("Number of process: ");
  cin >> n_prcs;

  //printf("Context switch units: ",&context_switch);
  cin >> context_switch;

  Process *prcs = new Process;

  for (i = 0;i < n_prcs; i++) {
    prcs->p_id = i + 1;
    cin >> prcs->burst_time >> prcs->arrival_time >> prcs->priority;
    prcs->completation_time = -1;

    p_th1.push_back(prcs);
    prcs = new Process;
  }

  copyProcess(p_th1, &p_th2);
  copyProcess(p_th1, &p_th3);

  threads[0] = thread(fcfsTHREAD, p_th1, n_prcs, context_switch);
  threads[0].join();

  threads[1] = thread(priorityTHREAD, p_th2, n_prcs, context_switch);
  threads[1].join();

  threads[2] = thread(sjfTHREAD, p_th3, n_prcs, context_switch);
  threads[2].join();

  return 0;
}
