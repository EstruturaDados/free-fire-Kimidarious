/*
 * SISTEMA DE MONTAGEM DA TORRE DE FUGA - NIVEL MESTRE
 * Desafio Final: Organização estratégica de componentes
 * 
 * Este programa implementa um sistema avançado de priorização e ordenação
 * de componentes necessários para construir a torre de resgate.
 * 
 * O jogador pode escolher diferentes algoritmos de ordenação e avaliar
 * seu desempenho através de contadores de comparações e tempo de execução.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição de constantes
#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

/*
 * STRUCT COMPONENTE
 * Representa um componente necessário para a montagem da torre
 * - nome: identificação do componente
 * - tipo: categoria (controle, suporte, propulsão, etc)
 * - prioridade: nível de importância (1 a 10)
 */
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade;
} Componente;

// Variáveis globais
Componente componentes[MAX_COMPONENTES];
int totalComponentes = 0;
long long comparacoes = 0;

/*
 * ============================================================
 *                  FUNÇÕES AUXILIARES
 * ============================================================
 */

/*
 * FUNÇÃO: limparBuffer
 * Remove caracteres residuais do buffer de entrada
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * FUNÇÃO: removerNovaLinha
 * Remove o caractere de nova linha de strings lidas com fgets
 */
void removerNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

/*
 * FUNÇÃO: mostrarComponentes
 * Exibe todos os componentes formatados em tabela
 */
void mostrarComponentes(Componente comp[], int total) {
    printf("\n========================================================================\n");
    printf("                    COMPONENTES DA TORRE DE FUGA\n");
    printf("========================================================================\n");
    
    if (total == 0) {
        printf("\n[!] Nenhum componente cadastrado ainda.\n");
        return;
    }
    
    printf("\nTotal de componentes: %d/%d\n\n", total, MAX_COMPONENTES);
    printf("%-4s %-28s %-18s %-10s\n", "ID", "NOME", "TIPO", "PRIORIDADE");
    printf("------------------------------------------------------------------------\n");
    
    for (int i = 0; i < total; i++) {
        printf("%-4d %-28s %-18s %-10d\n", 
               i + 1, 
               comp[i].nome, 
               comp[i].tipo, 
               comp[i].prioridade);
    }
    printf("\n");
}

/*
 * ============================================================
 *              FUNÇÕES DE CADASTRO E ENTRADA
 * ============================================================
 */

/*
 * FUNÇÃO: cadastrarComponente
 * Adiciona um novo componente ao sistema
 * Valida a entrada de dados e garante consistência
 */
void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\n[!] Limite maximo de componentes atingido!\n");
        return;
    }
    
    printf("\n=== CADASTRAR NOVO COMPONENTE ===\n");
    
    // Leitura do nome com fgets para segurança
    printf("Nome do componente: ");
    fgets(componentes[totalComponentes].nome, TAM_NOME, stdin);
    removerNovaLinha(componentes[totalComponentes].nome);
    
    // Leitura do tipo
    printf("Tipo (controle/suporte/propulsao/energia): ");
    fgets(componentes[totalComponentes].tipo, TAM_TIPO, stdin);
    removerNovaLinha(componentes[totalComponentes].tipo);
    
    // Leitura da prioridade com validação
    do {
        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[totalComponentes].prioridade);
        limparBuffer();
        
        if (componentes[totalComponentes].prioridade < 1 || 
            componentes[totalComponentes].prioridade > 10) {
            printf("[!] Prioridade deve estar entre 1 e 10!\n");
        }
    } while (componentes[totalComponentes].prioridade < 1 || 
             componentes[totalComponentes].prioridade > 10);
    
    totalComponentes++;
    printf("\n[OK] Componente cadastrado com sucesso!\n");
}

/*
 * FUNÇÃO: cadastrarLote
 * Permite cadastrar múltiplos componentes de uma vez
 */
