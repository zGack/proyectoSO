#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <queue> 
#include <cstring>
#include "PRR.h"

using namespace std;


using namespace std;

PRR::PRR(vector <Process*> in_prcs, int in_n, int c_s) {
  prcs = in_prcs;
  n_prcs = in_n;
  context_switch = c_s;
}

void PRR::execute() {
  int i, completed = 0, current_time = 0, current_pid, max_priority, nd = 0, prio;
  int cambioIdx[50], cambioTm[50], ind[n_prcs];

  printf("\n======== executing PRIORITY RR ========\n");

  for (i = 0; i < n_prcs - 1; i++) {
      prcs[i]-> arrival_time = 0; //Ya que no importa el tiempo de llegada para este algoritmo
      ind[i] = 0;
  }

  sort(prcs.begin(), prcs.end(), comparePrio);

  while (completed != n_prcs) {
    cout << "in";
    current_pid = -1;
    max_priority = -1;

    for (i = 0; i < n_prcs - 1; i++) {
        // IF TOW PROCESS HAS SAME PRIORITY SELECT WHICH HAS LESS AT
        cout << prcs[0] -> completation_time << endl;
        if ( prcs[i]->priority == prcs[i+1]->priority) {
            prio = prcs[i]->priority;
            cout << prcs[0] -> priority<< endl;
            for(int j = i; j < n_prcs; j++){
                if(prcs[j]->priority == prio){
                    cout << prcs[0] -> priority<< endl;
                    ind[nd] = j;
                    nd++;
                }
            }

            int burst_remaining[100];
            int idx;

            cout << setprecision(2) << fixed;

            for(int i = 0; i < nd; i++) {
                burst_remaining[ind[i]] = prcs[ind[i]]-> burst_time;
            }

            

            queue<int> q;
            int current_time = 0;
            q.push(ind[0]);
            int pass = 0, cambio = 0;
            int completed = 0;
            int cambioIdx[50], cambioTm[50];
            int mark[100];
            memset(mark,0,sizeof(mark));
            mark[0] = 1;

            while(completed != nd) {
                idx = q.front();
                q.pop();

                if(burst_remaining[idx] == prcs[idx]->burst_time) {
                    prcs[idx]-> start_time = max(current_time,prcs[idx]->arrival_time);
                    current_time = prcs[idx]->start_time;
                }

                if(burst_remaining[idx]- QUANTUM> 0) {
                    burst_remaining[idx] -= QUANTUM;
                    current_time += QUANTUM;

                    cambioIdx[cambio] = idx;
                    cambioTm[cambio] = current_time;
                    cambio++;

                    current_time += context_switch;
                }
                else {
                    current_time += burst_remaining[idx];
                    burst_remaining[idx] = 0;
                    completed++;

                    cambioIdx[cambio] = idx;
                    cambioTm[cambio] = current_time;
                    cambio++;

                    prcs[idx]->completation_time = current_time;
                    prcs[idx]->turnaround_time = prcs[idx]->completation_time - prcs[idx]->arrival_time;
                    prcs[idx]->waiting_time = prcs[idx]->turnaround_time - prcs[idx]->burst_time;
                    prcs[idx]->response_time = prcs[idx]->start_time - prcs[idx]->arrival_time;

                    total_turnaround_time += prcs[idx]->turnaround_time;
                    total_waiting_time += prcs[idx]->waiting_time;
                    total_response_time += prcs[idx]->response_time;

                    current_time += context_switch;
                }

                for(int i = 1; i < nd; i++) {
                    if(burst_remaining[ind[i]] > 0 && prcs[ind[i]]->arrival_time <= current_time && mark[ind[i]] == 0) {
                        q.push(ind[i]);
                        mark[ind[i]] = 1;
                    }
                }
                if(burst_remaining[idx] > 0) {
                    q.push(idx);
                }

                if(q.empty()) {
                    for(int i = 1; i < nd; i++) {
                        if(burst_remaining[ind[i]] > 0) {
                            q.push(ind[i]);
                            mark[ind[i]] = 1;
                            break;
                        }
                    }
                }
            }
            completed += nd;
            nd = 0;
             for (i = 0; i < n_prcs - 1; i++) {
                    ind[i] = 0;
            }

        }  

        else{
            current_pid = i;
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

  //printGantt(prcs, n_prcs);

  printf("\nAVG TURNAROUND TIME: %.2f\n",total_turnaround_time/n_prcs);
  printf("AVG WAITING TIME: %.2f\n",total_waiting_time/n_prcs);
  printf("AVG RESPONSE TIME: %.2f\n",total_response_time/n_prcs);

}
