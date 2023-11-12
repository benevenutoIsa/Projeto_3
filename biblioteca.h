typedef enum {
    COMPLETO,
    EM_ANDAMENTO,
    NAO_INICIADO
} EstadoTarefa;

typedef struct {
    int prioridade;
    int numTarefa;
    char descricao[301];
    char categoria[101];
    EstadoTarefa estado;
} Tarefa;

//essas funções foram implementadas no projeto 1 mas fiz algumas alterações
void menu();
void escreverTarefa(Tarefa *tarefa);
void salvarStruct(const Tarefa *tarefa, int n, const char *arquivoBin);
void lerStruct(Tarefa *tarefa, char *arquivoBin);
void listarStruct(const Tarefa *tarefa, int n);
void excluir(Tarefa *tarefa, int numTarefa, int *n);

//já essas funções são novas especificadamente do projjeto 3
void alterarTarefas(Tarefa *tarefa, int n);
void filtrarPrioridade(const Tarefa *tarefa, int n, int prioridade);
void filtrarEstado(const Tarefa *tarefa, int n, EstadoTarefa estado);
void filtrarCategoria(const Tarefa *tarefa, int n, const char *categoria);
void filtrarPrioridadeCategoria(const Tarefa *tarefa, int n, int prioridade, const char *categoria);
void exportarPrioridade(const Tarefa *tarefa, int n, int prioridade, const char *nomeArquivo);
void exportarCategoria(const Tarefa *tarefa, int n, const char *categoria, const char *nomeArquivo);
void exportarPrioridadeCategoria(const Tarefa *tarefa, int n, int prioridade, const char *categoria, const char *nomeArquivo);
