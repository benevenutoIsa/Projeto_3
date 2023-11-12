#include <stdio.h>
#include "biblioteca.h"
#include <string.h>
// Isabella Carvalho Benevenuto Izaias RA: 22123007-1


int main() {
    
    //essa parte esta sendo declarada arrays, variaveis e strings que irao armazenar as informacoes dos usuarios
    Tarefa pessoaTarefa[100];
    int opcao;
    int n = 0;
    int prioridadeExportar; 
    char nomeArquivoExportar[101];
    char categoriaFiltrar[101];

    // leitura do arquivo
    lerStruct(pessoaTarefa, "arquivo.bin");

    //aqui se inicializa o programa printando o menu de opcoes que o usuario tem para escolher com um loop que se encerra ao clicar na opcao 0
    do {
        menu();
        scanf("%d", &opcao);
        //depois de printar menu, com o scanf ele pega a opção escolhida pelo ususario e printa de acordo com o numero escolhido nos cases abaixo

        switch (opcao) {
            case 1: //adcionar tarefas
                if (n < 100) {
                    escreverTarefa(&pessoaTarefa[n]);
                    n++;
                } else {
                    printf("cheio\n");
                }
                // salvar e ler  os dados da struct ante de encerrar 
                break;
            case 2: //listar todas as tarefas, nao precisa de nenhuma entrada 
                listarStruct(pessoaTarefa, n);
                break;
            case 3: //excluir tarefas existentes pelo seu numero 
                printf("Digite o numero da tarefa que deseja excluir: \n");
                int numTarefaExcluir;
                scanf("%d", &numTarefaExcluir);
                excluir(pessoaTarefa, numTarefaExcluir, &n);
                break;
            case 4: //altera algum dado relacionado a tarefa 
                alterarTarefas(pessoaTarefa, n);
                break;
            case 5: // filtra todas as atividades com o numero especifico de prioridade
                printf("Digite o numero da prioridade da tarefa para filtrar as tarefas:\n");
                int prioridade;
                scanf("%d", &prioridade);
                filtrarPrioridade(pessoaTarefa, n, prioridade);
                break;
            case 6: //filtra todas as atividades que tem o mesmo estado de tarefa 
                printf("Selecione o estado da tarefa para filtrar:\n");
                printf("1- Completo\n");
                printf("2- Em andamento\n");
                printf("3- Nao iniciado\n");
                int opcaoEstado;
                scanf("%d", &opcaoEstado);

                EstadoTarefa estadoFiltrar;
                switch (opcaoEstado) {
                    case 1:
                        estadoFiltrar = COMPLETO;
                        break;
                    case 2:
                        estadoFiltrar = EM_ANDAMENTO;
                        break;
                    case 3:
                        estadoFiltrar = NAO_INICIADO;
                        break;
                    default:
                        printf("Opcao invalida \n");
                        continue;  //volta ao menu
                }

                filtrarEstado(pessoaTarefa, n, estadoFiltrar);
                break;
            case 7: //filtra todas as tarefas que tem a mesma categoria 
                printf("Digite a categoria da tarefa para filtrar:\n");
                getchar();
                fgets(categoriaFiltrar, sizeof(categoriaFiltrar), stdin);
                categoriaFiltrar[strlen(categoriaFiltrar) - 1] = '\0';
                filtrarCategoria(pessoaTarefa, n, categoriaFiltrar);
                break;
            case 8:// nesse ele filtra as tarefas que tem a mesma prioridade e a mesma categoria 
                printf("Digite a prioridade da tarefa para filtrar:\n");
                int prioridadeFiltrar;
                scanf("%d", &prioridadeFiltrar);

                printf("Digite a categoria as tarefa para filtrar:\n");
                getchar();
                fgets(categoriaFiltrar, sizeof(categoriaFiltrar), stdin);
                categoriaFiltrar[strlen(categoriaFiltrar) - 1] = '\0';

                filtrarPrioridadeCategoria(pessoaTarefa, n, prioridadeFiltrar, categoriaFiltrar);
                break;
            case 9: //vai pegar as tarefas com o numero de prioridade escolhido e exportar para um arquivo novo com o nome que o usuario escolher
                printf("Digite a prioridade as tarefa para exportar:\n");
                scanf("%d", &prioridadeExportar);

                printf("Digite o nome do novo arquivo  para exportar as tarefas:\n");
                getchar();
                fgets(nomeArquivoExportar, sizeof(nomeArquivoExportar), stdin);
                nomeArquivoExportar[strlen(nomeArquivoExportar) - 1] = '\0';
                
                exportarPrioridade(pessoaTarefa, n, prioridadeExportar, nomeArquivoExportar);
                break;
            case 10: //vai pegar as tarefas com a categoria escolhida e exportar para um arquivo novo com o nome que o usuario escolher
                printf("Digite a categoria da tarefa para exportar:\n");
                char categoriaExportar[101];
                getchar();
                fgets(categoriaExportar, sizeof(categoriaExportar), stdin);
                categoriaExportar[strlen(categoriaExportar) - 1] = '\0';

                printf("Digite o nome do novo arquivo para exportar as tarefas:\n");
                char nomeArquivoExportar[101];
                getchar();
                fgets(nomeArquivoExportar, sizeof(nomeArquivoExportar), stdin);
                nomeArquivoExportar[strlen(nomeArquivoExportar) - 1] = '\0';
                
                exportarCategoria(pessoaTarefa, n, categoriaExportar, nomeArquivoExportar);
                break;
            case 11: //vai pegar as tarefas que tenham a categoria escolhida e a prioriade escolhida e exportar para um arquivo novo com o nome que o usuario escolher
                printf("Digite a prioridade para exportar as tarefas:\n");
                scanf("%d", &prioridadeExportar);

                printf("Digite a categoria para exportar as tarefas:\n");
                getchar(); 
                fgets(categoriaExportar, sizeof(categoriaExportar), stdin);
                categoriaExportar[strlen(categoriaExportar) - 1] = '\0'; 

                printf("Digite o nome do arquivo para exportar as tarefas:\n");
                getchar(); 
                fgets(nomeArquivoExportar, sizeof(nomeArquivoExportar), stdin);
                nomeArquivoExportar[strlen(nomeArquivoExportar) - 1] = '\0'; 

                exportarPrioridadeCategoria(pessoaTarefa, n, prioridadeExportar, categoriaExportar, nomeArquivoExportar);
                break;
            case 0: //salva as informacoes antes de fechar o programa 
                salvarStruct(pessoaTarefa, n, "arquivo.bin");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    //se a opção escolhida no menu for 0 encerra o programa

    return 0;
}
