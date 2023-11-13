<<<<<<< HEAD
<<<<<<< HEAD
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
=======
void Deletar_Tarefa(STarefas tarefas[], int *numero_de_tarefas, char cate[], int priori) {
    int localizar_tarefa = 0;
    int i;
    for (i = 0; i < *numero_de_tarefas; i++) {
        if (tarefas[i].prioridade == priori && strcmp(tarefas[i].categoria, cate) == 0) {
            localizar_tarefa = 1;
            break;
        }
    }
    if (localizar_tarefa) {
        for (int j = i; j < *numero_de_tarefas - 1; j++) {
            tarefas[j] = tarefas[j + 1];
        }
        (*numero_de_tarefas)--;
        Salvar_Tarefas(tarefas, *numero_de_tarefas);
        printf("A tarefa foi excluida\n");
        printf("\n");
    } else {
        printf("Tarefa nao localizada.\n");
    }
}

int Salvar_Tarefas(STarefas tarefas[], int numero_de_tarefas) {
    FILE *arquivo = fopen("Projeto_Tarefas.bin", "wb");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return 1;
    }
    fwrite(tarefas, sizeof(STarefas), numero_de_tarefas, arquivo);
    fclose(arquivo);
    return 0;
}

int Carregar_Tarefas(STarefas tarefas[]) {
    FILE *arquivo = fopen("Projeto_Tarefas.bin", "rb");
    if (arquivo == NULL) {
        printf("Este arquivo nao existe.\n");
        return 0;
    }
    int numero_de_tarefas = 0;
    while (fread(&tarefas[numero_de_tarefas], sizeof(STarefas), 1, arquivo) == 1) {
        numero_de_tarefas++;
    }
    fclose(arquivo);
    return numero_de_tarefas;
}

=======
>>>>>>> Filtros
void FiltrarTarefas(STarefas tarefas[], int numero_de_tarefas) {
    int escolha;
    printf("Escolha uma opcao de filtro: ");
    printf("1. Prioridade\n");
    printf("2. Categoria\n");
    printf("3. Estado\n");
    printf("4. Prioridade e Categoria\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            FiltrarPorPrioridade(tarefas, numero_de_tarefas);
            break;
        case 2:
            FiltrarPorCategoria(tarefas, numero_de_tarefas);
            break;
        case 3:
            FiltrarPorEstado(tarefas, numero_de_tarefas);
            break;
        case 4:
            FiltrarPorPrioridadeECategoria(tarefas, numero_de_tarefas);
            break;
        default:
            printf("Esta opcao nao eh valida.\n");
            break;
<<<<<<< HEAD
>>>>>>> DeletarSalvareCarregar
    }
}
=======
    }
}

int CompararPorPrioridade(const void *a, const void *b) {
    return ((STarefas*)a)->prioridade - ((STarefas*)b)->prioridade;
}

void FiltrarPorPrioridade(STarefas tarefas[], int numero_de_tarefas) {
    int prioridade;
    printf("Digite a prioridade que deseja filtrar as tarefas: ");
    scanf("%d", &prioridade);

    printf("Tarefas filtradas por prioridade:\n");
    for (int i = 0; i < numero_de_tarefas; i++) {
        if (tarefas[i].prioridade == prioridade) {
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
            printf("Estado: %s\n", tarefas[i].estado);
            printf("\n");
            printf("---------------------------------------------------------\n");
        }
    }
}

