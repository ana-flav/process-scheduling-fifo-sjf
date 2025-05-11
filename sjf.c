#include <stdio.h>

#define NUM_PROCESSOS 5

struct Processo {
    int id;
    int tempo_chegada;
    int tempo_execucao;
    int tempo_espera;
    int tempo_saida;
    int tempo_turnaround;
    int concluido;
    int ordem_execucao;
};


int encontrarProcessoMaisCurto(struct Processo processos[], int tempo_atual, int n) {
    int menor_tempo = 1e9;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (!processos[i].concluido && processos[i].tempo_chegada <= tempo_atual &&
            processos[i].tempo_execucao < menor_tempo) {
            menor_tempo = processos[i].tempo_execucao;
            index = i;
        }
    }
    return index;
}



void calcularSJF(struct Processo processos[], int n) {
    int tempo_atual = 0, completados = 0;

    while (completados < n) {
        int idx = encontrarProcessoMaisCurto(processos, tempo_atual, n);

        if (idx == -1) {
            tempo_atual++;
            continue;
        }

        processos[idx].tempo_espera = tempo_atual - processos[idx].tempo_chegada;
        tempo_atual += processos[idx].tempo_execucao;
        processos[idx].tempo_saida = tempo_atual;
        processos[idx].tempo_turnaround = processos[idx].tempo_saida - processos[idx].tempo_chegada;
        processos[idx].concluido = 1;
        processos[idx].ordem_execucao = completados + 1;
        completados++;
    }
}


void imprimirResultado(struct Processo processos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processos[j].ordem_execucao > processos[j + 1].ordem_execucao) {
                struct Processo temp = processos[j];
                processos[j] = processos[j + 1];
                processos[j + 1] = temp;
            }
        }
    }

    printf("Ordem | ID | Chegada | Execução | Espera | Saída | Turnaround\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("  %2d   | P%d |   %2d     |    %2d    |   %2d   |  %2d  |     %2d\n",
            processos[i].ordem_execucao,
            processos[i].id,
            processos[i].tempo_chegada,
            processos[i].tempo_execucao,
            processos[i].tempo_espera,
            processos[i].tempo_saida,
            processos[i].tempo_turnaround);
    }
}


int main() {
    struct Processo processos[NUM_PROCESSOS] = {
        {1, 0, 6, 0, 0, 0, 0, 0},
        {2, 1, 8, 0, 0, 0, 0, 0},
        {3, 2, 7, 0, 0, 0, 0, 0},
        {4, 3, 3, 0, 0, 0, 0, 0},
        {5, 5, 4, 0, 0, 0, 0, 0},
    };

    calcularSJF(processos, NUM_PROCESSOS);
    imprimirResultado(processos, NUM_PROCESSOS);

    return 0;
}
