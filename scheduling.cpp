#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <pthread.h>
#include <vector>
#include "process.h"
#include "FCFS.h"
#include "PRIORITY_NONP.h"
#include "SJF_NONP.h"
#include "ROUND_ROBIN.h"

using namespace std;

void fcfsTHREAD(vector <Process*> p, int n_p, int c_s) {
  FCFS fcfs_sche(p, n_p, c_s);
  fcfs_sche.execute();
}

void sjfTHREAD(vector <Process*> p, int n_p, int c_s) {
  SJF2 sjf_sche(p, n_p, c_s);
  sjf_sche.execute();
}

void priorityTHREAD(vector <Process *> p, int n_p, int c_s) {
  PRIORITY prio_sche(p, n_p, c_s);
  prio_sche.execute();
}

void roundrTHREAD(vector <Process *> p, int n_p, int c_s) {
  ROUNDR roundr_sche(p, n_p, c_s);
  roundr_sche.execute();
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
    prcs->response_time = (*it)->response_time; th_pd->push_back(prcs);
  }
}

void selectAlgorithm(int opt, vector <Process*> p_base, int n_prcs, int context_switch) {
  int q = 4;
  vector <Process*> p_th1, p_th2, p_th3, p_th4, p_th5;
  thread threads[5];

  switch (opt) {
    case 1:
      copyProcess(p_base, &p_th1);
      threads[0] = thread(fcfsTHREAD, p_th1, n_prcs, context_switch);
      threads[0].join();
      break;
    case 2:
      copyProcess(p_base, &p_th2);
      threads[1] = thread(sjfTHREAD, p_th2, n_prcs, context_switch);
      threads[1].join();
      break;
    case 3:
      copyProcess(p_base, &p_th3);
      threads[2] = thread(priorityTHREAD, p_th3, n_prcs, context_switch);
      threads[2].join();
      break;
    case 4:
      copyProcess(p_base, &p_th4);
      threads[3] = thread(roundrTHREAD, p_th4, n_prcs, context_switch);
      threads[3].join();
      break;
    case 5:
      /*copyProcess(p_th1, &p_th5);
      threads[4] = thread(fcfsTHREAD, p_th5, n_prcs, context_switch);
      threads[4].join();*/
      break;
    default:
      break;
  }
}

void menu(int opt) {

  cout << "\n╔═══════════════════════╗" << endl;
  cout << "║ SCHEDULING ALGORITHMS ║" << endl;
  cout << "╚═══════════════════════╝" << endl;
  cout << "Type an option." << endl;
  cout << "1. FCSF" << endl;
  cout << "2. SJF" << endl;
  cout << "3. PRIORITY" << endl;
  cout << "4. ROUND-ROBIN" << endl;
  cout << "5. PRIORITY-RR" << endl;
  (opt == 1)?(cout << "6. EXECUTE ALL" << endl):(cout << "6. CONTINUE" << endl);
  cout << "> ";

}

int main() {
  int i, n_prcs, context_switch, opt, opt2, q;
  thread threads[5];
  vector <Process*> p_th1, p_th2, p_th3, p_th4, p_th5, p_base;

  printf("Number of process: ");
  cin >> n_prcs;

  printf("Context switch units: ");
  cin >> context_switch;

  Process *prcs = new Process;

  for (i = 0;i < n_prcs; i++) {
    prcs->p_id = i + 1;
    //cin >> prcs->burst_time >> prcs->arrival_time >> prcs->priority;
    printf("\nprocess %d burst time: ",i+1);
    cin >> prcs->burst_time;
    printf("process %d arrival time: ",i+1);
    cin >> prcs->arrival_time;
    printf("process %d priority: ",i+1);
    cin >> prcs->priority;

    prcs->completation_time = -1;

    p_base.push_back(prcs);
    prcs = new Process;
  }

  menu(1);
  
  cin >> opt;

  if (opt < 6) {
    menu(2);
    cin >> opt2;

    selectAlgorithm(opt, p_base, n_prcs, context_switch);

    if(opt2 < 6){
      selectAlgorithm(opt2, p_base, n_prcs, context_switch);
    }
  }
  else {
    for (i = 1; i <= 4;i++) 
      selectAlgorithm(i, p_base, n_prcs, context_switch);
  }

  return 0;
}
