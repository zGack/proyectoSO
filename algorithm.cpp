#include "algorithm.h"

void Algorithm::printGantt(Process p[], int n_prcs) {
  //TO DO FIX LAST CT
  int i, j, prev_ct = 0;
  printf("\tGANTT CHART\t\n");
  printf(" ");
  for (i=0;i < n_prcs;i++) {
    if (p[i].start_time != prev_ct) {
      for (j = 0;j < p[i].start_time - prev_ct;j++)printf("---");
      printf(" ");
    }
    for (j = 0;j < p[i].burst_time;j++)printf("--");
    prev_ct = p[i].completation_time;
    printf(" ");
  }

  printf("\n|");
  prev_ct = 0;

  for (i=0;i<n_prcs;i++) {
    if (p[i].start_time != prev_ct) {
      for (j = 0;j < p[i].start_time - prev_ct;j++)printf(" ");
      printf("X");
      for(j=0; j<p[i].start_time - prev_ct; j++) printf(" ");
      printf("|");
    }
    for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
    printf("P%d", p[i].p_id);
    for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
    printf("|");
    prev_ct = p[i].completation_time;
  }

  printf("\n ");
  prev_ct = 0;

  for(i=0; i<n_prcs; i++) {
    if (p[i].start_time != prev_ct) {
      for (j = 0;j < p[i].start_time - prev_ct;j++)printf("---");
      printf(" ");
    }
    for(j=0; j < p[i].burst_time; j++) printf("--");
    printf(" ");
    prev_ct = p[i].completation_time;
  }

  printf("\n");
  prev_ct = 0;

  //printf("0");
  for(i=0; i<n_prcs; i++) {
    if (p[i].start_time != prev_ct) {
      printf("%d", prev_ct);
      for (j = 0;j < p[i].start_time - prev_ct;j++)printf("   ");
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
