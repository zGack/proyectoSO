// Round Robin
#include "ROUND_ROBIN.h"

using namespace std;

ROUNDR::ROUNDR(vector <Process*> in_prcs, int in_n, int c_s) {
  prcs = in_prcs;
  n_prcs = in_n;
  context_switch = c_s;
}

void ROUNDR::execute() {
  int i, completed = 0, current_time = 0, current_pid, q;
  int *burst_remaining = new int[n_prcs], *initializated = new int[n_prcs];
  queue<int> ready_q;
  memset(initializated,0,sizeof(initializated));

  printf("\n======== executing ROUND ROBIN ========\n");

  cout << "\nType quantum for Round Robin \n> ";
  cin >> q;

  for(i = 0;i < n_prcs;i++) {
    burst_remaining[i] = prcs[i]->burst_time;
  } 

  sort(prcs.begin(), prcs.end(), compareArrival);

  ready_q.push(0);
  initializated[0] = 1;

  while (completed != n_prcs) {
    current_pid = ready_q.front();
    ready_q.pop();

    if (burst_remaining[current_pid] == prcs[current_pid]->burst_time) {
      prcs[current_pid]->start_time = max(current_time, prcs[current_pid]->arrival_time) + context_switch;
      total_idle_time += prcs[current_pid]->start_time - current_time;
      current_time = prcs[current_pid]->start_time;
    }

    if (burst_remaining[current_pid] - q > 0 ) {
      burst_remaining[current_pid] -= q;
      current_time += q;
    }
    else {
      current_time += burst_remaining[current_pid];
      burst_remaining[current_pid] = 0;
      completed++;

      prcs[current_pid]->completation_time = current_time;
      // TURNAROUND
      prcs[current_pid]->turnaround_time = prcs[current_pid]->completation_time - prcs[current_pid]->arrival_time;
      total_turnaround_time += prcs[current_pid]->turnaround_time;
      // WAITING
      prcs[current_pid]->waiting_time = prcs[current_pid]->turnaround_time - prcs[current_pid]->burst_time;
      total_waiting_time += prcs[current_pid]->waiting_time;
      // RESPONSE
      prcs[current_pid]->response_time = prcs[current_pid]->start_time - prcs[current_pid]->arrival_time;
      total_response_time += prcs[current_pid]->response_time;
    }


    for(i = 0;i < n_prcs;i++) {
      if (burst_remaining[i] > 0 && prcs[i]->arrival_time <= current_time && initializated[i] == 0) {
        ready_q.push(i);
        initializated[i] = 1;
      }
    }

    if (burst_remaining[current_pid] > 0) {
      ready_q.push(current_pid);
    }

    if (ready_q.empty()) {
      for(i = 0;i < n_prcs;i++) {
        if (burst_remaining[i] > 0) {
          ready_q.push(i);
          initializated[i] = 1;
          break;
        }
      }
    }
  }

  sort(prcs.begin(), prcs.end(), compareST);

  int prev_ct = 0 + context_switch;

  printf("Context switch units: %d\n\n",context_switch);
  printf("PID\tSTART\tCOMPLETATION\n");

  for (int i = 0; i < n_prcs; i++) {
    printf("%d\t",prcs[i]->p_id);
    printf("%d\t",prcs[i]->start_time);
    printf("%d\n",prcs[i]->completation_time);
    prev_ct = prcs[i]->completation_time + context_switch;
  }

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

  //printGantt(prcs, n_prcs);

  printf("\nAVG TURNAROUND TIME: %.2f\n",total_turnaround_time/n_prcs);
  printf("AVG WAITING TIME: %.2f\n",total_waiting_time/n_prcs);
  printf("AVG RESPONSE TIME: %.2f\n",total_response_time/n_prcs);
  printf("CPU UTILIZATION: %.0f%%\n", ((prcs[n_prcs-1]->completation_time - total_idle_time) / prcs[n_prcs-1]->completation_time)*100);

  writeData(prcs, n_prcs, "ROUND ROBIN");

}
