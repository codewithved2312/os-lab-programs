#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processid;
    int arrivaltime;
    int bursttime;
    int remainingtime;
    int completiontime;
    int turn_around_time;
    int waiting_time;
} Process;

void calculateRR(Process process[], int n, int quantum) {
    int current_time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    int *queue = (int*)malloc(n * 100 * sizeof(int)); // circular queue large enough
    int front = 0, rear = 0;

    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    // push first arrived process
    queue[rear++] = 0;
    visited[0] = 1;
    current_time = process[0].arrivaltime;

    printf("\nRound Robin Scheduling Algorithm\n");
    printf("process id\tarrival time\tburst time\tcompletion time\tturn around time\twaiting time\n");
    printf("--------------------------------------------------------------------------------------------------\n");

    while (completed < n) {
        int idx = queue[front++];
        if (process[idx].remainingtime > 0) {
            if (process[idx].remainingtime <= quantum) {
                current_time += process[idx].remainingtime;
                process[idx].completiontime = current_time;
                process[idx].remainingtime = 0;
                completed++;

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
            } else {
                current_time += quantum;
                process[idx].remainingtime -= quantum;
            }

            // enqueue newly arrived processes up to current_time
            for (int i = 0; i < n; i++) {
                if (!visited[i] && process[i].arrivaltime <= current_time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            // if current process still has remaining time, re-add to queue
            if (process[idx].remainingtime > 0) {
                queue[rear++] = idx;
            }
        }
    }

    float avg_tat = total_tat / (float)n;
    float avg_wt = total_wt / (float)n;

    printf("--------------------------------------------------------------------------------------------------\n");
    printf("average turn around time = %.2f\t", avg_tat);
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("average waiting time = %.2f\t", avg_wt);

    free(queue);
}

// Ready Queue sequence for display
void ReadyQueue(Process process[], int n) {
    printf("\nInitial Ready Queue Sequence (by arrival time):\n");
    printf("----------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", process[i].processid);
        if (i != n - 1) printf("-> ");
    }
    printf("\n----------------------------------------------------------------------------------\n");
}

int main() {
    system("cls");
    int num_of_process, quantum;
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
        process[i].remainingtime = process[i].bursttime; // initialize
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    ReadyQueue(process, num_of_process);
    calculateRR(process, num_of_process, quantum);

    free(process);
    return 0;
}
