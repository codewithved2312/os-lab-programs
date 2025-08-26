#include<stdio.h> //preprocessor directive
#include<stdlib.h>  //standard library

typedef struct {      // typedef se alias banta hai
    int processid;
    int arrivaltime;
    int bursttime;
    int completiontime;
    int turn_around_time;
    int waiting_time;
} Process;


// function to calculate FCFS Algorithm (non-preemptive)
void calculateFCFS(Process process[], int n) {
    int current_time = 0;
    float total_tat = 0, total_wt = 0;

    
    printf("\n FCFS Scheduling Algorithm\n");
    printf("process id\tarrival time\tburst time\tcompletion time\tturn around time\twaiting time\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {

        if (current_time < process[i].arrivaltime) {
            current_time = process[i].arrivaltime;
        }
        current_time += process[i].bursttime;
        process[i].completiontime = current_time;
        process[i].turn_around_time = process[i].completiontime - process[i].arrivaltime;
        process[i].waiting_time = process[i].turn_around_time - process[i].bursttime;

        total_tat = total_tat + process[i].turn_around_time;
        total_wt = total_wt + process[i].waiting_time;
  

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               process[i].processid,
               process[i].arrivaltime,
               process[i].bursttime,
               process[i].completiontime,
               process[i].turn_around_time,
               process[i].waiting_time);
    }
     float avg_tat = total_tat /(float) n;    //typecast
     float avg_wt = total_wt /(float) n; 
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("average turn around time = %.2f\t",avg_tat);
    printf("--------------------------------------------------------------------------------------------------\n");
     printf("average waiting time = %.2f\t",avg_wt);
}

// function to sort process by arrival  
// ye function bubble sort pe based hai

void ProcessSort(Process process[], int n) {
    Process temp;   // temporary variable   
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (process[i].arrivaltime > process[j].arrivaltime) {
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
}

// function to print Gantt chart
void GanttChart(Process process[], int n) {
    printf("\nGantt Chart:\n");
    printf("----------------------------------------------------------------------------------\n");

    // print process sequence
    for (int i = 0; i < n; i++) {
        printf("|  P%d  ", process[i].processid);
    }
    printf("|\n");

    printf("----------------------------------------------------------------------------------\n");
    // print time sequence
    printf("%d", process[0].arrivaltime);
    for (int i = 0; i < n; i++) {
        printf("     %d", process[i].completiontime);
    }
    printf("\n");
}


// function to print Ready Queue
void ReadyQueue(Process process[], int n) {
    printf("\nReady Queue Sequence (by arrival time):\n");
    printf("----------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", process[i].processid);
        if (i != n - 1) printf("-> ");
    }
    printf("\n----------------------------------------------------------------------------------\n");
}


int main() {   //execution starts from here
    system("cls");
    int num_of_process;
    printf("enter number of processes: ");
    scanf("%d",&num_of_process);

    // dynamic memory allocation for process array
   Process *process = (Process*)malloc(num_of_process*sizeof(Process));
  //  Process *process = (Process*)calloc(num_of_process*,sizeof(Process));

  for(int i=0; i<num_of_process; i++) {
    printf("enter process details for process  %d",i+1);
    process[i].processid = i+1;
    printf(" arrival time: ");
    scanf("%d",&process[i].arrivaltime);
    printf(" burst time:");
    scanf("%d",&process[i].bursttime);
  }

    //function calls
    ProcessSort(process, num_of_process);
    calculateFCFS(process, num_of_process);
    ReadyQueue(process, num_of_process);
    GanttChart(process, num_of_process);
    
    free(process);   //free allocated memory

return 0;  //end of code
}

