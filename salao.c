#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salao.h"
#include "cardapio.h"


void adicionarPedido(Pedido **cabeca, int numMesa, int idPedido, char prato[][50], int qntdPratos){
    Pedido *novoPedido = malloc(sizeof(Pedido)); // Aloca um nó do pedido
    
    if(novoPedido == NULL){ 
        printf("Erro ao alocar memória para o pedido!\n");
        return;
    }
    
    // inicializa os dados do novo pedido
    novoPedido->numMesa = numMesa;
    novoPedido->idPedido = idPedido;
    novoPedido->listaPratos = NULL; 
    novoPedido->prox = NULL;

    // Adiciona os pratos à lista de pratos do pedido
    for(int i=0; i < qntdPratos; i++){
        PratoNode *novoPrato = malloc(sizeof(PratoNode));

        if(novoPrato == NULL){
            printf("Erro ao alocar memória para o prato!\n");
            continue;
        }

        strcpy(novoPrato->dadosPrato.nome, prato[i]);
        novoPrato->prox = novoPedido->listaPratos; // adiciona o novo prato no início da lista de PRATOS de um único pedido
        novoPedido->listaPratos = novoPrato; // atualiza o ponteiro da lista de pratos do pedido
    }

    if(*cabeca == NULL){ 
        *cabeca = novoPedido; 
        printf("Pedido adicionado com sucesso!\n");
        return;
    }
    
    Pedido *atual = *cabeca;

    while(atual->prox != NULL){
        atual = atual->prox; // atualiza o ponteiro para o próximo pedido
    }

    atual->prox = novoPedido;
    printf("Pedido adicionado com sucesso!\n");
}

void removerPrato(Pedido **cabeca, int idPedido, const char *nomePrato){
    if(*cabeca == NULL){
        printf("Nenhum pedido encontrado.\n");
        return;
    }

    // Percorre a lista de pedidos para encontrar o pedido com o idPedido especificado
    Pedido *pedidoAtual = *cabeca;
    while(pedidoAtual != NULL && pedidoAtual->idPedido != idPedido){
        pedidoAtual = pedidoAtual->prox; // avança para o próximo pedido    
    }

    if(pedidoAtual == NULL){
        printf("Pedido com ID %d não encontrado.\n", idPedido);
        return;
    }

    // PedidoAtual aponta para o pedido correto
    // Removemos o prato da lista de pratos dentro deste pedido
    
    if(pedidoAtual->listaPratos == NULL){
        printf("Nenhum prato encontrado no pedido %d.\n", idPedido);
        return;
    }

    // Percorre a lista de pratos para encontrar o prato com o nome especificado
    PratoNode *pratoAnterior = NULL;
    PratoNode *pratoAtual = pedidoAtual->listaPratos;

    while(pratoAtual != NULL && strcmp(pratoAtual->dadosPrato.nome, nomePrato) != 0){
        pratoAnterior = pratoAtual; // atualiza o ponteiro do prato anterior
        pratoAtual = pratoAtual->prox; // avança para o próximo prato
    }

    if(pratoAtual == NULL){
        printf("Prato %s não encontrado no pedido %d.\n", nomePrato, idPedido);
        return;
    }

    // Remove o nó do prato encontrado da lista interna do pedido
    if(pratoAnterior == NULL){
        pedidoAtual->listaPratos = pratoAtual->prox; 
    } else {
        pratoAnterior->prox = pratoAtual->prox;
    }

    free(pratoAtual);
    printf("Prato %s removido do pedido %d com sucesso!\n", nomePrato, idPedido);

    // Se a lista de pratos do pedido estiver vazia após a remoção, remove-se o pedido da lista de pedidos
    if(pedidoAtual->listaPratos == NULL){
        if(*cabeca == pedidoAtual){
            *cabeca = pedidoAtual->prox; 
        } else {
            Pedido *pedidoAnterior = *cabeca;
            while(pedidoAnterior->prox != pedidoAtual){
                pedidoAnterior = pedidoAnterior->prox; 
            }
            pedidoAnterior->prox = pedidoAtual->prox; 
        }
        free(pedidoAtual);
        printf("Pedido %d removido com sucesso!\n", idPedido);
    }
} 

void listarPedidosPendentes(Pedido *cabeca){
    if(cabeca == NULL){ 
        printf("Nenhum pedido pendente.\n");
        return;
    }

    Pedido *atual = cabeca; 

    while(atual != NULL){ 
        printf("Mesa: %d, ID do Pedido: %d\n", atual->numMesa, atual->idPedido);
        printf("Pratos:\n");
    
        PratoNode *pratoAtual = atual->listaPratos;
        if(pratoAtual == NULL){ 
            printf("Nenhum prato neste pedido.\n");
        } else {
            while(pratoAtual != NULL){ // percorre a lista de pratos
                printf("- %s\n", pratoAtual->dadosPrato.nome); // exibe o nome do prato
                pratoAtual = pratoAtual->prox; // avança para o próximo prato
            }
        }
        
        printf("\n");
        atual = atual->prox; // avança para o próximo pedido
    }
}


