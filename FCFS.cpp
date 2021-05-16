#include "FCFS.h"

using namespace std;

FCFS::FCFS(Process in_prcs[], int in_n, int c_s) {
  prcs = in_prcs;
  n_prcs = in_n;
  context_switch = c_s;
}

void FCFS::execute() {
  int i;

  printf("executing FCFS\n");
  printf("\nContext switch units: %d\n", context_switch);

  sort(prcs,prcs + n_prcs, compareArrival);

  calculateTAT();
  calculateWT();
  calculateRT();

  sort(prcs, prcs + n_prcs, comparePID);

  cout<<"\nPID\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;
  for(int i = 0; i < n_prcs; i++) {
    cout<<prcs[i].p_id<<"\t";
    cout<<prcs[i].arrival_time;
    cout<<"\t"<<prcs[i].burst_time;
    cout<<"\t"<<prcs[i].start_time;
    cout<<"\t"<<prcs[i].completation_time;
    cout<<"\t"<<prcs[i].turnaround_time;
    cout<<"\t"<<prcs[i].waiting_time;
    cout<<"\t"<<prcs[i].response_time<<"\t"<<"\n"<<endl;
  }

  sort(prcs,prcs + n_prcs, compareArrival);
  printGantt(prcs, n_prcs);

  printf("\nAVG TURNAROUND TIME: %.2f\n",total_turnaround_time/n_prcs);
  printf("AVG WAITING TIME: %.2f\n",total_waiting_time/n_prcs);
  printf("AVG RESPONSE TIME: %.2f\n",total_response_time/n_prcs);
  
}

void FCFS::calculateTAT() {
  int i;

  prcs[0].start_time = prcs[0].arrival_time + context_switch;
  prcs[0].completation_time = prcs[0].start_time + prcs[0].burst_time;
  prcs[0].turnaround_time = prcs[0].completation_time - prcs[0].arrival_time;
  total_turnaround_time += prcs[0].turnaround_time;

  for (i = 1;i < n_prcs; i++) {
    prcs[i].start_time = max(prcs[i-1].completation_time,prcs[i].arrival_time) + context_switch;
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

