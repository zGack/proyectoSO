#include "SJF.h"

using namespace std;

int tCambios[2000];
int nCambios[2000];
int cambios = 0;

SJF::SJF(vector <Process*> in_prcs, int in_n, int ctx) {
  prcs = in_prcs;
  n_prcs = in_n;
  chan = ctx;
}

//
void SJF :: calculateWT(){ 
  using namespace std;
    int rt[n_prcs];
  
    // Copiamos tiempo de burst en rt
    for (int i = 0; i < n_prcs; i++)
        rt[i] = prcs[i]->burst_time;
  
    int done = 0;
    int t = 0;
    int minburst = 100000000; 
    int s = -2; //Tiempo de burst mas corto
    //int completation_time[n_prcs];
    bool check = false;
    int repe = 0;
    
  
    //No termina hasta que todos los procesos acaben
    while (done != n_prcs) {
        
        for (int j = 0; j < n_prcs; j++) {
            if (( prcs[j]->arrival_time <= t) &&(rt[j] < minburst) && rt[j] > 0) {
                //cout << s <<" "<< t << endl;
                minburst = rt[j];
                s = j;
                t = t + chan; // APLICAMOS EL CAMBIO DE CONTEXTO
                tCambios[cambios] = t;
                nCambios[cambios] = s;
                cambios++;
                repe++;
                check = true;
                
            }
        }
        

        //cout<< s << " " << t << endl;


        if(prcs[s]->start_time == 0){
            prcs[s]->start_time = t;
        }
  
        if (check == false) {
            t++;
            
            if(s != -1){
              if(t != 1) t = t + chan; // APLICAMOS EL CAMBIO DE CONTEXTO
              tCambios[cambios] = t - 1;
              nCambios[cambios] = -1;
              cambios++;
            }
            s = -1;
            continue;
        }
  
        // Reduzco el tiempo de burst del proceso
        

        rt[s]--;
        minburst = rt[s];
        if (minburst == 0)
            minburst = 100000000;
  
        //Se ejecuta el proceso
        if (rt[s] == 0) {
            done++;
            check = false;
  
            prcs[s]->completation_time = t + 1;
  
            prcs[s]->waiting_time = prcs[s]->completation_time - prcs[s]->burst_time - prcs[s]->arrival_time;
            total_waiting_time = total_waiting_time + prcs[s]->waiting_time;
            if (prcs[s]->waiting_time < 0)
                prcs[s]->waiting_time = 0;
        }
        t++;
    }
}
  
void SJF :: calculateTAT()
{
      int i;

  //prcs[0].start_time = prcs[0].arrival_time;
  //prcs[0].completation_time = prcs[0].start_time + prcs[0].burst_time;
  prcs[0]->turnaround_time = prcs[0]->completation_time - prcs[0]->arrival_time;
  total_turnaround_time += prcs[0]->turnaround_time;

  for (i = 1;i < n_prcs; i++) {
    //prcs[i].start_time = max(prcs[i-1].completation_time,prcs[i].arrival_time);
    //prcs[i].completation_time = prcs[i].start_time + prcs[i].burst_time;
    prcs[i]->turnaround_time = prcs[i]->completation_time - prcs[i]->arrival_time;
    total_turnaround_time += prcs[i]->turnaround_time;
  }
}

void SJF::calculateRT() {
  int i;

  for (i = 0;i < n_prcs; i++) {
    prcs[i]->response_time = prcs[i]->start_time - prcs[i]->arrival_time;
    total_response_time += prcs[i]->response_time;
  }
}

  
// Function to calculate average time
void SJF :: execute()
{
    printf("\n======== executing SJF ========\n");
    printf("\nContext switch units: %d\n",chan);
    sort(prcs.begin(), prcs.end(), compareArrival);
    
    calculateWT();
    calculateTAT();
    calculateRT();
    cout << endl;
    /* for(int y=0; y < cambios; y++){
      cout << nCambios[y] << " "<< tCambios[y] << endl;
    }
    cout << nCambios[cambios-1] << " "<< prcs[nCambios[cambios-1]].completation_time <<endl; */
    
    printGanttSJF(prcs, n_prcs);

    sort(prcs.begin(), prcs.end(), comparePID);

    cout<<"\nPID\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;
    for(int i = 0; i < n_prcs; i++) {
        cout<<prcs[i]->p_id<<"\t";
        cout<<prcs[i]->arrival_time;
        cout<<"\t"<<prcs[i]->burst_time;
        cout<<"\t"<<prcs[i]->start_time;
        cout<<"\t"<<prcs[i]->completation_time;
        cout<<"\t"<<prcs[i]->turnaround_time;
        cout<<"\t"<<prcs[i]->waiting_time;
        cout<<"\t"<<prcs[i]->response_time<<"\t"<<"\n"<<endl;
    }

  printf("\nAVG TURNAROUND TIME: %.2f\n",total_turnaround_time/n_prcs);
  printf("AVG WAITING TIME: %.2f\n",total_waiting_time/n_prcs);
  printf("AVG RESPONSE TIME: %.2f\n",total_response_time/n_prcs);
}

