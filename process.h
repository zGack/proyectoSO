#ifndef PROCESS_H_
#define PROCESS_H_
struct process {
  int p_id,
      burst_time,
      arrival_time,
      waiting_time,
      turnaround_time,
      response_time,
      start_time,
      completation_time;
};

typedef struct process Process;

#endif
