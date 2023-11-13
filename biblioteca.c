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
