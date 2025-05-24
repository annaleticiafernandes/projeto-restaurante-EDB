#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cozinha.h"

// Ponteiros globais para a fila da cozinha
static Pedido *frente = NULL;
static Pedido *tras = NULL;

void enfileirarPedido(Pedido *pedidoOriginal) {
    if (pedidoOriginal == NULL) {
        printf("Pedido inválido para enfileirar.\n");
        return;
    }

    // Cria uma cópia do pedido original (para manter independência entre as listas)
    Pedido *novoPedido = malloc(sizeof(Pedido));
    if (novoPedido == NULL) {
        printf("Erro ao alocar memória para o pedido na cozinha!\n");
        return;
    }

    novoPedido->numMesa = pedidoOriginal->numMesa;
    novoPedido->idPedido = pedidoOriginal->idPedido;
    novoPedido->listaPratos = NULL;
    novoPedido->prox = NULL;

    // Copia os pratos do pedido original
    PratoNode *pratoAtual = pedidoOriginal->listaPratos;
    PratoNode *ultimoPrato = NULL;

    while (pratoAtual != NULL) {
        PratoNode *novoPrato = malloc(sizeof(PratoNode));
        if (novoPrato == NULL) {
            printf("Erro ao alocar memória para um prato na cozinha!\n");
            pratoAtual = pratoAtual->prox;
            continue;
        }

        strcpy(novoPrato->dadosPrato.nome, pratoAtual->dadosPrato.nome);
        novoPrato->prox = NULL;

        if (novoPedido->listaPratos == NULL) {
            novoPedido->listaPratos = novoPrato;
        } else {
            ultimoPrato->prox = novoPrato;
        }

        ultimoPrato = novoPrato;
        pratoAtual = pratoAtual->prox;
    }

    // Adiciona o pedido na fila da cozinha
    if (frente == NULL) {
        frente = novoPedido;
        tras = novoPedido;
    } else {
        tras->prox = novoPedido;
        tras = novoPedido;
    }

    printf("Pedido %d da mesa %d enviado para a cozinha!\n", novoPedido->idPedido, novoPedido->numMesa);
}

void processarProximoPedido() {
    if (frente == NULL) {
        printf("Nenhum pedido na cozinha para processar.\n");
        return;
    }

    Pedido *pedidoProcessado = frente;
    printf("Processando pedido %d da mesa %d...\n", pedidoProcessado->idPedido, pedidoProcessado->numMesa);

    // Libera a lista de pratos
    PratoNode *prato = pedidoProcessado->listaPratos;
    while (prato != NULL) {
        PratoNode *temp = prato;
        prato = prato->prox;
        free(temp);
    }

    // Remove da fila
    frente = frente->prox;
    if (frente == NULL) {
        tras = NULL;
    }

    free(pedidoProcessado);
    printf("Pedido processado com sucesso!\n");
}

void listarPedidosCozinha() {
    if (frente == NULL) {
        printf("Nenhum pedido na cozinha.\n");
        return;
    }

    printf("---- FILA DE PEDIDOS NA COZINHA ----\n");
    Pedido *atual = frente;

    while (atual != NULL) {
        printf("Mesa: %d, ID do Pedido: %d\n", atual->numMesa, atual->idPedido);
        printf("Pratos:\n");

        PratoNode *pratoAtual = atual->listaPratos;
        while (pratoAtual != NULL) {
            printf("- %s\n", pratoAtual->dadosPrato.nome);
            pratoAtual = pratoAtual->prox;
        }

        printf("\n");
        atual = atual->prox;
    }
}