void FiltrarPorCategoria(STarefas tarefas[], int numero_de_tarefas) {
    char categoria[100];
    printf("Digite a categoria para filtrar as tarefas: ");
    clear_buffer();
    fgets(categoria, sizeof(categoria), stdin);

    int tarefasFiltradas = 0;
    STarefas tarefasFiltradasArray[numero_de_tarefas];

    for (int i = 0; i < numero_de_tarefas; i++) {
        if (strcmp(tarefas[i].categoria, categoria) == 0) {
            tarefasFiltradasArray[tarefasFiltradas++] = tarefas[i];
        }
    }

    if (tarefasFiltradas == 0) {
        printf("Nenhuma tarefa com a categoria indicada foi encotrada.\n");
        return;
    }

    qsort(tarefasFiltradasArray, tarefasFiltradas, sizeof(STarefas), CompararPorPrioridade);

    printf("Tarefas filtradas por categoria :\n");
    for (int i = 0; i < tarefasFiltradas; i++) {
        printf("Categoria: %s\n", tarefasFiltradasArray[i].categoria);
        printf("Prioridade: %d\n", tarefasFiltradasArray[i].prioridade);
        printf("Descricao: %s\n", tarefasFiltradasArray[i].descricao);
        printf("Estado: %s\n", tarefasFiltradasArray[i].estado);
        printf("\n");
        printf("---------------------------------------------------------\n");
    }
}

void FiltrarPorEstado(STarefas tarefas[], int numero_de_tarefas) {
    char estado[100];
    printf("Digite a categoria para filtrar as tarefas: ");
    clear_buffer();
    fgets(estado, sizeof(estado), stdin);

    int tarefasFiltradas = 0;
    STarefas tarefasFiltradasArray[numero_de_tarefas];

    for (int i = 0; i < numero_de_tarefas; i++) {
        if (strcmp(tarefas[i].estado, estado) == 0) {
            tarefasFiltradasArray[tarefasFiltradas++] = tarefas[i];
        }
    }

    if (tarefasFiltradas == 0) {
        printf("Nenhuma tarefa com o estado indicado foi encontrada.\n");
        return;
    }

    qsort(tarefasFiltradasArray, tarefasFiltradas, sizeof(STarefas), CompararPorPrioridade);

    printf("Tarefas filtradas por estado:\n");
    for (int i = 0; i < tarefasFiltradas; i++) {
        printf("Estado: %s\n", tarefasFiltradasArray[i].estado);
        printf("Prioridade: %d\n", tarefasFiltradasArray[i].prioridade);
        printf("Categoria: %s\n", tarefasFiltradasArray[i].categoria);
        printf("Descricao: %s\n", tarefasFiltradasArray[i].descricao);
        printf("\n");
        printf("---------------------------------------------------------\n");
    }
}

void FiltrarPorPrioridadeECategoria(STarefas tarefas[], int numero_de_tarefas) {
    int prioridade;
    char categoria[100];
    printf("Digite a prioridade para filtrar as tarefas: ");
    scanf("%d", &prioridade);
    printf("Digite a categoria para filtrar as tarefas: ");
    clear_buffer();
    fgets(categoria, sizeof(categoria), stdin);

    int tarefasFiltradas = 0;
    STarefas tarefasFiltradasArray[numero_de_tarefas];

    for (int i = 0; i < numero_de_tarefas; i++) {
        if (tarefas[i].prioridade == prioridade && strcmp(tarefas[i].categoria, categoria) == 0) {
            tarefasFiltradasArray[tarefasFiltradas++] = tarefas[i];
        }
    }

    if (tarefasFiltradas == 0) {
        printf("Nenhuma tarefa com a prioridade e catgoria indicada foi encontrada.\n");
        return;
    }

    qsort(tarefasFiltradasArray, tarefasFiltradas, sizeof(STarefas), CompararPorPrioridade);

    printf("Tarefas filtradas por prioridade e categoria:\n");
    for (int i = 0; i < tarefasFiltradas; i++) {
        printf("Prioridade: %d\n", tarefasFiltradasArray[i].prioridade);
        printf("Categoria: %s\n", tarefasFiltradasArray[i].categoria);
        printf("Estado: %s\n", tarefasFiltradasArray[i].estado);
        printf("Descricao: %s\n", tarefasFiltradasArray[i].descricao);
        printf("\n");
        printf("---------------------------------------------------------\n");
    }
}
>>>>>>> Filtros
