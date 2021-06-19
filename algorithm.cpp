#include "algorithm.h"

void Algorithm::printGantt(Process p[], int n_prcs) {
  //TO DO FIX LAST CT
  int i, j, prev_ct = context_switch, context_flag = 1;

  printf(" ");
  for (i=0;i < n_prcs;i++) {
    if(context_switch > 0)printf("--- "); // CONTEXT SWITCH

    if (p[i].start_time != prev_ct) {
      printf("--- "); // CPU WAITING FOR PROCESS
    }
    for (j = 0;j < p[i].burst_time;j++)printf("--");
    prev_ct = p[i].completation_time + context_switch;
    printf(" ");
  }

  printf("\n|");
  prev_ct = context_switch;

  for (i=0;i<n_prcs;i++) {
    if(context_switch > 0)printf(" C |"); // CONTEXT
    if (p[i].start_time != prev_ct) {
      printf(" X |"); // CPU WAITING FOR PROCESS
    }
    for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
    printf("P%d", p[i].p_id);
    for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
    printf("|");
    prev_ct = p[i].completation_time + context_switch;
  }

  printf("\n ");
  prev_ct = context_switch;

  for(i=0; i<n_prcs; i++) {
    if(context_switch > 0)printf("--- "); // CONTEXT
    if (p[i].start_time != prev_ct) {
      printf("--- "); // CPU WAITING FOR PROCESS
    }
    for(j=0; j < p[i].burst_time; j++) printf("--");
    printf(" ");
    prev_ct = p[i].completation_time + context_switch;
  }

  printf("\n");
  prev_ct = 0;

  //printf("0");
  for(i=0; i<n_prcs; i++) {
    if(prev_ct > 9)printf("\b"); // backspace : remove 1 space
    if(context_switch > 0)printf("%d   ", prev_ct); // CONTEXT
    prev_ct += context_switch;

    if (p[i].start_time != prev_ct) {
      if(prev_ct > 9)printf("\b"); // backspace : remove 1 space
      printf("%d   ", prev_ct); // CPU WAITING FOR CONTEXT
    }
    if(p[i].start_time > 9) printf("\b"); // backspace : remove 1 space
    printf("%d", p[i].start_time);
    for(j=0; j<p[i].burst_time; j++) printf("  ");
    prev_ct = p[i].completation_time;
    if (i + 1 == n_prcs) {
      if(p[i].completation_time > 9) printf("\b"); // backspace : remove 1 space
      printf("%d",p[i].completation_time);
    }
  }
  printf("\n");
}


void Algorithm::printGanttV2(vector <Process*> p, int n_prcs) {
  int prev_ct = 0 + context_switch;

  printf("Context switch units: %d\n\n",context_switch);
  printf("PID\tSTART\tCOMPLETATION\n");

  for (int i = 0; i < n_prcs; i++) {
    if (p[i]->start_time != prev_ct ) {
      printf("X\t%d\t%d\n", prev_ct, p[i]->start_time);
    }
    printf("%d\t",p[i]->p_id);
    printf("%d\t",p[i]->start_time);
    printf("%d\n",p[i]->completation_time);
    prev_ct = p[i]->completation_time + context_switch;
  }
}

void Algorithm::writeData(vector <Process*> prcs, int n_prcs, string file_name) {
  ofstream text_file;

  text_file.open(file_name + ".txt");
  text_file << file_name << endl;

  text_file << "\nPID\t"<<"PRI\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;

  for(int i = 0; i < n_prcs; i++) {
    text_file << prcs[i]->p_id<<"\t";
    text_file << prcs[i]->priority<<"\t";
    text_file << prcs[i]->arrival_time;
    text_file << "\t"<<prcs[i]->burst_time;
    text_file << "\t"<<prcs[i]->start_time;
    text_file << "\t"<<prcs[i]->completation_time;
    text_file << "\t"<<prcs[i]->turnaround_time;
    text_file << "\t"<<prcs[i]->waiting_time;
    text_file << "\t"<<prcs[i]->response_time<<"\t"<<"\n"<<endl;
  }

  text_file.close();
  
}

bool Algorithm::compareArrival(Process *p1, Process *p2) {
  return p1->arrival_time < p2->arrival_time;
}

bool Algorithm::comparePID(Process *p1, Process *p2) {
  return p1->p_id < p2->p_id;
}

bool Algorithm::compareST(Process *p1, Process *p2) {
  return p1->start_time < p2->start_time;
}
