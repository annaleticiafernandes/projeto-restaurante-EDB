#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salao.h"

// Adiciona um novo pedido à lista
void adicionarPedido(Pedido **cabeca, int numMesa, int idPedido, char prato[][50], int qntdPratos) {
    Pedido *novo = (Pedido *)malloc(sizeof(Pedido));
    novo->numMesa = numMesa;
    novo->idPedido = idPedido;
    novo->listaPratos = NULL;
    novo->prox = NULL;

    // Adiciona os pratos à lista de pratos do pedido
    PratoNode *ultimoPrato = NULL;

    for (int i = 0; i < qntdPratos; i++) {
        PratoNode *novoPrato = (PratoNode *)malloc(sizeof(PratoNode));
        strcpy(novoPrato->dadosPrato.nome, prato[i]);
        novoPrato->prox = NULL;

        if (novo->listaPratos == NULL) {
            novo->listaPratos = novoPrato;
        } else {
            ultimoPrato->prox = novoPrato;
        }
        ultimoPrato = novoPrato;
    }

    // Adiciona o pedido ao final da lista
    if (*cabeca == NULL) {
        *cabeca = novo;
    } else {
        Pedido *atual = *cabeca;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    printf("\033[32mPedido adicionado com sucesso!\033[0m\n");
}

// Remove um prato de um pedido; remove o pedido se não restarem pratos
void removerPrato(Pedido **cabeca, int idPedido, const char *nomePrato) {
    Pedido *atual = *cabeca;
    Pedido *anterior = NULL;

    while (atual != NULL && atual->idPedido != idPedido) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("\033[31mPedido com ID %d nao encontrado.\033[0m\n", idPedido);
        return;
    }

    PratoNode *pratoAtual = atual->listaPratos;
    PratoNode *pratoAnterior = NULL;
    int encontrado = 0;

    while (pratoAtual != NULL) {
        if (strcmp(pratoAtual->dadosPrato.nome, nomePrato) == 0) {
            encontrado = 1;
            if (pratoAnterior == NULL) {
                atual->listaPratos = pratoAtual->prox;
            } else {
                pratoAnterior->prox = pratoAtual->prox;
            }
            free(pratoAtual);
            break;
        }
        pratoAnterior = pratoAtual;
        pratoAtual = pratoAtual->prox;
    }

    if (!encontrado) {
        printf("\033[31mPrato '%s' nao encontrado no pedido.\033[0m\n", nomePrato);
        return;
    }

    // Se não restarem pratos, remove o pedido inteiro
    if (atual->listaPratos == NULL) {
        if (anterior == NULL) {
            *cabeca = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
        printf("\033[31mPedido removido pois nao restaram pratos.\033[0m\n");
    } else {
        printf("\033[32mPrato removido do pedido com sucesso.\033[0m\n");
    }
}

// Lista todos os pedidos pendentes no salão
void listarPedidosPendentes(Pedido *cabeca) {
    if (cabeca == NULL) {
        printf("Nenhum pedido pendente.\n");
        return;
    }

    Pedido *atual = cabeca;
    while (atual != NULL) {
        printf("\nPedido ID: %d | Mesa: %d\n", atual->idPedido, atual->numMesa);
        printf("Pratos:\n");

        PratoNode *prato = atual->listaPratos;
        while (prato != NULL) {
            printf(" - %s\n", prato->dadosPrato.nome);
            prato = prato->prox;
        }

        atual = atual->prox;
    }
}

// Libera a memória de um pedido (incluindo lista de pratos)
void liberarPedido(Pedido *pedido) {
    if (pedido == NULL) return;

    PratoNode *atual = pedido->listaPratos;
    while (atual != NULL) {
        PratoNode *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    free(pedido);
}

// Copia um pedido inteiro, incluindo sua lista de pratos
Pedido* copiarPedido(Pedido *pedidoOriginal) {
    if (pedidoOriginal == NULL) return NULL;

    Pedido *novoPedido = (Pedido*)malloc(sizeof(Pedido));
    if (!novoPedido) {
        printf("\033[31mErro ao alocar memoria para copia do pedido.\033[0m\n");
        return NULL;
    }

    novoPedido->numMesa = pedidoOriginal->numMesa;
    novoPedido->idPedido = pedidoOriginal->idPedido;
    novoPedido->prox = NULL;

    // Copiar a lista de pratos
    PratoNode *atualOriginal = pedidoOriginal->listaPratos;
    PratoNode *ultimoNovo = NULL;
    novoPedido->listaPratos = NULL;

    while (atualOriginal != NULL) {
        PratoNode *novoPrato = (PratoNode*)malloc(sizeof(PratoNode));
        if (!novoPrato) {
            printf("\033[31mErro ao alocar memoria para prato na copia do pedido.\033[0m\n");
            liberarPedido(novoPedido);
            return NULL;
        }
        strcpy(novoPrato->dadosPrato.nome, atualOriginal->dadosPrato.nome);
        novoPrato->prox = NULL;

        if (novoPedido->listaPratos == NULL) {
            novoPedido->listaPratos = novoPrato;
        } else {
            ultimoNovo->prox = novoPrato;
        }
        ultimoNovo = novoPrato;
        atualOriginal = atualOriginal->prox;
    }

    return novoPedido;
}

// Imprime um pedido com seus pratos
void imprimirPedido(Pedido *pedido) {
    if (pedido == NULL) {
        printf("\033[31mPedido vazio.\033[0m\n");
        return;
    }

    printf("\033[32mPedido ID: %d\033[0m\n", pedido->idPedido);
    printf("\033[32mMesa: %d\033[0m\n", pedido->numMesa);
    printf("Pratos:\n");

    PratoNode *atual = pedido->listaPratos;
    int i = 1;
    while (atual != NULL) {
        printf("  %d. %s\n", i, atual->dadosPrato.nome);
        atual = atual->prox;
        i++;
    }
}
