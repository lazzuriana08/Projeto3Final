
#ifndef PROJETO3FINAL_BIBLIOTECA_H
#define PROJETO3FINAL_BIBLIOTECA_H
typedef struct {
    int prioridade;
    char descricao[300];
    char categoria[100];
    char estado [50];
}STarefas;

int Salvar_Tarefas(STarefas tarefas[], int numero_de_tarefas);

int Carregar_Tarefas(STarefas tarefas[]);

int Cadastrar_Tarefas(STarefas tarefas[], int* numero_de_tarefas);

int Listar_Tarefas(STarefas tarefas[], int numero_de_tarefas);

void Deletar_Tarefa(STarefas tarefas[], int *numero_de_tarefas, char cate[], int priori);

void FiltrarTarefas(STarefas tarefas[], int numero_de_tarefas);
void FiltrarPorPrioridade(STarefas tarefas[], int numero_de_tarefas);
void FiltrarPorCategoria(STarefas tarefas[], int numero_de_tarefas);
void FiltrarPorEstado(STarefas tarefas[], int numero_de_tarefas);
void FiltrarPorPrioridadeECategoria(STarefas tarefas[], int numero_de_tarefas);

int CompararPorPrioridade(const void *a, const void *b);

int AlterarTarefas(STarefas tarefas[], int numero_de_tarefas);

void ExportarTarefasPorPrioridade(STarefas tarefas[], int numero_de_tarefas, int prioridade);
void ExportarTarefasPorCategoria(STarefas tarefas[], int numero_de_tarefas, char categoria[]);
void ExportarTarefasPorPrioridadeECategoria(STarefas tarefas[], int numero_de_tarefas, int prioridade, char categoria[]);

#endif //PROJETO3FINAL_BIBLIOTECA_H
