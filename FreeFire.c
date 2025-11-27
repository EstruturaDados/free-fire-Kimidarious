/*
 * SISTEMA DE INVENTÁRIO - COMPARAÇÃO DE ESTRUTURAS DE DADOS
 * Desafio: Análise de desempenho entre Vetor e Lista Encadeada
 *
 * Este programa implementa duas versões de um sistema de inventário:
 * - Versão 1: Usando vetor (lista sequencial)
 * - Versão 2: Usando lista encadeada (estrutura dinâmica)
 *
 * Objetivo: Comparar o desempenho das operações em ambas as estruturas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição de constantes
#define MAX_ITENS 100
#define TAM_NOME 30
#define TAM_TIPO 20

/*
 * STRUCT ITEM
 * Representa um item do inventário com suas propriedades
 */
typedef struct
{
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

/*
 * STRUCT NO
 * Representa um nó da lista encadeada
 * Contém os dados do item e ponteiro para o próximo nó
 */
typedef struct No
{
    Item dados;
    struct No *proximo;
} No;

// Variáveis globais para o VETOR
Item inventarioVetor[MAX_ITENS];
int totalItensVetor = 0;

// Variável global para a LISTA ENCADEADA
No *inicioLista = NULL;
int totalItensLista = 0;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

/*
 * ============================================================
 *                  FUNÇÕES AUXILIARES
 * ============================================================
 */

/*
 * FUNÇÃO: limparBuffer
 * Limpa o buffer de entrada para evitar problemas com scanf
 */
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/*
 * FUNÇÃO: exibirItem
 * Exibe os dados de um item formatado
 */
void exibirItem(Item item)
{
    printf("%-25s %-15s %-10d\n", item.nome, item.tipo, item.quantidade);
}

/*
 * ============================================================
 *              OPERAÇÕES COM VETOR (LISTA SEQUENCIAL)
 * ============================================================
 */

/*
 * FUNÇÃO: inserirItemVetor
 * Insere um novo item no vetor
 * Complexidade: O(1) - inserção no final do vetor
 */
void inserirItemVetor()
{
    if (totalItensVetor >= MAX_ITENS)
    {
        printf("\n[!] Mochila (vetor) cheia! Capacidade maxima atingida.\n");
        return;
    }

    printf("\n=== INSERIR ITEM NO VETOR ===\n");

    printf("Nome do item: ");
    scanf("%s", inventarioVetor[totalItensVetor].nome);
    limparBuffer();

    printf("Tipo: ");
    scanf("%s", inventarioVetor[totalItensVetor].tipo);
    limparBuffer();

    printf("Quantidade: ");
    scanf("%d", &inventarioVetor[totalItensVetor].quantidade);
    limparBuffer();

    totalItensVetor++;
    printf("\n[OK] Item adicionado ao vetor com sucesso!\n");
}

/*
 * FUNÇÃO: removerItemVetor
 * Remove um item do vetor baseado no nome
 * Complexidade: O(n) - busca + deslocamento dos elementos
 */
void removerItemVetor()
{
    if (totalItensVetor == 0)
    {
        printf("\n[!] Inventario vazio!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== REMOVER ITEM DO VETOR ===\n");
    printf("Nome do item a remover: ");
    scanf("%s", nomeBusca);
    limparBuffer();

    int encontrado = -1;
    for (int i = 0; i < totalItensVetor; i++)
    {
        if (strcmp(inventarioVetor[i].nome, nomeBusca) == 0)
        {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1)
    {
        // Desloca elementos para preencher o espaço
        for (int i = encontrado; i < totalItensVetor - 1; i++)
        {
            inventarioVetor[i] = inventarioVetor[i + 1];
        }
        totalItensVetor--;
        printf("\n[OK] Item removido do vetor!\n");
    }
    else
    {
        printf("\n[!] Item nao encontrado no vetor.\n");
    }
}

/*
 * FUNÇÃO: listarItensVetor
 * Lista todos os itens armazenados no vetor
 * Complexidade: O(n)
 */
void listarItensVetor()
{
    printf("\n========================================\n");
    printf("  INVENTARIO - VETOR (Lista Sequencial)\n");
    printf("========================================\n");

    if (totalItensVetor == 0)
    {
        printf("\n[!] Inventario vazio!\n");
        return;
    }

    printf("\nTotal de itens: %d/%d\n\n", totalItensVetor, MAX_ITENS);
    printf("%-25s %-15s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < totalItensVetor; i++)
    {
        exibirItem(inventarioVetor[i]);
    }
    printf("\n");
}

/*
 * FUNÇÃO: buscarSequencialVetor
 * Realiza busca sequencial no vetor
 * Complexidade: O(n) - percorre o vetor linearmente
 */
void buscarSequencialVetor()
{
    if (totalItensVetor == 0)
    {
        printf("\n[!] Inventario vazio!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== BUSCA SEQUENCIAL NO VETOR ===\n");
    printf("Nome do item: ");
    scanf("%s", nomeBusca);
    limparBuffer();

    comparacoesSequencial = 0;
    int encontrado = -1;

    clock_t inicio = clock();

    for (int i = 0; i < totalItensVetor; i++)
    {
        comparacoesSequencial++;
        if (strcmp(inventarioVetor[i].nome, nomeBusca) == 0)
        {
            encontrado = i;
            break;
        }
    }

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000;

    if (encontrado != -1)
    {
        printf("\n[OK] Item encontrado!\n");
        printf("--------------------------------\n");
        printf("Nome:       %s\n", inventarioVetor[encontrado].nome);
        printf("Tipo:       %s\n", inventarioVetor[encontrado].tipo);
        printf("Quantidade: %d\n", inventarioVetor[encontrado].quantidade);
        printf("Posicao:    [%d]\n", encontrado);
    }
    else
    {
        printf("\n[!] Item nao encontrado.\n");
    }

    printf("\n--- ESTATISTICAS DA BUSCA SEQUENCIAL ---\n");
    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
    printf("Tempo de execucao: %.2f microsegundos\n", tempoGasto);
}

/*
 * FUNÇÃO: ordenarVetor
 * Ordena os itens do vetor por nome usando Bubble Sort
 * Complexidade: O(n²)
 */
void ordenarVetor()
{
    if (totalItensVetor == 0)
    {
        printf("\n[!] Inventario vazio!\n");
        return;
    }

    printf("\n=== ORDENANDO VETOR (Bubble Sort) ===\n");

    clock_t inicio = clock();

    // Bubble Sort
    for (int i = 0; i < totalItensVetor - 1; i++)
    {
        for (int j = 0; j < totalItensVetor - i - 1; j++)
        {
            if (strcmp(inventarioVetor[j].nome, inventarioVetor[j + 1].nome) > 0)
            {
                // Troca os itens
                Item temp = inventarioVetor[j];
                inventarioVetor[j] = inventarioVetor[j + 1];
                inventarioVetor[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000;

    printf("[OK] Vetor ordenado com sucesso!\n");
    printf("Tempo de ordenacao: %.2f microsegundos\n", tempoGasto);
}

/*
 * FUNÇÃO: buscarBinariaVetor
 * Realiza busca binária no vetor (requer vetor ordenado)
 * Complexidade: O(log n) - divide o espaço de busca pela metade a cada iteração
 */
void buscarBinariaVetor()
{
    if (totalItensVetor == 0)
    {
        printf("\n[!] Inventario vazio!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== BUSCA BINARIA NO VETOR ===\n");
    printf("ATENCAO: O vetor deve estar ordenado!\n");
    printf("Nome do item: ");
    scanf("%s", nomeBusca);
    limparBuffer();

    comparacoesBinaria = 0;
    int esquerda = 0;
    int direita = totalItensVetor - 1;
    int encontrado = -1;

    clock_t inicio = clock();

    while (esquerda <= direita)
    {
        comparacoesBinaria++;
        int meio = esquerda + (direita - esquerda) / 2;
        int resultado = strcmp(inventarioVetor[meio].nome, nomeBusca);

        if (resultado == 0)
        {
            encontrado = meio;
            break;
        }
        else if (resultado < 0)
        {
            esquerda = meio + 1;
        }
        else
        {
            direita = meio - 1;
        }
    }

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000;

    if (encontrado != -1)
    {
        printf("\n[OK] Item encontrado!\n");
        printf("--------------------------------\n");
        printf("Nome:       %s\n", inventarioVetor[encontrado].nome);
        printf("Tipo:       %s\n", inventarioVetor[encontrado].tipo);
        printf("Quantidade: %d\n", inventarioVetor[encontrado].quantidade);
        printf("Posicao:    [%d]\n", encontrado);
    }
    else
    {
        printf("\n[!] Item nao encontrado.\n");
    }

    printf("\n--- ESTATISTICAS DA BUSCA BINARIA ---\n");
    printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
    printf("Tempo de execucao: %.2f microsegundos\n", tempoGasto);
}

/*
 * ============================================================
 *           OPERAÇÕES COM LISTA ENCADEADA
 * ============================================================
 */

/*
 * FUNÇÃO: criarNo
 * Cria um novo nó para a lista encadeada
 */
No *criarNo(Item dados)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("\n[ERRO] Falha na alocacao de memoria!\n");
        return NULL;
    }
    novoNo->dados = dados;
    novoNo->proximo = NULL;
    return novoNo;
}

/*
 * FUNÇÃO: inserirItemLista
 * Insere um novo item no final da lista encadeada
 * Complexidade: O(n) - precisa percorrer até o final
 */
void inserirItemLista()
{
    Item novoItem;

    printf("\n=== INSERIR ITEM NA LISTA ENCADEADA ===\n");

    printf("Nome do item: ");
    scanf("%s", novoItem.nome);
    limparBuffer();

    printf("Tipo: ");
    scanf("%s", novoItem.tipo);
    limparBuffer();

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();

    No *novoNo = criarNo(novoItem);
    if (novoNo == NULL)
        return;

    if (inicioLista == NULL)
    {
        // Lista vazia, novo nó é o primeiro
        inicioLista = novoNo;
    }
    else
    {
        // Percorre até o final da lista
        No *atual = inicioLista;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }

    totalItensLista++;
    printf("\n[OK] Item adicionado a lista encadeada com sucesso!\n");
}

/*
 * FUNÇÃO: removerItemLista
 * Remove um item da lista encadeada baseado no nome
 * Complexidade: O(n) - busca sequencial
 */
void removerItemLista()
{
    if (inicioLista == NULL)
    {
        printf("\n[!] Lista encadeada vazia!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== REMOVER ITEM DA LISTA ENCADEADA ===\n");
    printf("Nome do item a remover: ");
    scanf("%s", nomeBusca);
    limparBuffer();

    No *atual = inicioLista;
    No *anterior = NULL;

    // Busca o nó a ser removido
    while (atual != NULL && strcmp(atual->dados.nome, nomeBusca) != 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("\n[!] Item nao encontrado na lista.\n");
        return;
    }

    // Remove o nó
    if (anterior == NULL)
    {
        // Remove o primeiro nó
        inicioLista = atual->proximo;
    }
    else
    {
        // Remove nó do meio ou final
        anterior->proximo = atual->proximo;
    }

    free(atual);
    totalItensLista--;
    printf("\n[OK] Item removido da lista encadeada!\n");
}

/*
 * FUNÇÃO: listarItensLista
 * Lista todos os itens da lista encadeada
 * Complexidade: O(n)
 */
void listarItensLista()
{
    printf("\n========================================\n");
    printf("  INVENTARIO - LISTA ENCADEADA\n");
    printf("========================================\n");

    if (inicioLista == NULL)
    {
        printf("\n[!] Lista encadeada vazia!\n");
        return;
    }

    printf("\nTotal de itens: %d\n\n", totalItensLista);
    printf("%-25s %-15s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("----------------------------------------------------------\n");

    No *atual = inicioLista;
    while (atual != NULL)
    {
        exibirItem(atual->dados);
        atual = atual->proximo;
    }
    printf("\n");
}

/*
 * FUNÇÃO: buscarSequencialLista
 * Realiza busca sequencial na lista encadeada
 * Complexidade: O(n)
 */
void buscarSequencialLista()
{
    if (inicioLista == NULL)
    {
        printf("\n[!] Lista encadeada vazia!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== BUSCA SEQUENCIAL NA LISTA ENCADEADA ===\n");
    printf("Nome do item: ");
    scanf("%s", nomeBusca);
    limparBuffer();

    comparacoesSequencial = 0;
    No *atual = inicioLista;
    int posicao = 0;

    clock_t inicio = clock();

    while (atual != NULL)
    {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0)
        {
            clock_t fim = clock();
            double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000;

            printf("\n[OK] Item encontrado!\n");
            printf("--------------------------------\n");
            printf("Nome:       %s\n", atual->dados.nome);
            printf("Tipo:       %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("Posicao:    [%d]\n", posicao);

            printf("\n--- ESTATISTICAS DA BUSCA SEQUENCIAL ---\n");
            printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
            printf("Tempo de execucao: %.2f microsegundos\n", tempoGasto);
            return;
        }
        atual = atual->proximo;
        posicao++;
    }

    clock_t fim = clock();
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000;

    printf("\n[!] Item nao encontrado.\n");
    printf("\n--- ESTATISTICAS DA BUSCA SEQUENCIAL ---\n");
    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
    printf("Tempo de execucao: %.2f microsegundos\n", tempoGasto);
}

/*
 * FUNÇÃO: liberarLista
 * Libera toda a memória alocada para a lista encadeada
 */
void liberarLista()
{
    No *atual = inicioLista;
    while (atual != NULL)
    {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicioLista = NULL;
    totalItensLista = 0;
}

/*
 * ============================================================
 *                    MENUS E INTERFACE
 * ============================================================
 */

/*
 * FUNÇÃO: menuVetor
 * Menu de operações para o vetor
 */
void menuVetor()
{
    int opcao;

    do
    {
        printf("\n========================================\n");
        printf("     MENU - VETOR (Lista Sequencial)\n");
        printf("========================================\n");
        printf("[1] Inserir item\n");
        printf("[2] Remover item\n");
        printf("[3] Listar itens\n");
        printf("[4] Buscar item (sequencial)\n");
        printf("[5] Ordenar vetor\n");
        printf("[6] Buscar item (binaria - requer ordenacao)\n");
        printf("[0] Voltar ao menu principal\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            inserirItemVetor();
            break;
        case 2:
            removerItemVetor();
            break;
        case 3:
            listarItensVetor();
            break;
        case 4:
            buscarSequencialVetor();
            break;
        case 5:
            ordenarVetor();
            break;
        case 6:
            buscarBinariaVetor();
            break;
        case 0:
            printf("\nVoltando ao menu principal...\n");
            break;
        default:
            printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

/*
 * FUNÇÃO: menuLista
 * Menu de operações para a lista encadeada
 */
void menuLista()
{
    int opcao;

    do
    {
        printf("\n========================================\n");
        printf("        MENU - LISTA ENCADEADA\n");
        printf("========================================\n");
        printf("[1] Inserir item\n");
        printf("[2] Remover item\n");
        printf("[3] Listar itens\n");
        printf("[4] Buscar item (sequencial)\n");
        printf("[0] Voltar ao menu principal\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            inserirItemLista();
            break;
        case 2:
            removerItemLista();
            break;
        case 3:
            listarItensLista();
            break;
        case 4:
            buscarSequencialLista();
            break;
        case 0:
            printf("\nVoltando ao menu principal...\n");
            break;
        default:
            printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

/*
 * FUNÇÃO: exibirComparacao
 * Exibe uma comparação teórica entre as duas estruturas
 */
void exibirComparacao()
{
    printf("\n========================================\n");
    printf("  COMPARACAO: VETOR vs LISTA ENCADEADA\n");
    printf("========================================\n\n");

    printf("OPERACAO          | VETOR      | LISTA ENCADEADA\n");
    printf("------------------+------------+----------------\n");
    printf("Insercao (final)  | O(1)       | O(n)\n");
    printf("Remocao           | O(n)       | O(n)\n");
    printf("Busca Sequencial  | O(n)       | O(n)\n");
    printf("Busca Binaria     | O(log n)   | Nao aplicavel\n");
    printf("Acesso por indice | O(1)       | O(n)\n");
    printf("Uso de memoria    | Continuo   | Dinamico\n");
    printf("\n");

    printf("VANTAGENS DO VETOR:\n");
    printf("- Acesso direto por indice (O(1))\n");
    printf("- Permite busca binaria apos ordenacao\n");
    printf("- Memoria contigua (melhor cache)\n");
    printf("- Simples de implementar\n\n");

    printf("VANTAGENS DA LISTA ENCADEADA:\n");
    printf("- Tamanho dinamico (cresce conforme necessario)\n");
    printf("- Insercao/remocao no inicio e O(1)\n");
    printf("- Nao desperdicoa memoria pre-alocada\n");
    printf("- Flexivel para reorganizacao\n\n");
}

/*
 * ============================================================
 *                   FUNÇÃO PRINCIPAL
 * ============================================================
 */

int main()
{
    int opcao;

    printf("\n========================================\n");
    printf("  SISTEMA DE INVENTARIO - BATTLE ROYALE\n");
    printf("    Comparacao de Estruturas de Dados\n");
    printf("========================================\n");

    do
    {
        printf("\n========================================\n");
        printf("           MENU PRINCIPAL\n");
        printf("========================================\n");
        printf("[1] Gerenciar mochila com VETOR\n");
        printf("[2] Gerenciar mochila com LISTA ENCADEADA\n");
        printf("[3] Exibir comparacao teorica\n");
        printf("[0] Sair do programa\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            menuVetor();
            break;
        case 2:
            menuLista();
            break;
        case 3:
            exibirComparacao();
            break;
        case 0:
            printf("\nEncerrando o programa...\n");
            liberarLista();
            break;
        default:
            printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}