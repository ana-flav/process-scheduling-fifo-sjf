#include <stdio.h>

struct Processo {
    int id;
    int tempo_chegada;
    int tempo_execucao;
    int tempo_espera;
    int tempo_saida;
};

void ordenarPorChegada(struct Processo p[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].tempo_chegada > p[j].tempo_chegada) {
                struct Processo temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
}

void escalonar(struct Processo p[], int n) {
    int tempo_atual = 0;
    for (int i = 0; i < n; i++) {
        if (tempo_atual < p[i].tempo_chegada)
            tempo_atual = p[i].tempo_chegada;
        p[i].tempo_espera = tempo_atual - p[i].tempo_chegada;
        tempo_atual += p[i].tempo_execucao;
        p[i].tempo_saida = tempo_atual;
    }
}

void imprimirTabela(struct Processo p[], int n) {
    printf("ID | Chegada | Execucao | Espera | Saida\n");
    for (int i = 0; i < n; i++) {
        printf("P%d |    %d     |    %d     |   %d   |  %d\n",
               p[i].id, p[i].tempo_chegada, p[i].tempo_execucao,
               p[i].tempo_espera, p[i].tempo_saida);
    }
}


void imprimirGantt(struct Processo p[], int n) {
    printf("\nGráfico de Gantt (FIFO):\n ");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].tempo_execucao; j++)
            printf("--");
        printf(" ");
    }

    printf("\n|");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].tempo_execucao - 1; j++)
            printf(" ");
        printf("P%d", p[i].id);
        for (int j = 0; j < p[i].tempo_execucao - 1; j++)
            printf(" ");
        printf("|");
    }

    printf("\n ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].tempo_execucao; j++)
            printf("--");
        printf(" ");
    }


    printf("\n0");
    for (int i = 0; i < n; i++) {
        int espacos = p[i].tempo_saida - (i > 0 ? p[i - 1].tempo_saida : 0);
        for (int j = 0; j < espacos * 2 - 1; j++)
            printf(" ");
        printf("%d", p[i].tempo_saida);
    }
    printf("\n");
}

int main() {
    int n = 4;
    struct Processo processos[] = {
        {1, 0, 6},
        {2, 1, 8},
        {3, 2, 7},
        {4, 3, 3}
    };

    printf("=== Escalonamento FIFO ===\n");
    ordenarPorChegada(processos, n);
    escalonar(processos, n);
    imprimirTabela(processos, n);
    imprimirGantt(processos, n);

    return 0;
}
