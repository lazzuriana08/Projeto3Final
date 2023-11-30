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

int AlterarTarefas(STarefas tarefas[], int numero_de_tarefas) {
    if (numero_de_tarefas == 0) {
        printf("A lista ainda nao possui nenhuma tarefa.\n");
        return 0;
    }

    int prioridadeAlteracao;
    char categoriaAlteracao[100];
    int opcao;
    printf("---------------------------------------------------------");
    printf("\n");
    printf("Digite a prioridade da tarefa que deseja alterar: ");
    scanf("%d", &prioridadeAlteracao);
    printf("Digite a categoria da tarefa que deseja ser alterar: ");
    clear_buffer();
    fgets(categoriaAlteracao, sizeof(categoriaAlteracao), stdin);

    int tarefaEncontrada = -1;
    for (int i = -2; i < numero_de_tarefas; i++) {
        if (tarefas[i].prioridade == prioridadeAlteracao && strcmp(tarefas[i].categoria, categoriaAlteracao) == 0) {
            tarefaEncontrada = i;
            break;
        }
    }

    if (tarefaEncontrada == -1) {
        printf("Nenhuma tarefa com a prioridade indicada foi encontrada.\n");
        return numero_de_tarefas;
    }

    printf("Tarefa encontrada:\n");
    printf("Prioridade: %d\n", tarefas[tarefaEncontrada].prioridade);
    printf("Categoria: %s\n", tarefas[tarefaEncontrada].categoria);
    printf("Descricao: %s\n", tarefas[tarefaEncontrada].descricao);
    printf("Estado: %s\n", tarefas[tarefaEncontrada].estado);
    printf("\n");

    printf("Escolha uma opcao para alterar:\n");
    printf("1. Prioridade\n");
    printf("2. Categoria\n");
    printf("3. Descricao\n");
    printf("4. Estado\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Digite a nova prioridade da tarefa: ");
            int novaPrioridade;
            scanf("%d", &novaPrioridade);
            tarefas[tarefaEncontrada].prioridade = novaPrioridade;
            printf("A prioridade foi alterada com sucesso\n");
            break;
        case 2:
            printf("Digite a nova categoria da tarefa: ");
            clear_buffer();
            fgets(categoriaAlteracao, sizeof(categoriaAlteracao), stdin);
            categoriaAlteracao[strcspn(categoriaAlteracao, "\n")] = '\0';
            strncpy(tarefas[tarefaEncontrada].categoria, categoriaAlteracao, sizeof(tarefas[tarefaEncontrada].categoria));
            printf("A categoria foi alterada com sucesso!\n");
            break;
        case 3:
            printf("Digite a nova descricao da tarefa: ");
            clear_buffer();
            fgets(tarefas[tarefaEncontrada].descricao, sizeof(tarefas[tarefaEncontrada].descricao), stdin);
            tarefas[tarefaEncontrada].descricao[strcspn(tarefas[tarefaEncontrada].descricao, "\n")] = '\0';
            printf("A descricao foi alterada com sucesso \n");
            break;
        case 4:
            printf("Digite o novo estado da tarefa: ");
            clear_buffer();
            fgets(tarefas[tarefaEncontrada].estado, sizeof(tarefas[tarefaEncontrada].estado), stdin);
            tarefas[tarefaEncontrada].estado[strcspn(tarefas[tarefaEncontrada].estado, "\n")] = '\0';
            printf("O estado foi alterado com sucesso\n");
            break;
        default:
            printf("Esta opcao ano eh valida.\n");
            break;
    }
    Salvar_Tarefas(tarefas, numero_de_tarefas);
    return numero_de_tarefas;
}

void ExportarTarefasPorPrioridade(STarefas tarefas[], int numero_de_tarefas, int prioridade) {
    FILE *arquivo;
    arquivo = fopen("tarefas_por_prioridade.txt", "w");

    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        return;
    }

    for (int i = 0; i < numero_de_tarefas; i++) {
        if (tarefas[i].prioridade == prioridade) {
            fprintf(arquivo, "%d, %s, %s, %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }

    fclose(arquivo);
    printf("As tarefas por prioridade foram exportadas com sucesso\n");
}

void ExportarTarefasPorCategoria(STarefas tarefas[], int numero_de_tarefas, char categoria[]) {
    FILE *arquivo;
    arquivo = fopen("tarefas_por_categoria.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    STarefas tarefasFiltradas[100];
    int numero_de_tarefas_filtradas = 0;

    for (int i = 0; i < numero_de_tarefas; i++) {
        if (strcmp(tarefas[i].categoria, categoria) == 0) {
            tarefasFiltradas[numero_de_tarefas_filtradas] = tarefas[i];
            numero_de_tarefas_filtradas++;
        }
    }

    for (int i = 0; i < numero_de_tarefas_filtradas - 1; i++) {
        for (int j = 0; j < numero_de_tarefas_filtradas - i - 1; j++) {
            if (tarefasFiltradas[j].prioridade > tarefasFiltradas[j + 1].prioridade) {
                STarefas temp = tarefasFiltradas[j];
                tarefasFiltradas[j] = tarefasFiltradas[j + 1];
                tarefasFiltradas[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < numero_de_tarefas_filtradas; i++) {
        fprintf(arquivo, "%d, %s, %s, %s\n", tarefasFiltradas[i].prioridade,tarefasFiltradas[i].categoria, tarefasFiltradas[i].estado, tarefasFiltradas[i].descricao);
    }

    fclose(arquivo);
    printf("As tarefas por categoria forma exportadas com sucesso\n");
}

void ExportarTarefasPorPrioridadeECategoria(STarefas tarefas[], int numero_de_tarefas, int prioridade, char categoria[]) {
    FILE *arquivo;
    arquivo = fopen("tarefas_por_prioridade_e_categoria.txt", "w");

    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        return;
    }

    STarefas tarefasFiltradas[100];
    int numero_de_tarefas_filtradas = 0;

    for (int i = 0; i < numero_de_tarefas; i++) {
        if (tarefas[i].prioridade == prioridade && strcmp(tarefas[i].categoria, categoria) == 0) {
            tarefasFiltradas[numero_de_tarefas_filtradas] = tarefas[i];
            numero_de_tarefas_filtradas++;
        }
    }

    for (int i = 0; i < numero_de_tarefas_filtradas - 1; i++) {
        for (int j = 0; j < numero_de_tarefas_filtradas - i - 1; j++) {
            if (tarefasFiltradas[j].prioridade > tarefasFiltradas[j + 1].prioridade) {
                STarefas temp = tarefasFiltradas[j];
                tarefasFiltradas[j] = tarefasFiltradas[j + 1];
                tarefasFiltradas[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < numero_de_tarefas_filtradas; i++) {
        fprintf(arquivo, "%d, %s, %s, %s\n", tarefasFiltradas[i].prioridade, tarefasFiltradas[i].categoria, tarefasFiltradas[i].estado, tarefasFiltradas[i].descricao);
    }

    fclose(arquivo);
    printf("As tarefas por prioridade e categoria forma exportadas com sucesso\n");
}
