#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cozinha.h"

// Ponteiros globais para a fila da cozinha
static Pedido *frente = NULL;
static Pedido *tras = NULL;

// Função para enfileirar um pedido na cozinha (copia o pedido)
void enfileirarPedido(Pedido *pedidoOriginal) {
    if (pedidoOriginal == NULL) {
        printf("\033[31mPedido invalido para enfileirar.\033[0m\n");
        return;
    }

    // Cria uma cópia do pedido original
    Pedido *novoPedido = (Pedido *)malloc(sizeof(Pedido));
    if (!novoPedido) {
        printf("\033[31mErro ao alocar memoria para o pedido na cozinha!\033[0m\n");
        return;
    }

    novoPedido->numMesa = pedidoOriginal->numMesa;
    novoPedido->idPedido = pedidoOriginal->idPedido;
    novoPedido->listaPratos = NULL;
    novoPedido->prox = NULL;

    // Copia a lista ligada de pratos
    PratoNode *pratoAtualOrig = pedidoOriginal->listaPratos;
    PratoNode *ultimoPrato = NULL;

    while (pratoAtualOrig != NULL) {
        PratoNode *novoPrato = (PratoNode *)malloc(sizeof(PratoNode));
        if (!novoPrato) {
            printf("\033[31mErro ao alocar memoria para prato na cozinha!\033[0m\n");
            // Se quiser, pode liberar toda a cópia feita até aqui para evitar leak
            // Mas para simplicidade, apenas pula este prato
            pratoAtualOrig = pratoAtualOrig->prox;
            continue;
        }

        strcpy(novoPrato->dadosPrato.nome, pratoAtualOrig->dadosPrato.nome);
        novoPrato->prox = NULL;

        if (novoPedido->listaPratos == NULL) {
            novoPedido->listaPratos = novoPrato;
        } else {
            ultimoPrato->prox = novoPrato;
        }

        ultimoPrato = novoPrato;
        pratoAtualOrig = pratoAtualOrig->prox;
    }

    // Enfileira na fila da cozinha (FIFO)
    if (frente == NULL) {
        frente = novoPedido;
        tras = novoPedido;
    } else {
        tras->prox = novoPedido;
        tras = novoPedido;
    }

    printf("\033[32mPedido %d da mesa %d enviado para a cozinha!\033[0m\n", novoPedido->idPedido, novoPedido->numMesa);
}

// Função que processa (desenfileira) o próximo pedido da cozinha
void processarProximoPedido() {
    if (frente == NULL) {
        printf("Nenhum pedido na cozinha para processar.\n");
        return;
    }

    Pedido *pedidoProcessado = frente;
    printf("Processando pedido %d da mesa %d...\n", pedidoProcessado->idPedido, pedidoProcessado->numMesa);

    // Libera lista de pratos
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
    printf("\033[32mPedido processado com sucesso!\033[0m\n");
}

// Lista todos os pedidos na fila da cozinha
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
