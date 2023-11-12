#include "biblioteca.h"
#include <stdio.h>
#include <string.h>

// essa função apenas imprime as opçoes disponiveis do programa
void menu() {
    printf("Selecione uma opcao: \n");
    printf("1- Adicionar tarefa \n");
    printf("2- Listar todas as tarefas\n");
    printf("3- Excluir tarefa\n");
    printf("4- Alterar alguma informacao da tarefa\n");
    printf("5- Filtrar tarefas por prioridade \n");
    printf("6- Filtrar tarefas pelo estado \n");
    printf("7- Filtrar tarefas pela categoria ordenando pela prioridade \n");
    printf("8- Filtrar tarefas por prioridade e categoria \n");
    printf("9- Exportar por prioridade \n");
    printf("10- Exportar por categoria \n");
    printf("11- Exportar por prioridade e categoria \n");
    printf("0- Sair\n");
}

// essa função pega os dados que o  usuario escreveu e armazena em uma estrutura
void escreverTarefa(Tarefa *tarefa, int numTarefa) {
    tarefa->numTarefa = numTarefa;
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

    printf("Digite o estado da tarefa (1- Completo, 2- Em andamento, 3- Nao iniciado):\n");
    int opcaoEstado;
    scanf("%d", &opcaoEstado); //vai pegar o numero relacionado ao estado e guardar na variavel relacionada ao estados das tarefas
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
            printf("Esta opcao é invalida para estado, sendo assim sera marcada como Nao iniciado.\n");
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
    //vai abrir o arquivo, colocar as informacoes dentro dele e fechar
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
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("Numero da tarefa: %d\n", i + 1); 
        //ele pega todaa as informacoes guardadas nas variaveis e printa em uma ordem para criar o numero de cada tarefa
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
                printf("Estado: Nao iniciado\n");
                break;
            default:
                printf("Estado: Desconhecido\n");
        }
        printf("\n");
    }
}

//nesta função o programa procura pelo numero indicado pelo usuario a tarefa que deseja ser excluida, e assim ela é apagada do programa 
void excluir(Tarefa *tarefa, int numTarefa, int *n) {
    if (numTarefa >= 1 && numTarefa <= *n) {
        int indice = numTarefa - 1;
        for (int i = indice; i < *n - 1; i++) { //exclui a tarefa pelo seu numero 
            tarefa[i] = tarefa[i + 1];
        }
        (*n)--;
        printf("Tarefa removida com sucesso!\n");
    } else {
        printf("Erro\n");
    }
}

//nesta função conseguimos alterar campos de uma tarefa ja adcionada
void alterar(Tarefa *tarefa, int n) {
    printf("Digite o numero da tarefa que deseja modificar:\n");
    int numTarefa;
    scanf("%d", &numTarefa);
    //vai pegar o numero atraves do scanf e salvvar em uma variavel 
    int indice = -1;
    for (int i = 0; i < n; i++) {
        if (tarefa[i].numTarefa == numTarefa) {
            indice = i;
            break;
        } // verifica se o numero da tarefa realmente existe
    }

    if (indice != -1) { //assim que ele confirma que a tarefa realmente existe (diferente de indice-1) mostra as opcoes no qual o usuario pode alterar
        printf("Escolha o que deseja alterar:\n");
        printf("1- Prioridade\n");
        printf("2- Descricao\n");
        printf("3- Categoria\n");
        printf("4- Estado\n");
        //vai pegar a opção escolhida pelo usuario (pelo scanf) e seguir de acordo com os cases
        int opcao;
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a nova prioridade:\n");
                scanf("%d", &tarefa[indice].prioridade); //aqui ele adciona a nova prioridade na variavel
                printf("Prioridade da tarefa %d alterada.\n", numTarefa);
                break;
            case 2:
                printf("Digite a nova descricao:\n");
                getchar();
                fgets(tarefa[indice].descricao, sizeof(tarefa[indice].descricao), stdin);
                tarefa[indice].descricao[strcspn(tarefa[indice].descricao, "\n")] = '\0';
                printf("Descricao da tarefa %d alterada.\n", numTarefa);
                break;
            case 3:
                printf("Digite a nova categoria:\n");
                getchar(); //usado pra evitar erros quando tem essa questao de adcionar coisas novas
                fgets(tarefa[indice].categoria, sizeof(tarefa[indice].categoria), stdin); //le a nova categoria (fgets) escrita pelo usuario e altera ela 
                tarefa[indice].categoria[strcspn(tarefa[indice].categoria, "\n")] = '\0';
                printf("Categoria da tarefa %d alterada.\n", numTarefa);
                break;
            case 4:
                printf("Escolha o novo estado para a tarefa %d:\n", numTarefa);
                printf("1- Completo\n");
                printf("2- Em andamento\n");
                printf("3- Nao iniciado\n");
                int estado;
                scanf("%d", &estado);

                switch (estado) {
                    case 1:
                        tarefa[indice].estado = COMPLETO;
                        printf("Estado da tarefa %d alterado para Completo.\n", numTarefa);
                        break;
                    case 2:
                        tarefa[indice].estado = EM_ANDAMENTO;
                        printf("Estado da tarefa %d alterado para Em andamento.\n", numTarefa);
                        break;
                    case 3:
                        tarefa[indice].estado = NAO_INICIADO;
                        printf("Estado da tarefa %d alterado para Nao iniciado.\n", numTarefa);
                        break;
                    default:
                        printf("Opcao invalida\n");
                }
                break;
            default:
                printf("Opcao invalida\n");
        }
    } else {
        printf("Numero da tarefa escolhida nao foi encontrado\n");
    }
}

