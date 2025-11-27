/*
 * SISTEMA DE INVENTÁRIO - BATTLE ROYALE
 * Desafio: Gerenciamento de itens de loot inicial
 *
 * Este programa simula uma mochila de inventário onde o jogador
 * pode cadastrar, remover, listar e buscar itens coletados.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição de constantes
#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

/*
 * STRUCT ITEM
 * Representa um item no inventário do jogador
 * - nome: identificação do item (ex: "AK-47", "Kit Médico")
 * - tipo: categoria do item (ex: "arma", "munição", "cura")
 * - quantidade: número de unidades do item
 */
typedef struct
{
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Variáveis globais
Item inventario[MAX_ITENS]; // Vetor que armazena os itens
int totalItens = 0;         // Contador de itens cadastrados

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
 * FUNÇÃO: inserirItem
 * Cadastra um novo item no inventário
 * Verifica se há espaço disponível antes de inserir
 */
void inserirItem()
{
    // Verifica se o inventário está cheio
    if (totalItens >= MAX_ITENS)
    {
        printf("\n[!] Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n=== CADASTRAR NOVO ITEM ===\n");

    // Lê o nome do item
    printf("Nome do item: ");
    scanf("%s", inventario[totalItens].nome);
    limparBuffer();

    // Lê o tipo do item
    printf("Tipo (arma/munição/cura/ferramenta): ");
    scanf("%s", inventario[totalItens].tipo);
    limparBuffer();

    // Lê a quantidade
    printf("Quantidade: ");
    scanf("%d", &inventario[totalItens].quantidade);
    limparBuffer();

    totalItens++;
    printf("\n[✓] Item '%s' adicionado com sucesso!\n", inventario[totalItens - 1].nome);
}

/*
 * FUNÇÃO: removerItem
 * Remove um item do inventário baseado no nome
 * Usa busca sequencial para localizar o item
 */
void removerItem()
{
    if (totalItens == 0)
    {
        printf("\n[!] Inventário vazio! Não há itens para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== REMOVER ITEM ===\n");
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeBusca);
    limparBuffer();

    // Busca sequencial pelo item
    int encontrado = -1;
    for (int i = 0; i < totalItens; i++)
    {
        if (strcmp(inventario[i].nome, nomeBusca) == 0)
        {
            encontrado = i;
            break;
        }
    }

    // Se encontrou, remove o item
    if (encontrado != -1)
    {
        // Desloca todos os itens posteriores uma posição para trás
        for (int i = encontrado; i < totalItens - 1; i++)
        {
            inventario[i] = inventario[i + 1];
        }
        totalItens--;
        printf("\n[✓] Item '%s' removido com sucesso!\n", nomeBusca);
    }
    else
    {
        printf("\n[!] Item '%s' não encontrado no inventário.\n", nomeBusca);
    }
}

/*
 * FUNÇÃO: listarItens
 * Exibe todos os itens cadastrados no inventário
 * Mostra nome, tipo e quantidade de cada item
 */
void listarItens()
{
    printf("\n╔═══════════════════════════════════════════════════════════╗\n");
    printf("║              INVENTÁRIO DE LOOT - MOCHILA                 ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");

    if (totalItens == 0)
    {
        printf("\n[!] Inventário vazio! Colete itens no mapa.\n");
        return;
    }

    printf("\nCapacidade: [%d/%d] itens\n", totalItens, MAX_ITENS);
    printf("\n%-20s %-15s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("─────────────────────────────────────────────────────────\n");

    // Percorre e exibe todos os itens
    for (int i = 0; i < totalItens; i++)
    {
        printf("%-20s %-15s %-10d\n",
               inventario[i].nome,
               inventario[i].tipo,
               inventario[i].quantidade);
    }
    printf("\n");
}

/*
 * FUNÇÃO: buscarItem
 * Implementa busca sequencial por nome de item
 * Exibe os dados completos se o item for encontrado
 */
void buscarItem()
{
    if (totalItens == 0)
    {
        printf("\n[!] Inventário vazio! Não há itens para buscar.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== BUSCAR ITEM ===\n");
    printf("Digite o nome do item: ");
    scanf("%s", nomeBusca);
    limparBuffer();

    // Busca sequencial
    int encontrado = -1;
    for (int i = 0; i < totalItens; i++)
    {
        if (strcmp(inventario[i].nome, nomeBusca) == 0)
        {
            encontrado = i;
            break;
        }
    }

    // Exibe resultado da busca
    if (encontrado != -1)
    {
        printf("\n[✓] Item encontrado!\n");
        printf("─────────────────────────────────\n");
        printf("Nome:       %s\n", inventario[encontrado].nome);
        printf("Tipo:       %s\n", inventario[encontrado].tipo);
        printf("Quantidade: %d\n", inventario[encontrado].quantidade);
        printf("Posição:    [%d]\n", encontrado + 1);
    }
    else
    {
        printf("\n[!] Item '%s' não encontrado no inventário.\n", nomeBusca);
    }
}

/*
 * FUNÇÃO: exibirMenu
 * Mostra as opções disponíveis para o jogador
 */
void exibirMenu()
{
    printf("\n╔═══════════════════════════════════════════════════════════╗\n");
    printf("║          SISTEMA DE INVENTÁRIO - BATTLE ROYALE            ║\n");
    printf("╠═══════════════════════════════════════════════════════════╣\n");
    printf("║  [1] Cadastrar item (coletar loot)                        ║\n");
    printf("║  [2] Remover item (descartar)                             ║\n");
    printf("║  [3] Listar todos os itens                                ║\n");
    printf("║  [4] Buscar item específico                               ║\n");
    printf("║  [0] Sair do jogo                                         ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("\nEscolha uma opção: ");
}

/*
 * FUNÇÃO PRINCIPAL
 * Controla o fluxo do programa com menu interativo
 */
int main()
{
    int opcao;

    printf("\n Bem-vindo ao Sistema de Inventário Battle Royale!\n");
    printf("Gerencie seu loot e sobreviva!\n");

    // Loop principal do programa
    do
    {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        // Executa a ação escolhida pelo jogador
        switch (opcao)
        {
        case 1:
            inserirItem();
            listarItens(); // Mostra inventário atualizado
            break;
        case 2:
            removerItem();
            listarItens(); // Mostra inventário atualizado
            break;
        case 3:
            listarItens();
            break;
        case 4:
            buscarItem();
            break;
        case 0:
            printf("\n Encerrando o jogo... Boa sorte na battle royale!\n");
            break;
        default:
            printf("\n[!] Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}