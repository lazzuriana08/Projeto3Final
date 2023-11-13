
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
