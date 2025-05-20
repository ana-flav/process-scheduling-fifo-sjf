#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void roundRobin(int burst_time[], int no_of_processes, int quantum);
void drawGanttChart(int burst_time[], int no_of_processes, int quantum);


int main(void)
{
    int no_of_processes = 4;  // Número de processos
    int bt[MAX] = {5, 15, 4, 3};  // Tempos de burst fixos para os processos
    int quantum = 5;  // Quantum fixo

    printf("Número de processos: %d\n", no_of_processes);
    printf("Tempos de burst:\n");
    for (int i = 0; i < no_of_processes; ++i) {
        printf("P%d = %d\n", i + 1, bt[i]);
    }
    printf("Quantum: %d\n\n", quantum);

    roundRobin(bt, no_of_processes, quantum);

    printf("\n\n");

    return 0;
}

void drawGanttChart(int burst_time[], int no_of_processes, int quantum)
{
    int remaining_time[MAX];
    int remain = no_of_processes;
    int time = 0;
    int exec_time[MAX * 10];   // Execução em ordem
    int exec_proc[MAX * 10];   // Processos em ordem
    int exec_count = 0;

    for (int i = 0; i < no_of_processes; ++i)
        remaining_time[i] = burst_time[i];

    for (int process = 0; remain != 0;)
    {
        if (remaining_time[process] > 0)
        {
            int t_exec = (remaining_time[process] <= quantum) ? remaining_time[process] : quantum;

            exec_proc[exec_count] = process + 1;
            exec_time[exec_count] = time;
            exec_count++;

            time += t_exec;
            remaining_time[process] -= t_exec;

            if (remaining_time[process] == 0)
                --remain;
        }

        process = (process + 1) % no_of_processes;
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n\n");
    for (int i = 0; i < exec_count; i++)
        printf("|P%d ", exec_proc[i]);
    printf("|\n");

    for (int i = 0; i < exec_count; i++)
        printf("%-4d", exec_time[i]);
    printf("%d\n\n", time);
}

void roundRobin(int burst_time[], int no_of_processes, int quantum)
{
    int remaining_time[no_of_processes];     //Temporary array for storing the remaining time of each process.
    int waiting_time = 0;       //Total waiting time.
    int turnaround_time = 0;    //Total turnaround time.
    int flag = 0;

    // Copy the burst times of each process into the temporary array.
    for (int i = 0; i < no_of_processes; ++i)
    {
        remaining_time[i] = burst_time[i];
    }

    int process = 0;            //Current process.
    int time = 0;               //Turnaround around time of each process.
    int remain = no_of_processes;

    printf("Process No.\t\tWaiting Time\tTurnaround Time\n");

    while (remain != 0)
    {
        // Remaining time is less than the quantum and also greater than 0.
        if (remaining_time[process] <= quantum && remaining_time[process] > 0)
        {
            time += remaining_time[process]; // The remaining time is added to the turnaround time of the process.
            remaining_time[process] = 0;    //Since the remaining time is lower than the quantum we set it to 0.

            flag = 1;
        }

        // Remaining time is greater than 0.
        else if (remaining_time[process] > 0)
        {
            time += quantum;
            remaining_time[process] -= quantum;
        }

        // Execute only if the remaining time of a process is set to 0.
        // Cannot enter this statement if the remaining time evaluates to 0 in line 155.
        if (flag == 1)
        {
            --remain;
            printf("Process[%d]\t\t\t%d\t\t\t\t%d\n", process + 1, time - burst_time[process], time);
            waiting_time += time - burst_time[process];
            turnaround_time += time;

            flag = 0;
        }

        // Check if the maximum number of processes is reached.
        if (process == no_of_processes - 1)
        {
            process = 0;    // If yes, go back to the first process.
        }

        else
        {
            ++process;  // Else, go to the next process.
        }
    }

    drawGanttChart(burst_time, no_of_processes, quantum);

    printf("Average turnaround time: %.2f\n", (float) turnaround_time / no_of_processes);
    printf("Average waiting time: %.2f", (float) waiting_time / no_of_processes);
}



