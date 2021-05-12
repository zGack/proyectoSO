#include "algorithm.h"

void Algorithm::printGantt(Process p[], int n_prcs) {
  //TO DO FIX LAST CT
  int i, j, prev_ct = context_switch, context_flag = 1;

  printf("\tGANTT CHART\t\n");
  printf(" ");
  for (i=0;i < n_prcs;i++) {
    printf("--- ");
    if (p[i].start_time != prev_ct) {
      printf("--- ");
    }
    for (j = 0;j < p[i].burst_time;j++)printf("--");
    prev_ct = p[i].completation_time + context_switch;
    printf(" ");
  }

  printf("\n|");
  prev_ct = context_switch;

  for (i=0;i<n_prcs;i++) {
    printf(" C |");
    if (p[i].start_time != prev_ct) {
      printf(" X |");
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
    printf("--- ");
    if (p[i].start_time != prev_ct) {
      printf("--- ");
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
    printf("%d   ", prev_ct);
    prev_ct += context_switch;

    if (p[i].start_time != prev_ct) {
      if(prev_ct > 9)printf("\b"); // backspace : remove 1 space
      printf("%d   ", prev_ct);
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

bool Algorithm::compareArrival(Process p1, Process p2) {
  return p1.arrival_time < p2.arrival_time;
}

bool Algorithm::comparePID(Process p1, Process p2) {
  return p1.p_id < p2.p_id;
}

bool Algorithm::compareST(Process p1, Process p2) {
  return p1.start_time < p2.start_time;
}
