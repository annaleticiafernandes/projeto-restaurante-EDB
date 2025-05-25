#ifndef SALAO_H
#define SALAO_H

typedef struct Prato {
    char nome[50];
} Prato;

// estrutura de um nó na lista de pratos DENTRO de um pedido
typedef struct PratoNode {
    Prato dadosPrato;
    struct PratoNode *prox;
} PratoNode;

// estrutura de nó na lista ligada de PEDIDO (salão)
typedef struct Pedido{
    int numMesa;
    int idPedido;
    PratoNode* listaPratos; // Ponteiro para a lista de PratoNode deste pedido
    struct Pedido *prox; // Ponteiro para o proximo pedido da lista salão 
} Pedido;

// OPERAÇÕES
void adicionarPedido(Pedido **cabeca, int numMesa, int idPedido, char prato[][50], int qntdPratos);
void removerPrato(Pedido **cabeca, int idPedido, const char *nomePrato);
void listarPedidosPendentes(Pedido *cabeca);

#endif