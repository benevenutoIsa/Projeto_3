#include "biblioteca.h"
#include <stdio.h>
#include <string.h>

// essa função apenas imprime as opçoes disponiveis do programa
void menu() {
    printf("Selecione uma opcao: \n");
    printf("1- Adicionar tarefa \n");
    printf("2- Listar todas as tarefas\n");
    printf("3- Excluir tarefa\n");
    printf("4- Estado da tarefa\n");
    printf("5- Filtrar por Prioridade \n");
    printf("6- Filtrar por Estado \n");
    printf("7- Filtrar por Categoria e Ordenar por Prioridade \n");
    printf("8- Filtrar tarefas por prioridade e categoria \n");
    printf("9- Exportar por Prioridade \n");
    printf("10- Exportar por Categoria \n");
    printf("11- Exportar por Prioridade e Categoria \n");
    printf("0- Sair\n");
}

// essa função pega os dados que o  usuario escreveu e armazena em uma estrutura
void escreverTarefa(Tarefa *tarefa) {
    printf("Digite a prioridade da tarefa:\n");
    scanf("%d", &tarefa->prioridade);

    //lê a linha de texto fornecida pelo usuárop e armazena no campo da estrutura
    printf("Descreva a tarefa:\n");
    getchar();
    fgets(tarefa->descricao, sizeof(tarefa->descricao), stdin);
    tarefa->descricao[strcspn(tarefa->descricao, "\n")] = '\0';

    printf("Digite a categoria:\n");
    fgets(tarefa->categoria, sizeof(tarefa->categoria), stdin);

    //remove o caractere da nova linha para a string ser salva corretamente
    tarefa->categoria[strcspn(tarefa->categoria, "\n")] = '\0';

    printf("Digite o estado da tarefa (1- Completo, 2- Em andamento, 3- Não iniciado):\n");
    int opcaoEstado;
    scanf("%d", &opcaoEstado);
    switch (opcaoEstado) {
        case 1:
            tarefa->estado = COMPLETO;
            break;
        case 2:
            tarefa->estado = EM_ANDAMENTO;
            break;
        case 3:
            tarefa->estado = NAO_INICIADO;
            break;
        default:
            printf("Esta opcao é invalida para estado, sendo assim sera marcada como Não iniciado.\n");
            tarefa->estado = NAO_INICIADO;
    }

    printf("Tarefa adcionada com sucesso!\n");
}

// nessa função é salvo as coisas escritas pelo usuario no aquivoBin, com uma verificação caso ele não seja aberto corretamente
void salvarStruct(const Tarefa *tarefa, int n, const char *arquivoBin) {
    FILE *arquivo = fopen(arquivoBin, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fwrite(tarefa, sizeof(Tarefa), n, arquivo);
    fclose(arquivo);

    printf("Tarefa salva com sucesso!\n");
}

// aqui também é usado um ponteiro para um vetor de struct para os dados serem armazenados e depois há uma verificação se o arquivo foi aberto e uma iteração para realizar a leitura das tarefas e depois fecha
void lerStruct(Tarefa *tarefa, char *arquivoBin) {
    FILE *arquivo = fopen(arquivoBin, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int i = 0;
    while (fread(&tarefa[i], sizeof(Tarefa), 1, arquivo)) {
        i++;
    }

    fclose(arquivo);
}

//nessa função ele printa todas as tarefas
void listarStruct(const Tarefa *tarefa, int n) {
    printf("Listando todas as tarefas:\n");
    for (int i = 0; i < n; i++) {
        printf("Prioridade: %d\n", tarefa[i].prioridade);
        printf("Descricao: %s\n", tarefa[i].descricao);
        printf("Categoria: %s\n", tarefa[i].categoria);
        switch (tarefa[i].estado) {
            case COMPLETO:
                printf("Estado: Completo\n");
                break;
            case EM_ANDAMENTO:
                printf("Estado: Em andamento\n");
                break;
            case NAO_INICIADO:
                printf("Estado: Não iniciado\n");
                break;
            default:
                printf("Estado: Desconhecido\n");
        }
        printf("\n");
    }
}

//nesta função o programa procura pelo indice indicado pelo usuario a tarefa que deseja ser excluida, e assim ela é apagada do programa por indice
void excluir(Tarefa *tarefa, int indice, int *n) {
    if (indice >= 0 && indice < *n) {
        for (int i = indice; i < *n - 1; i++) {
            tarefa[i] = tarefa[i + 1];
        }
        (*n)--;
        printf("Tarefa removida com sucesso!\n");
    } else {
        printf("Erro!\n");
    }
}