//nesta função o usuario consegue filtratar todas as tarefas descritas naquela prioridade
void filtrarP(const Tarefa *tarefa, int n, int prioridade) {
    printf("Listando tarefas com prioridade %d:\n", prioridade);
    int encontrou = 0;
    //vai encontrar a prioridade escolhida pelo usuario e sera printado
    for (int i = 0; i < n; i++) {
        if (tarefa[i].prioridade == prioridade) { //aqui ele confirma todas as tarefas que tem a prioridade == a escolhida pelo usuario
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
                    printf("Estado: Nao iniciado\n");
                    break;
                default:
                    printf("Estado: Desconhecido\n");
            }
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com a prioridade %d.\n", prioridade);
    }
}


//nesta função o usuario consegue filtrar todas as tarefas descritas com o estado desejado especifico
void filtrarE(const Tarefa *tarefa, int n, EstadoTarefa estado) {
    printf("Listando tarefas com o estado escolhido:\n");
    int encontrou = 0;

    for (int i = 0; i < n; i++) { //vai fazer a confirmacao primeiro
        if (tarefa[i].estado == estado) { //vai procurar todas as tarefas com o estado == ao que o susuario escolheu 
            printf("Prioridade: %d\n", tarefa[i].prioridade);
            printf("Descricao: %s\n", tarefa[i].descricao);
            printf("Categoria: %s\n", tarefa[i].categoria);
            printf("Estado: %s\n", (tarefa[i].estado == COMPLETO) ? "Completo" :
                                   (tarefa[i].estado == EM_ANDAMENTO) ? "Em andamento" : "Nao iniciado");
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com o estado escolhido.\n");
    }
}

//nesta função o usuario consegue filtrar todas as tarefas na ordem de categoria em que elas estão
void filtrarC(const Tarefa *tarefa, int n, const char *categoria) {
    printf("Listando tarefas na categoria '%s' ordenadas por prioridade:\n", categoria);
    int encontrou = 0;

    //cria um vetor temporário para armazenar as tarefas com a categoria especificada
    Tarefa tarefasFiltradas[100]; // o número máximo de tarefas é 100
    int contador = 0;

    //vai filtrar as tarefas por categoria
    for (int i = 0; i < n; i++) {
        if (strcmp(tarefa[i].categoria, categoria) == 0) {
            tarefasFiltradas[contador] = tarefa[i];
            contador++;
            encontrou = 1;
        }
    }

    //aqui  vai ordena as tarefas filtradas por prioridade (do maior para o menor)
    for (int i = 0; i < contador - 1; i++) {
        for (int j = i + 1; j < contador; j++) {
            if (tarefasFiltradas[i].prioridade < tarefasFiltradas[j].prioridade) {
                // troca as tarefas de posição (se a prioridade for maior assim criando a ordem)
                Tarefa temp = tarefasFiltradas[i];
                tarefasFiltradas[i] = tarefasFiltradas[j];
                tarefasFiltradas[j] = temp;
            }
        }
    }

    // imprime as tarefas filtradas e ordenadas
    for (int i = 0; i < contador; i++) {
        printf("Prioridade: %d\n", tarefasFiltradas[i].prioridade);
        printf("Descricao: %s\n", tarefasFiltradas[i].descricao);
        printf("Categoria: %s\n", tarefasFiltradas[i].categoria);
        encontrou = 1;
    }

    //se ele não encontrar nada isso sera impresso
    if (!encontrou) {
        printf("Nenhuma tarefa encontrada na categoria '%s'.\n", categoria);
    }
}

//nesta função o usuario consegue filtrar todas as tarefas na ordem de categoria em que elas estão juntamente a prioridade em que elas se encontram de acordo com a categoria
void filtrarPC(const Tarefa *tarefa, int n, int prioridade, const char *categoria) {
    printf("Listando tarefas com prioridade %d na categoria '%s':\n", prioridade, categoria);
    int encontrou = 0;

    for (int i = 0; i < n; i++) { //itera sobre as tarefas e ai entra o if caso ele encontre o que esta sendo pedido ou nao 
        if (tarefa[i].prioridade == prioridade && strcmp(tarefa[i].categoria, categoria) == 0) { //vai confirmar se as informacoes que o usuario quer tem em alguma tarefa, nesse caso a categoria e a priroridade
            printf("Prioridade: %d\n", tarefa[i].prioridade);
            printf("Descricao: %s\n", tarefa[i].descricao);
            printf("Categoria: %s\n", tarefa[i].categoria);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com a prioridade %d na categoria '%s'.\n", prioridade, categoria);
    }//se ele nao encontrar sera printado isso 
}

//nesta função o usuario consegue exportar para um novo arquivo todas as tarefas que estão na prioridade especifica escolhida pelo usuario
void exportarP(const Tarefa *tarefa, int n, int prioridade, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w"); //cria um arquivo para escrita ("w")
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de exportacao.\n");
        return;
    }

    for (int i = 0; i < n; i++) { //aqui ele esta iterando sobre as tarefas (procurando) pra ve se ele acha algo igual ao que o usuario esta pedindo
        if (tarefa[i].prioridade == prioridade) { //se ele achar comeca a exportacao
            fprintf(arquivo, "Prioridade: %d\n", tarefa[i].prioridade);
            fprintf(arquivo, "Categoria: %s\n", tarefa[i].categoria);
            fprintf(arquivo, "Estado: %s\n", (tarefa[i].estado == COMPLETO) ? "Completo" :
                                             (tarefa[i].estado == EM_ANDAMENTO) ? "Em andamento" : "Nao iniciado");
            fprintf(arquivo, "Descricao: %s\n", tarefa[i].descricao);
            fprintf(arquivo, "\n");
            //essa parte dentro do if indica todas as informacooes necessarias sendo adcionadas no arquivo novo
        }
    }

    fclose(arquivo); //fecha o arquivo novo 
    printf("Tarefas da prioridade %d exportadas para o arquivo: %s\n", prioridade, nomeArquivo);
}

//nesta função o usuario consegue exportar para um novo arquivo todas as tarefas que estão na categoria especifica escolhida pelo usuario
void exportarC(const Tarefa *tarefa, int n, const char *categoria, const char *nomeArquivo) {
    //filtra as tarefas com a categoria fornecida
    Tarefa tarefasFiltradas[100];
    int contadorFiltradas = 0;
    for (int i = 0; i < n; i++) { //itera sobre ate achar e entra a parte do if se ele acha ou não
        if (strcmp(tarefa[i].categoria, categoria) == 0) {
            tarefasFiltradas[contadorFiltradas] = tarefa[i];
            contadorFiltradas++;
        }
    }
    //aqui esta ordenando as tarefas filtradas por prioridade
    for (int i = 0; i < contadorFiltradas - 1; i++) {
        for (int j = 0; j < contadorFiltradas - i - 1; j++) {
            if (tarefasFiltradas[j].prioridade < tarefasFiltradas[j + 1].prioridade) {
                // troca as tarefas se a prioridade for menor
                Tarefa temp = tarefasFiltradas[j];
                tarefasFiltradas[j] = tarefasFiltradas[j + 1];
                tarefasFiltradas[j + 1] = temp;
            }
        }
    }

    //exporta as tarefas filtradas e ordenadas por prioridade para o novo arquivo
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de exportacao.\n");
        return;
    }

    for (int i = 0; i < contadorFiltradas; i++) {
        fprintf(arquivo, "Prioridade: %d\n", tarefasFiltradas[i].prioridade);
        fprintf(arquivo, "Categoria: %s\n", tarefasFiltradas[i].categoria);
        fprintf(arquivo, "Estado: %s\n", (tarefasFiltradas[i].estado == COMPLETO) ? "Completo" :
                                         (tarefasFiltradas[i].estado == EM_ANDAMENTO) ? "Em andamento" : "Nao iniciado");
        fprintf(arquivo, "Descricao: %s\n", tarefasFiltradas[i].descricao);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo); //fecha o arquivo novo
    printf("Tarefas da categoria \"%s\" exportadas para o arquivo: %s\n", categoria, nomeArquivo);
}

