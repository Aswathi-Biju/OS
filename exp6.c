#include <stdio.h>
#include <string.h>
#define MAX 20
#define Q 3

typedef struct {
    int pid, at, bt, pr;
    int ct, tat, wt, rt;
} P;

/* -------- Utility -------- */

void copy(P a[], P b[], int n) {
    for (int i = 0; i < n; i++)
        a[i] = b[i];
}

float avgWT(P p[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += p[i].wt;
    return sum / n;
}

/* -------- Print Functions -------- */

void printFull(P p[], int n, char name[]) {
    printf("\n%s\n", name);
    printf("----------------------------\n");
    printf("PID AT BT PR CT TAT WT\n");
    printf("----------------------------\n");
    for (int i = 0; i < n; i++)
        printf("%d   %d  %d  %d  %d  %d   %d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
}

/* -------- FCFS -------- */

float FCFS(P p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    return avgWT(p, n);
}

/* -------- SJF (Non-Preemptive) -------- */

float SJF(P p[], int n) {
    int done = 0, time = 0, vis[MAX] = {0};

    while (done < n) {
        int idx = -1;

        for (int i = 0; i < n; i++) {
            // Check if arrived, not finished, and find the shortest burst time
            if (p[i].at <= time && !vis[i]) {
                if (idx == -1 || p[i].bt < p[idx].bt)
                    idx = i;
            }
        }

        if (idx == -1) {
            time++;
        } else {
            // Process runs to completion (Non-preemptive)
            time += p[idx].bt; 
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            vis[idx] = 1;
            done++;
        }
    }
    return avgWT(p, n);
}

/* -------- Priority (Non-Preemptive) -------- */

float Priority(P p[], int n) {
    int done = 0, time = 0, vis[MAX] = {0};

    while (done < n) {
        int idx = -1;

        for (int i = 0; i < n; i++)
            if (p[i].at <= time && !vis[i])
                if (idx == -1 || p[i].pr > p[idx].pr)
                    idx = i;

        if (idx == -1) {
            time++;
        } else {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            vis[idx] = 1;
            done++;
        }
    }
    return avgWT(p, n);
}

/* -------- Round Robin -------- */

float RR(P p[], int n) {
    int done = 0, time = 0;

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (done < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                executed = 1;

                int t = (p[i].rt > Q) ? Q : p[i].rt;
                p[i].rt -= t;
                time += t;

                if (p[i].rt == 0) {
                    done++;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
            }
        }
        if (!executed) time++;
    }
    return avgWT(p, n);
}

/* -------- MAIN -------- */

int main() {
    int n;
    P p[MAX], temp[MAX];

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        printf("\nPID AT BT PR: ");
        scanf("%d%d%d%d", &p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
    }

    copy(temp, p, n);
    float a = FCFS(temp, n);
    printFull(temp, n, "FCFS");

    copy(temp, p, n);
    float b = SJF(temp, n);
    printFull(temp, n, "SJF");

    copy(temp, p, n);
    float c = Priority(temp, n);
    printFull(temp, n, "Priority");

    copy(temp, p, n);
    float d = RR(temp, n);
    printFull(temp, n, "Round Robin");

    printf("\nAverage Waiting Time\n");
    printf("----------------------------\n");
    printf("FCFS: %.2f\nSJF: %.2f\nPriority: %.2f\nRR: %.2f\n", a, b, c, d);

    float min = a;
    char algo[20] = "FCFS";

    if (b < min) { min = b; strcpy(algo, "SJF"); }
    if (c < min) { min = c; strcpy(algo, "Priority"); }
    if (d < min) { min = d; strcpy(algo, "Round Robin"); }

    printf("\nMinimum Average Waiting Time: %s (%.2f)\n", algo, min);

    return 0;
}
