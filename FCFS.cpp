#include "FCFS.h"

using namespace std;

FCFS::FCFS(Process in_prcs[], int in_n) {
  prcs = in_prcs;
  n_prcs = in_n;
}

void FCFS::execute() {
  int i;
  cout << "executing FCFS" << endl;

  sort(prcs,prcs + n_prcs, compareArrival);

  printf("\n");
  for (i = 0;i < n_prcs; i++) {
    printf("P[%d] BURST: %d ARRIVAL: %d\n",prcs[i].p_id, prcs[i].burst_time, prcs[i].arrival_time);
  }

  calculateTAT();
  calculateWT();
  calculateRT();

  cout << "\nturnaround" << endl;
  printf("\n");
  for (i = 0;i < n_prcs;i++) {
    printf("P[%d] TAT: %d\n",prcs[i].p_id, prcs[i].turnaround_time);
  }

  cout << "\nwaiting" << endl;
  for (i = 0;i < n_prcs;i++) {
    printf("P[%d] WT: %d\n",prcs[i].p_id, prcs[i].waiting_time);
  }

  cout << "\nresponse" << endl;
  for (i = 0;i < n_prcs;i++) {
    printf("P[%d] WT: %d\n",prcs[i].p_id, prcs[i].response_time);
  }

  cout << "\ncompletation" << endl;
  for (i = 0;i < n_prcs;i++) {
    printf("P[%d] WT: %d\n",prcs[i].p_id, prcs[i].completation_time);
  }

  printf("\nAVG TAT: %d\n",total_turnaround_time/n_prcs);
  printf("AVG WT: %d\n",total_waiting_time/n_prcs);
  printf("AVG WT: %d\n",total_response_time/n_prcs);
}

bool FCFS::compareArrival(Process p1, Process p2) {
  return p1.arrival_time < p2.arrival_time;
}

/*static bool FCFS::comparePID(Process p1, Process p2) {
  return p1.p_id < p2.p_id;
}*/

void FCFS::calculateTAT() {
  int i;

  prcs[0].start_time = prcs[0].arrival_time;
  prcs[0].completation_time = prcs[0].start_time + prcs[0].burst_time;
  prcs[0].turnaround_time = prcs[0].completation_time - prcs[0].arrival_time;
  total_turnaround_time += prcs[0].turnaround_time;

  for (i = 1;i < n_prcs; i++) {
    prcs[i].start_time = max(prcs[i-1].completation_time,prcs[i].arrival_time);
    prcs[i].completation_time = prcs[i].start_time + prcs[i].burst_time;
    prcs[i].turnaround_time = prcs[i].completation_time - prcs[i].arrival_time;
    total_turnaround_time += prcs[i].turnaround_time;
  }
}

void FCFS::calculateWT() {
  int i;

  for (i = 0;i < n_prcs; i++) {
    prcs[i].waiting_time = prcs[i].turnaround_time - prcs[i].burst_time;
    total_waiting_time += prcs[i].waiting_time;
  }
}

void FCFS::calculateRT() {
  int i;

  for (i = 0;i < n_prcs; i++) {
    prcs[i].response_time = prcs[i].start_time - prcs[i].arrival_time;
    total_response_time += prcs[i].response_time;
  }
}
