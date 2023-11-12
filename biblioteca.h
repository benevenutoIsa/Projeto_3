//usei typedef enum para facilitar pra mim na hora de criar as funcoes, fica menos repetitivo e com menos chance de errar

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
void alterar(Tarefa *tarefa, int n);
void filtrarP(const Tarefa *tarefa, int n, int prioridade);
void filtrarE(const Tarefa *tarefa, int n, EstadoTarefa estado);
void filtrarC(const Tarefa *tarefa, int n, const char *categoria);
void filtrarPC(const Tarefa *tarefa, int n, int prioridade, const char *categoria);
void exportarP(const Tarefa *tarefa, int n, int prioridade, const char *nomeArquivo);
void exportarC(const Tarefa *tarefa, int n, const char *categoria, const char *nomeArquivo);
void exportarPC(const Tarefa *tarefa, int n, int prioridade, const char *categoria, const char *nomeArquivo);
