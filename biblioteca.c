#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca.h"

void clear_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int Cadastrar_Tarefas(STarefas tarefas[], int* numero_de_tarefas) {

    if (*numero_de_tarefas >= 100) {
        printf("Voce atingiu o limite de 100 tarefas, nao eh continuar cadastrando mais tarefas.\n");
        return 0;
    }

    STarefas criar_tarefa;
    printf("Coloque a prioridade da sua tarefa entre 1 e 10: \n");
    scanf("%d", &criar_tarefa.prioridade);

    printf("Coloque a descricao da sua tarefa ( maximo de 300 caracteres): \n");
    clear_buffer();
    fgets(criar_tarefa.descricao, sizeof(criar_tarefa.descricao), stdin);

    printf("Classifique a categoria da tarefa (maximo de 100 caracteres): \n");
    fgets(criar_tarefa.categoria, sizeof(criar_tarefa.categoria), stdin);

    printf("Estado da tarefa (maximo de 50 caracteres): \n");
    fgets(criar_tarefa.estado, sizeof(criar_tarefa.estado), stdin);

    tarefas[*numero_de_tarefas] = criar_tarefa;
    (*numero_de_tarefas)++;
    Salvar_Tarefas(tarefas, *numero_de_tarefas);

    printf("Tarefa cadastrada.\n");

    return 1;
}

int Listar_Tarefas(STarefas tarefas[], int numero_de_tarefas) {
    if (numero_de_tarefas == 0) {
        printf("\n");
        printf("Sua lista de tarefas esta vazia.\n");
        return 0;
    } else {
        printf("\n");
        printf("Sua lista de tarefas:\n");

        for (int i = 0; i < numero_de_tarefas; i++) {
            printf("\n");
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
            printf("Estado: %s\n", tarefas[i].estado);
            printf("---------------------------------------------------------\n");
        }

        return numero_de_tarefas;
    }
}