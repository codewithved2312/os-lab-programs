#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processid;
    int arrivaltime;
    int bursttime;
    int completiontime;
    int turn_around_time;
    int waiting_time;
    int is_completed;   // flag to check if process is done
} Process;

// Function to calculate SJF (Non-preemptive)
void calculateSJF(Process process[], int n) {
    int current_time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("\n SJF Scheduling Algorithm (Non-preemptive)\n");
    printf("process id\tarrival time\tburst time\tcompletion time\tturn around time\twaiting time\n");
    printf("--------------------------------------------------------------------------------------------------\n");

    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9; // infinity

        // find process with min burst time among arrived & not completed
        for (int i = 0; i < n; i++) {
            if (process[i].arrivaltime <= current_time && !process[i].is_completed) {
                if (process[i].bursttime < min_bt) {
                    min_bt = process[i].bursttime;
                    idx = i;
                }
                // tie-breaking on arrival time
                else if (process[i].bursttime == min_bt) {
                    if (process[i].arrivaltime < process[idx].arrivaltime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {  
            current_time++; // if no process arrived yet
        } else {
            current_time += process[idx].bursttime;
            process[idx].completiontime = current_time;
            process[idx].turn_around_time = process[idx].completiontime - process[idx].arrivaltime;
            process[idx].waiting_time = process[idx].turn_around_time - process[idx].bursttime;

            total_tat += process[idx].turn_around_time;
            total_wt += process[idx].waiting_time;

            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",
                   process[idx].processid,
                   process[idx].arrivaltime,
                   process[idx].bursttime,
                   process[idx].completiontime,
                   process[idx].turn_around_time,
                   process[idx].waiting_time);

            process[idx].is_completed = 1;
            completed++;
        }
    }

    float avg_tat = total_tat / (float)n;
    float avg_wt = total_wt / (float)n;

    printf("--------------------------------------------------------------------------------------------------\n");
    printf("average turn around time = %.2f\t", avg_tat);
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("average waiting time = %.2f\t", avg_wt);
}

// Gantt Chart function
void GanttChart(Process process[], int n) {
    printf("\nGantt Chart:\n");
    printf("----------------------------------------------------------------------------------\n");

    // print process sequence
    for (int i = 0; i < n; i++) {
        printf("|  P%d  ", process[i].processid);
    }
    printf("|\n");

    printf("----------------------------------------------------------------------------------\n");
    printf("%d", process[0].arrivaltime);
    for (int i = 0; i < n; i++) {
        printf("     %d", process[i].completiontime);
    }
    printf("\n");
}

int main() {
    system("cls"); // clear screen (for Windows)
    int num_of_process;
    printf("Enter number of processes: ");
    scanf("%d", &num_of_process);

    Process *process = (Process*)malloc(num_of_process * sizeof(Process));

    for (int i = 0; i < num_of_process; i++) {
        printf("Enter process details for process %d\n", i+1);
        process[i].processid = i + 1;
        printf(" Arrival time: ");
        scanf("%d", &process[i].arrivaltime);
        printf(" Burst time: ");
        scanf("%d", &process[i].bursttime);
        process[i].is_completed = 0;
    }

    calculateSJF(process, num_of_process);

    GanttChart(process, num_of_process);

    free(process);
    return 0;
}
