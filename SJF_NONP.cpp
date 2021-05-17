// priority non preemtive
#include "SJF_NONP.h"

using namespace std;

SJF2::SJF2(vector <Process*> in_prcs, int in_n, int c_s) {
  prcs = in_prcs;
  n_prcs = in_n;
  context_switch = c_s;
}

void SJF2::execute() {
  int i, completed = 0, current_time = 0, current_pid, min_burst;

  printf("\n======== executing SJF non preemtive ========\n");

  while (completed != n_prcs) {
    current_pid = -1;
    min_burst = 9999;

    for (i = 0; i < n_prcs; i++) {
      // CHECK IF PROCESS IS NOT COMPLETED
      if (prcs[i]->arrival_time <= current_time && prcs[i]->completation_time == -1) {
        //GET PROCESS WITH THE MIN BURST IN THE CURRENT TIME
        if ( prcs[i]->burst_time < min_burst) {
          current_pid = i;
          min_burst = prcs[i]->burst_time;
        }

        // IF TOW PROCESS HAS SAME PRIORITY SELECT WHICH HAS LESS AT
        if ( prcs[i]->burst_time == min_burst) {
          if (prcs[i]->arrival_time < prcs[current_pid]->arrival_time) {
            current_pid = i;
            min_burst = prcs[i]->burst_time;
          }
        }
      }
    }   

    // PROCESS FOUND IN THE CURRENT TIME
    if (current_pid != -1) { 

      prcs[current_pid]->start_time = current_time + context_switch;
      prcs[current_pid]->completation_time = prcs[current_pid]->start_time + prcs[current_pid]->burst_time;
      // TURNAROUND
      prcs[current_pid]->turnaround_time = prcs[current_pid]->completation_time - prcs[current_pid]->arrival_time;
      total_turnaround_time += prcs[current_pid]->turnaround_time;
      // WAITING
      prcs[current_pid]->waiting_time = prcs[current_pid]->turnaround_time - prcs[current_pid]->burst_time;
      total_waiting_time += prcs[current_pid]->waiting_time;
      // RESPONSE
      prcs[current_pid]->response_time = prcs[current_pid]->start_time - prcs[current_pid]->arrival_time;
      total_response_time += prcs[current_pid]->response_time;

      current_time = prcs[current_pid]->completation_time;
      completed++;
    }
    else {
      current_time++;
    }
  }


  sort(prcs.begin(), prcs.end(), compareST);
  printGanttV2(prcs, n_prcs);


  sort(prcs.begin(), prcs.end(), comparePID);

  cout<<"\nPID\t"<<"PRI\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;
  for(int i = 0; i < n_prcs; i++) {
    cout<<prcs[i]->p_id<<"\t";
    cout<<prcs[i]->priority<<"\t";
    cout<<prcs[i]->arrival_time;
    cout<<"\t"<<prcs[i]->burst_time;
    cout<<"\t"<<prcs[i]->start_time;
    cout<<"\t"<<prcs[i]->completation_time;
    cout<<"\t"<<prcs[i]->turnaround_time;
    cout<<"\t"<<prcs[i]->waiting_time;
    cout<<"\t"<<prcs[i]->response_time<<"\t"<<"\n"<<endl;
  }


  // TO DO: PRINT GANTT CHART WITH ROUND ROBIN APROACH
  //printGantt(prcs, n_prcs);

  printf("\nAVG TURNAROUND TIME: %.2f\n",total_turnaround_time/n_prcs);
  printf("AVG WAITING TIME: %.2f\n",total_waiting_time/n_prcs);
  printf("AVG RESPONSE TIME: %.2f\n",total_response_time/n_prcs);

}