void cadastrarLote() {
    int quantidade;
    
    printf("\n=== CADASTRO EM LOTE ===\n");
    printf("Quantos componentes deseja cadastrar? ");
    scanf("%d", &quantidade);
    limparBuffer();
    
    if (quantidade < 1) {
        printf("[!] Quantidade invalida!\n");
        return;
    }
    
    if (totalComponentes + quantidade > MAX_COMPONENTES) {
        printf("[!] Isso excederia o limite! Espaco disponivel: %d\n", 
               MAX_COMPONENTES - totalComponentes);
        return;
    }
    
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Componente %d/%d ---\n", i + 1, quantidade);
        cadastrarComponente();
    }
}

/*
 * ============================================================
 *           ALGORITMOS DE ORDENAÇÃO
 * ============================================================
 */

/*
 * FUNÇÃO: bubbleSortNome
 * Ordena os componentes por nome usando Bubble Sort
 * Complexidade: O(n²) no pior caso
 * 
 * Características:
 * - Simples de implementar
 * - Ineficiente para grandes conjuntos
 * - Realiza muitas trocas
 */
void bubbleSortNome(Componente comp[], int total) {
    comparacoes = 0;
    
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            comparacoes++;
            if (strcmp(comp[j].nome, comp[j + 1].nome) > 0) {
                // Troca os componentes
                Componente temp = comp[j];
                comp[j] = comp[j + 1];
                comp[j + 1] = temp;
            }
        }
    }
}

/*
 * FUNÇÃO: insertionSortTipo
 * Ordena os componentes por tipo usando Insertion Sort
 * Complexidade: O(n²) no pior caso, O(n) no melhor caso
 * 
 * Características:
 * - Eficiente para conjuntos pequenos
 * - Adaptável (rápido se já estiver parcialmente ordenado)
 * - Estável (mantém ordem relativa de elementos iguais)
 */
void insertionSortTipo(Componente comp[], int total) {
    comparacoes = 0;
    
    for (int i = 1; i < total; i++) {
        Componente chave = comp[i];
        int j = i - 1;
        
        // Move elementos maiores que a chave uma posição à frente
        while (j >= 0) {
            comparacoes++;
            if (strcmp(comp[j].tipo, chave.tipo) > 0) {
                comp[j + 1] = comp[j];
                j--;
            } else {
                break;
            }
        }
        comp[j + 1] = chave;
    }
}

/*
 * FUNÇÃO: selectionSortPrioridade
 * Ordena os componentes por prioridade usando Selection Sort
 * Complexidade: O(n²) sempre
 * 
 * Características:
 * - Número fixo de comparações
 * - Minimiza o número de trocas
 * - Não é adaptável
 */
void selectionSortPrioridade(Componente comp[], int total) {
    comparacoes = 0;
    
    for (int i = 0; i < total - 1; i++) {
        int indiceMaior = i;
        
        // Procura o elemento de maior prioridade
        for (int j = i + 1; j < total; j++) {
            comparacoes++;
            if (comp[j].prioridade > comp[indiceMaior].prioridade) {
                indiceMaior = j;
            }
        }
        
        // Troca se necessário
        if (indiceMaior != i) {
            Componente temp = comp[i];
            comp[i] = comp[indiceMaior];
            comp[indiceMaior] = temp;
        }
    }
}

/*
 * ============================================================
 *                  FUNÇÕES DE BUSCA
 * ============================================================
 */

/*
 * FUNÇÃO: buscaBinariaPorNome
 * Realiza busca binária no array ordenado por nome
 * Complexidade: O(log n)
 * 
 * Pré-requisito: O array DEVE estar ordenado por nome
 * Retorna: índice do componente ou -1 se não encontrado
 */
