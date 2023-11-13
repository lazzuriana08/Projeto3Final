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