void SJF::printGanttSJF(vector <Process*> p, int n_prcs) {
  //TO DO FIX LAST CT
  int i, j, prev_ct = 0;
  //printf("\tGANTT CHART\t\n");
  cout<<"PID\t"<<"START\t"<<"COMPLETATION\t" << "\n"<<endl;
  for (i=0;i < cambios -1;i++) {
    if(nCambios[i] <= -1){
          printf("X");
      }
      else{
        printf("P%d", p[nCambios[i]]->p_id);
      }

    cout << "\t" << tCambios[i]<< "\t" << tCambios[i+1]-1<<"\t" << endl;
  }

  if(nCambios[cambios-1] <= -1){
          printf("X");
      }
      else{
        printf("P%d", p[nCambios[cambios-1]]->p_id);
      }
  cout << "\t" << tCambios[cambios-1] << "\t" << prcs[nCambios[cambios-1]]->completation_time <<"\t" << endl;


 /*  printf(" ");
  for (i=0;i < cambios -1;i++) {
    for (j = 0;j < tCambios[j+1] - tCambios[j]  ;j++)printf("------");
          printf(" ");
    // if (p[i].start_time != prev_ct) {
    //   for (j = 0;j < p[i].start_time - prev_ct;j++)printf("---");
    //   printf(" ");
    // }
    // for (j = 0;j < p[i].burst_time;j++)printf("--");
    // prev_ct = p[i].completation_time;
    // printf(" ");
  }
  for (j = 0;j < prcs[nCambios[cambios-1]].completation_time - tCambios[cambios-1]  ;j++)printf("------");
          printf(" ");

  printf("\n|");
  prev_ct = 0;

  for (i=0;i<cambios-1;i++) {
    /*if (p[i].start_time != prev_ct) {
      for (j = 0;j < p[i].start_time - prev_ct;j++)printf(" "); 
      for (j = 0;j < tCambios[j+1] - tCambios[j]  ;j++)printf("  ");
      if(nCambios[i] == -1){
          printf("X");
      }
      else{
        printf("P%d", p[nCambios[i]].p_id);
      }
      for (j = 0;j < tCambios[j+1] - tCambios[j]  ;j++)printf("  ");
      printf("|");
    }
    for (j = 0;j < prcs[nCambios[cambios-1]].completation_time - tCambios[cambios-1]  ;j++)printf("  ");
    if(nCambios[cambios-1] == -1){
          printf("X");
      }
      else{
        printf("P%d", p[nCambios[cambios-1]].p_id);
      }
    for (j = 0;j < prcs[nCambios[cambios-1]].completation_time - tCambios[cambios-1]  ;j++)printf("  ");
      printf("|");


    

  printf("\n ");
  prev_ct = 0;

  for (i=0;i < cambios -1;i++) {
    for (j = 0;j < tCambios[j+1] - tCambios[j]  ;j++)printf("------");
          printf(" ");
    // if (p[i].start_time != prev_ct) {
    //   for (j = 0;j < p[i].start_time - prev_ct;j++)printf("---");
    //   printf(" ");
    // }
    // for (j = 0;j < p[i].burst_time;j++)printf("--");
    // prev_ct = p[i].completation_time;
    // printf(" ");
  }
  for (j = 0;j < prcs[nCambios[cambios-1]].completation_time - tCambios[cambios-1]  ;j++)printf("------");
    printf(" ");

  printf("\n");
  prev_ct = 0;

  printf("%d", tCambios[0]);


  for (i=0;i < cambios -1;i++) {
    for (j = 0;j < tCambios[j+1] - tCambios[j]  ;j++)printf("       ");
          printf("%d", tCambios[i + 1]);
  }
  for (j = 0;j < prcs[nCambios[cambios-1]].completation_time - tCambios[cambios-1]  ;j++)printf("      ");
  printf("%d",prcs[nCambios[cambios-1]].completation_time);
  /* for(i=0; i<n_prcs; i++) {
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
  printf("\n"); */
}
