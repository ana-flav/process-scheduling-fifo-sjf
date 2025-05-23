#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int started;
} Process;

int main() {
    int n = 4;
    int completed = 0, current_time = 0, min_priority, index;

    Process p[MAX] = {
        {1, 0, 5, 5, 2, 0, 0, 0, 0},
        {2, 1, 3, 3, 1, 0, 0, 0, 0},
        {3, 2, 8, 8, 4, 0, 0, 0, 0},
        {4, 3, 6, 6, 3, 0, 0, 0, 0}
    };

    int timeline[100];

    while (completed < n) {
        min_priority = 9999;
        index = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                index = i;
            }
        }

        if (index != -1) {
            timeline[current_time] = p[index].pid;

            p[index].remaining_time--;
            current_time++;

            if (!p[index].started) {
                p[index].started = 1;
            }

            if (p[index].remaining_time == 0) {
                completed++;
                p[index].completion_time = current_time;
                p[index].turnaround_time = p[index].completion_time - p[index].arrival_time;
                p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;
            }
        } else {
            timeline[current_time] = -1;
            current_time++;
        }
    }

    float avg_waiting_time = 0, avg_turnaround_time = 0;
    printf("\nResumo dos Processos:\n");
    printf("PID\tChegada\tBurst\tPrioridade\tEspera\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority,
               p[i].waiting_time, p[i].turnaround_time);
        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turnaround_time;
    }

    printf("\nTempo médio de espera: %.2f", avg_waiting_time / n);
    printf("\nTempo médio de turnaround: %.2f\n", avg_turnaround_time / n);


    printf("\nGantt Chart:\n|");
    for (int i = 0; i < current_time; i++) {
        if (timeline[i] == -1)
            printf("  -  |");
        else
            printf(" P%d |", timeline[i]);
    }
    printf("\n");


    printf(" ");
    for (int i = 0; i <= current_time; i++) {
        printf("%2d   ", i);
    }
    printf("\n");

    return 0;
}
