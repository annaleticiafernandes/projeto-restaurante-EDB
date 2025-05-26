#ifndef SALAO_H
#define SALAO_H

typedef struct prato {
    char nome[50];
} Prato;

typedef struct pratoNode {
    Prato dadosPrato;
    struct pratoNode *prox;
} PratoNode;

typedef struct pedido {
    int numMesa;
    int idPedido;
    PratoNode *listaPratos;
    struct pedido *prox;
} Pedido;

// Funções já existentes
void adicionarPedido(Pedido **cabeca, int numMesa, int idPedido, char pratos[][50], int qtdPratos);
void listarPedidosPendentes(Pedido *cabeca);

// Funções auxiliares para o main.c
Pedido* copiarPedido(Pedido *pedidoOriginal);
void imprimirPedido(Pedido *pedido);
void liberarPedido(Pedido *pedido);

#endif
