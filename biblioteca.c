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
