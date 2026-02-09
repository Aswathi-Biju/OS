#include <stdio.h>
#include <string.h>

#define MAX 20
#define Q 3

typedef struct {
    int pid, at, bt, pr, ct, tat, wt, rt;
} Process;

/* ---------- Utility Functions ---------- */

void copy(Process dest[], Process src[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

void sortByAT(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
}

float calculateAvgWT(Process p[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += p[i].wt;
    return sum / n;
}

void printTable(Process p[], int n, const char* title) {
    printf("\n%s\n", title);
    printf("---------------------------------------------------\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }
}

/* ---------- FCFS ---------- */

float FCFS(Process p[], int n) {
    sortByAT(p, n);
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    return calculateAvgWT(p, n);
}

/* ---------- SRTF ---------- */

float SRTF(Process p[], int n) {
    int completed = 0, time = 0;
    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (idx == -1 || p[i].rt < p[idx].rt)
                    idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }
    return calculateAvgWT(p, n);
}

/* ---------- Non-Preemptive Priority ---------- */

float Priority(Process p[], int n) {
    int completed = 0, time = 0;
    int done[MAX] = {0};

    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !done[i]) {
                if (idx == -1 || p[i].pr > p[idx].pr)
                    idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        completed++;
    }
    return calculateAvgWT(p, n);
}

/* ---------- Round Robin ---------- */

float RR(Process p[], int n) {
    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    int visited[MAX] = {0};

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].at <= time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];

        int exec = (p[idx].rt > Q) ? Q : p[idx].rt;
        p[idx].rt -= exec;
        time += exec;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].at <= time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].rt > 0) {
            queue[rear++] = idx;
        } else {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }
    return calculateAvgWT(p, n);
}

/* ---------- Main ---------- */

int main() {
    int n;
    Process p[MAX], temp[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Enter PID: ");
        scanf("%d", &p[i].pid);
        printf("Enter AT: ");
        scanf("%d", &p[i].at);
        printf("Enter BT: ");
        scanf("%d", &p[i].bt);
        printf("Enter PR: ");
        scanf("%d", &p[i].pr);
        
        p[i].ct = 0;
    	p[i].tat = 0;
    	p[i].wt = 0;
    	p[i].rt = 0;
    }
		
    // Print entered table
    printTable(p, n, "The Process Table");

    // FCFS
    copy(temp, p, n);
    float wt_fcfs = FCFS(temp, n);
    printTable(temp, n, "FCFS Scheduling");

    // SRTF
    copy(temp, p, n);
    float wt_srtf = SRTF(temp, n);
    printTable(temp, n, "SRTF Scheduling");

    // Priority
    copy(temp, p, n);
    float wt_pr = Priority(temp, n);
    printTable(temp, n, "Priority Scheduling");

    // Round Robin
    copy(temp, p, n);
    float wt_rr = RR(temp, n);
    printTable(temp, n, "Round Robin Scheduling");

    // Average table
    printf("-------------------------\n");
    printf(" Average Waiting Times \n");
    printf("-------------------------\n");
    printf("Algorithm\tAverage WT\n");
    printf("FCFS\t\t%.2f\n", wt_fcfs);
    printf("SRTF\t\t%.2f\n", wt_srtf);
    printf("Priority\t%.2f\n", wt_pr);
    printf("Round Robin\t%.2f\n", wt_rr);

    // Minimum
    float min = wt_fcfs;
    char algo[20];
    strcpy(algo, "FCFS");
    if (wt_srtf < min)  { min = wt_srtf; strcpy(algo, "SRTF"); }
    if (wt_pr < min)    { min = wt_pr;   strcpy(algo, "Priority"); }
    if (wt_rr < min)    { min = wt_rr;   strcpy(algo, "Round Robin"); }

    printf("\nMinimum Average Waiting Time: %s (%.2f)\n", algo, min);

    return 0;
}

