// Banker's Algorithm - Deadlock Avoidance & Detection
#include <stdio.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];
    int f[n], ans[n], ind = 0;

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Max Matrix
    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Calculate Need Matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize Finish array
    for (int k = 0; k < n; k++)
        f[k] = 0;

    // Banker's Algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    // Check if system is in a safe state
    int safe = 1;
    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            safe = 0;
            printf("\nSystem is NOT in a safe state!\n");
            break;
        }
    }

    if (safe == 1) {
        printf("\nSystem is in a SAFE STATE.\nSafe sequence is: ");
        for (int i = 0; i < n - 1; i++) {
            printf("P%d -> ", ans[i]);
        }
        printf("P%d\n", ans[n - 1]);
    }

    return 0;
}
