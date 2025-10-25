#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
#define MAX_ITENS 10 // CAPACIDADE MÁXIMA DA MOCHILA
#define TAM_NOME 30  // TAMANHO MÁXIMO DO CAMPO NOME
#define TAM_TIPO 20  // TAMANHO MÁXIMO DO TIPO

typedef struct // definição da struct item
{
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} item;

// variável global
item mochila[MAX_ITENS]; // vetor que armazena os itens
int total = 0;           // número atual de itens na mochila

void limparBuffer(void) // Limpar o buffer stdin
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// inserir itens
void inserirItem(void)
{
    if (total >= MAX_ITENS)
    {
        printf("\n>>> A mochila já está cheia (máx. %d itens).\n", MAX_ITENS);
        return;
    }

    printf("\n=== Cadastro de novo item ===\n");

    printf("Nome do item (até %d caracteres): ", TAM_NOME - 1);
    fgets(mochila[total].nome, TAM_NOME, stdin);
    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0'; // remove o '\n'

    printf("Tipo (arma, munição, cura, ferramenta...): ");
    fgets(mochila[total].tipo, TAM_TIPO, stdin);
    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[total].quantidade);
    limparBuffer();

    total++;
    printf("\n>>> Item cadastrado com sucesso!\n");
}

// remover item()
void removerItem(void)
{
    if (total == 0)
    {
        printf("\n>>> Não há itens para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== Remover Item ===\n");
    printf("Informe o nome do item a ser removido: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < total; i++)
    {
        if (strcmp(mochila[i].nome, nomeBusca) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("\n>>> Item %s não encontrado.\n", nomeBusca);
        return;
    }

    // desloca item posterior para posição anterior
    for (int i = pos; i < total - 1; i++)
    {
        mochila[i] = mochila[i + 1];
    }
    total--;
    printf("\n>>> Item %s removido com sucesso.\n", nomeBusca);
}

// listar itens()
void listaItens(void)
{
    printf("\n=== Itens na mochila (%d/%d) ===\n", total, MAX_ITENS);
    if (total == 0)
    {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        printf("[%d] Nome: %-30s Tipo %-20s Quantidade: %d\n",
        i + 1,
        mochila[i].nome,
        mochila[i].tipo,
        mochila[i].quantidade);
    }
}

// buscar item()
void buscarItem(void)
{
    if (total == 0)
    {
        printf("\n>>> Não há itens para buscar.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== Busca de item ===\n");
    printf("Informe o nome do item a ser localizado: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++)
    {
        if (strcmp(mochila[i].nome, nomeBusca) == 0)
        {
            printf("\n>>> Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                mochila[i].nome,
                mochila[i].tipo,
                mochila[i].quantidade);
            return;
        }
    }
    printf("\n>>> Item %s não encontrado.\n", nomeBusca);
}

int main(void)
{
    int opcao;

    while (1)
    {
        printf("\n==== MENU INVENTÁRIO ====\n");
        printf("1 - Cadastrar Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens\n");
        printf("4 - Buscar Item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer(); // limpa o '\n'

        switch (opcao)
        {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listaItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("\nEncerrando... Boa Sorte!\n"); return 0;
            default: printf("\nOpção inválida! Tente novamente.\n");
        }
    }
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