int buscaBinariaPorNome(Componente comp[], int total, char nomeBusca[]) {
    int esquerda = 0;
    int direita = total - 1;
    comparacoes = 0;
    
    while (esquerda <= direita) {
        comparacoes++;
        int meio = esquerda + (direita - esquerda) / 2;
        int resultado = strcmp(comp[meio].nome, nomeBusca);
        
        if (resultado == 0) {
            return meio;
        } else if (resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    return -1;
}

/*
 * ============================================================
 *              FUNÇÕES DE MEDIÇÃO E ANÁLISE
 * ============================================================
 */

/*
 * FUNÇÃO: executarOrdenacaoComMedicao
 * Executa um algoritmo de ordenação e mede seu desempenho
 * Exibe estatísticas completas sobre a execução
 */
void executarOrdenacaoComMedicao(void (*algoritmo)(Componente[], int), 
                                  const char* nomeAlgoritmo) {
    if (totalComponentes == 0) {
        printf("\n[!] Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n=== EXECUTANDO: %s ===\n", nomeAlgoritmo);
    printf("Preparando ordenacao...\n");
    
    // Mede o tempo de execução
    clock_t inicio = clock();
    algoritmo(componentes, totalComponentes);
    clock_t fim = clock();
    
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000;
    
    // Exibe estatísticas
    printf("\n--- ESTATISTICAS DE DESEMPENHO ---\n");
    printf("Algoritmo:           %s\n", nomeAlgoritmo);
    printf("Componentes:         %d\n", totalComponentes);
    printf("Comparacoes:         %lld\n", comparacoes);
    printf("Tempo de execucao:   %.2f microsegundos\n", tempoGasto);
    
    // Exibe os componentes ordenados
    mostrarComponentes(componentes, totalComponentes);
    
    printf("[OK] Ordenacao concluida com sucesso!\n");
}

/*
 * FUNÇÃO: buscarComponenteChave
 * Busca o componente-chave necessário para ativar a torre
 * Utiliza busca binária para eficiência máxima
 */
void buscarComponenteChave() {
    if (totalComponentes == 0) {
        printf("\n[!] Nenhum componente cadastrado!\n");
        return;
    }
    
    char nomeBusca[TAM_NOME];
    
    printf("\n=== BUSCAR COMPONENTE-CHAVE ===\n");
    printf("ATENCAO: A lista deve estar ordenada por NOME!\n");
    printf("Digite o nome do componente-chave: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    removerNovaLinha(nomeBusca);
    
    printf("\nIniciando busca binaria...\n");
    
    clock_t inicio = clock();
    int indice = buscaBinariaPorNome(componentes, totalComponentes, nomeBusca);
    clock_t fim = clock();
    
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000;
    
    if (indice != -1) {
        printf("\n========================================\n");
        printf("    COMPONENTE-CHAVE ENCONTRADO!\n");
        printf("========================================\n");
        printf("Nome:       %s\n", componentes[indice].nome);
        printf("Tipo:       %s\n", componentes[indice].tipo);
        printf("Prioridade: %d\n", componentes[indice].prioridade);
        printf("Posicao:    [%d]\n", indice + 1);
        printf("\n[OK] Torre de fuga pode ser ativada!\n");
    } else {
        printf("\n[!] COMPONENTE NAO ENCONTRADO!\n");
        printf("A torre nao pode ser ativada sem este componente.\n");
    }
    
    printf("\n--- ESTATISTICAS DA BUSCA BINARIA ---\n");
    printf("Comparacoes realizadas: %lld\n", comparacoes);
    printf("Tempo de execucao:      %.2f microsegundos\n", tempoGasto);
}

/*
 * FUNÇÃO: compararAlgoritmos
 * Executa uma análise comparativa de todos os algoritmos
 * Útil para decisões estratégicas baseadas em dados
 */
void compararAlgoritmos() {
    if (totalComponentes == 0) {
        printf("\n[!] Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n========================================================================\n");
    printf("                  ANALISE COMPARATIVA DE ALGORITMOS\n");
    printf("========================================================================\n");
    
    // Cria cópias do array para cada teste
    Componente copia1[MAX_COMPONENTES];
    Componente copia2[MAX_COMPONENTES];
    Componente copia3[MAX_COMPONENTES];
    
    for (int i = 0; i < totalComponentes; i++) {
        copia1[i] = componentes[i];
        copia2[i] = componentes[i];
        copia3[i] = componentes[i];
    }
    
    // Teste 1: Bubble Sort
    clock_t inicio = clock();
    bubbleSortNome(copia1, totalComponentes);
    clock_t fim = clock();
    double tempoBubble = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000;
    long long compBubble = comparacoes;
    
    // Teste 2: Insertion Sort
    inicio = clock();
    insertionSortTipo(copia2, totalComponentes);
    fim = clock();
    double tempoInsertion = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000;
    long long compInsertion = comparacoes;
    
    // Teste 3: Selection Sort
    inicio = clock();
    selectionSortPrioridade(copia3, totalComponentes);
    fim = clock();
    double tempoSelection = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000000;
    long long compSelection = comparacoes;
    
    // Exibe resultados comparativos
    printf("\nNumero de componentes: %d\n\n", totalComponentes);
    printf("%-20s %-15s %-20s\n", "ALGORITMO", "COMPARACOES", "TEMPO (us)");
    printf("------------------------------------------------------------------------\n");
    printf("%-20s %-15lld %-20.2f\n", "Bubble Sort", compBubble, tempoBubble);
    printf("%-20s %-15lld %-20.2f\n", "Insertion Sort", compInsertion, tempoInsertion);
    printf("%-20s %-15lld %-20.2f\n", "Selection Sort", compSelection, tempoSelection);
    
    printf("\n--- ANALISE ---\n");
    printf("Mais rapido:        ");
    if (tempoBubble <= tempoInsertion && tempoBubble <= tempoSelection)
        printf("Bubble Sort\n");
    else if (tempoInsertion <= tempoSelection)
        printf("Insertion Sort\n");
    else
        printf("Selection Sort\n");
    
    printf("Menos comparacoes:  ");
    if (compBubble <= compInsertion && compBubble <= compSelection)
        printf("Bubble Sort\n");
    else if (compInsertion <= compSelection)
        printf("Insertion Sort\n");
    else
        printf("Selection Sort\n");
}

/*
 * ============================================================
 *              FUNÇÕES DE VALIDAÇÃO E MONTAGEM
 * ============================================================
 */

/*
 * FUNÇÃO: verificarComponentesEssenciais
 * Verifica se todos os tipos essenciais de componentes estão presentes
 */
void verificarComponentesEssenciais() {
    if (totalComponentes == 0) {
        printf("\n[!] Nenhum componente cadastrado!\n");
        return;
    }
    
    int temControle = 0, temSuporte = 0, temPropulsao = 0, temEnergia = 0;
    
    for (int i = 0; i < totalComponentes; i++) {
        if (strstr(componentes[i].tipo, "controle")) temControle = 1;
        if (strstr(componentes[i].tipo, "suporte")) temSuporte = 1;
        if (strstr(componentes[i].tipo, "propulsao")) temPropulsao = 1;
        if (strstr(componentes[i].tipo, "energia")) temEnergia = 1;
    }
    
    printf("\n=== VERIFICACAO DE COMPONENTES ESSENCIAIS ===\n");
    printf("Controle:   %s\n", temControle ? "[OK]" : "[FALTANDO]");
    printf("Suporte:    %s\n", temSuporte ? "[OK]" : "[FALTANDO]");
    printf("Propulsao:  %s\n", temPropulsao ? "[OK]" : "[FALTANDO]");
    printf("Energia:    %s\n", temEnergia ? "[OK]" : "[FALTANDO]");
    
    if (temControle && temSuporte && temPropulsao && temEnergia) {
        printf("\n[OK] Todos os componentes essenciais estao presentes!\n");
        printf("A torre pode ser montada.\n");
    } else {
        printf("\n[!] ATENCAO: Componentes essenciais faltando!\n");
        printf("A montagem da torre esta incompleta.\n");
    }
}

/*
 * FUNÇÃO: simularMontagem
 * Simula a montagem da torre seguindo a ordem de prioridade
 */
void simularMontagem() {
    if (totalComponentes == 0) {
        printf("\n[!] Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n========================================================================\n");
    printf("                   SIMULACAO DE MONTAGEM DA TORRE\n");
    printf("========================================================================\n");
    
    // Ordena por prioridade
    printf("\nOrdenando componentes por prioridade...\n");
    selectionSortPrioridade(componentes, totalComponentes);
    
    printf("\n--- SEQUENCIA DE MONTAGEM ---\n");
    printf("Os componentes devem ser instalados na seguinte ordem:\n\n");
    
    for (int i = 0; i < totalComponentes; i++) {
        printf("Passo %d: [Prioridade %d] %s (%s)\n", 
               i + 1, 
               componentes[i].prioridade,
               componentes[i].nome,
               componentes[i].tipo);
    }
    
    printf("\n[OK] Sequencia de montagem estabelecida!\n");
}

/*
 * ============================================================
 *                    MENUS E INTERFACE
 * ============================================================
 */

/*
 * FUNÇÃO: menuOrdenacao
 * Submenu para escolha do algoritmo de ordenação
 */
void menuOrdenacao() {
    int opcao;
    
    do {
        printf("\n========================================\n");
        printf("       MENU DE ORDENACAO\n");
        printf("========================================\n");
        printf("[1] Bubble Sort (ordenar por NOME)\n");
        printf("[2] Insertion Sort (ordenar por TIPO)\n");
        printf("[3] Selection Sort (ordenar por PRIORIDADE)\n");
        printf("[4] Comparar todos os algoritmos\n");
        printf("[0] Voltar\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                executarOrdenacaoComMedicao(bubbleSortNome, "Bubble Sort por Nome");
                break;
            case 2:
                executarOrdenacaoComMedicao(insertionSortTipo, "Insertion Sort por Tipo");
                break;
            case 3:
                executarOrdenacaoComMedicao(selectionSortPrioridade, "Selection Sort por Prioridade");
                break;
            case 4:
                compararAlgoritmos();
                break;
            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;
            default:
                printf("\n[!] Opcao invalida!\n");
        }
    } while(opcao != 0);
}

/*
 * FUNÇÃO: menuPrincipal
 * Menu principal do sistema
 */
void menuPrincipal() {
    int opcao;
    
    do {
        printf("\n========================================================================\n");
        printf("           SISTEMA DE MONTAGEM DA TORRE DE FUGA - NIVEL MESTRE\n");
        printf("========================================================================\n");
        printf("[1]  Cadastrar componente\n");
        printf("[2]  Cadastrar lote de componentes\n");
        printf("[3]  Listar componentes\n");
        printf("[4]  Ordenar componentes\n");
        printf("[5]  Buscar componente-chave (busca binaria)\n");
        printf("[6]  Verificar componentes essenciais\n");
        printf("[7]  Simular montagem da torre\n");
        printf("[0]  Sair e abandonar missao\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                cadastrarLote();
                break;
            case 3:
                mostrarComponentes(componentes, totalComponentes);
                break;
            case 4:
                menuOrdenacao();
                break;
            case 5:
                buscarComponenteChave();
                break;
            case 6:
                verificarComponentesEssenciais();
                break;
            case 7:
                simularMontagem();
                break;
            case 0:
                printf("\n========================================\n");
                printf("  Missao encerrada.\n");
                printf("  Boa sorte na proxima partida!\n");
                printf("========================================\n");
                break;
            default:
                printf("\n[!] Opcao invalida!\n");
        }
    } while(opcao != 0);
}

/*
 * ============================================================
 *                   FUNÇÃO PRINCIPAL
 * ============================================================
 */

int main() {
    printf("\n========================================================================\n");
    printf("                         BATTLE ROYALE - NIVEL MESTRE\n");
    printf("                      MISSAO: MONTAGEM DA TORRE DE FUGA\n");
    printf("========================================================================\n");
    printf("\nA zona de perigo esta se fechando!\n");
    printf("Organize os componentes estrategicamente para construir a torre\n");
    printf("de resgate e escapar da ilha antes que seja tarde demais.\n");
    
    menuPrincipal();
    
    return 0;
}