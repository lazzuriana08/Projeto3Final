#include <stdio.h>
#include "biblioteca.h"

int main() {
    STarefas tarefas[100];
    int numero_de_tarefas = Carregar_Tarefas(tarefas);


    int escolha;
    while(1){
        printf("Escolha uma operacao do menu: ");
        printf("\n");
        printf("1. Cadastrar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Deletar Tarefa\n");
        printf("4. Filtrar Tarefas\n");
        printf("5. Alterar Tarefas\n");
        printf("6. Exportar Tarefas\n");
        printf("7. Sair\n");
        scanf("%d", &escolha);

        int opcaoExportar;
        int prioridadeExportar;
        char categoriaExportar[100];
        switch (escolha) {
            case 1:
                Cadastrar_Tarefas(tarefas, &numero_de_tarefas);
                break;
            case 2:
                Listar_Tarefas(tarefas, numero_de_tarefas);
                break;
            case 3:
                if (numero_de_tarefas > 0) {
                    int priori;
                    char cate[100];
                    printf("Coloque a prioridade da tarefa que deseja excluir: ");
                    scanf("%d", &priori);
                    printf("Coloque a categoria da tarefa que deseja excluir: ");
                    clear_buffer();
                    fgets(cate, sizeof(cate), stdin);
                    Deletar_Tarefa(tarefas, &numero_de_tarefas, cate, priori);
                } else {
                    printf("A lista de tarefas esta vazia.\n");
                }
                break;
            case 4:
                FiltrarTarefas(tarefas, numero_de_tarefas);
                break;
            case 5:
                AlterarTarefas(tarefas, numero_de_tarefas);
                break;
            case 6:
                printf("Escolha uma opcao de exportacao: ");
                printf("1. Exportar Tarefas por Prioridade\n");
                printf("2. Exportar Tarefas por Categoria\n");
                printf("3. Exportar Tarefas por Prioridade e Categoria\n");
                scanf("%d", &opcaoExportar);

                switch (opcaoExportar) {
                    case 1:

                        printf("Digite a prioridade: ");
                        scanf("%d", &prioridadeExportar);
                        ExportarTarefasPorPrioridade(tarefas, numero_de_tarefas, prioridadeExportar);
                        break;
                    case 2:
                        printf("Digite a categoria: ");
                        clear_buffer();
                        fgets(categoriaExportar, sizeof(categoriaExportar), stdin);
                        ExportarTarefasPorCategoria(tarefas, numero_de_tarefas, categoriaExportar);
                        break;
                    case 3:
                        printf("Digite a prioridade: ");
                        scanf("%d", &prioridadeExportar);
                        printf("Digite a categoria: ");
                        clear_buffer();
                        fgets(categoriaExportar, sizeof(categoriaExportar), stdin);
                        ExportarTarefasPorPrioridadeECategoria(tarefas, numero_de_tarefas, prioridadeExportar, categoriaExportar);
                        break;
                    default:
                        printf("Essa opcao nao existe.\n");
                        break;
                }
                break;
            case 7:
                printf("Sessao encerrada\n");
                break;
            default:
                printf("Essa opcao nao existe.\n");
                break;
        }
    }
}