//nesta função o usuario consegue exportar para um novo arquivo todas as tarefas que estão na prioridade e categoria especificas escolhidas pelo usuario
void exportarPC(const Tarefa *tarefa, int n, int prioridade, const char *categoria, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w"); //abre um arquivo novo na funcao de escrever "w"
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de exportacao.\n");
        return;
    }

    for (int i = 0; i < n; i++) { //itera sobre ate achar o que esta sendo requisitado 
        if (tarefa[i].prioridade == prioridade && strcmp(tarefa[i].categoria, categoria) == 0) { //se achar ele pega as informacoes encontradas e adciona no novo aquivo
            fprintf(arquivo, "Prioridade: %d\n", tarefa[i].prioridade);
            fprintf(arquivo, "Categoria: %s\n", tarefa[i].categoria);
            fprintf(arquivo, "Estado: %s\n", (tarefa[i].estado == COMPLETO) ? "Completo" :
                                             (tarefa[i].estado == EM_ANDAMENTO) ? "Em andamento" : "Nao iniciado");
            fprintf(arquivo, "Descricao: %s\n", tarefa[i].descricao);
            fprintf(arquivo, "\n");
        }
    }

    fclose(arquivo); //fecha esse novo arquivo
    printf("Tarefas da prioridade %d na categoria '%s' exportadas para o arquivo: %s\n", prioridade, categoria, nomeArquivo);
}
