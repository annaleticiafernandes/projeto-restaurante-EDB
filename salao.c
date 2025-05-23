#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salao.h"
#include "cardapio.h"


void adicionarPedido(Pedido **cabeca, int numMesa, int idPedido, char prato[][50], int qntdPratos){
    Pedido *novoPedido = malloc(sizeof(Pedido)); // aloca um novo nó do tipo Pedido
    
    if(novoPedido == NULL){ // verifica se memoria foi alocada corretamente
        printf("Erro ao alocar memória para o pedido!\n");
        return;
    }
    
    // inicializa os dados do novo pedido
    novoPedido->numMesa = numMesa;
    novoPedido->idPedido = idPedido;
    novoPedido->listaPratos = NULL; // inicializa a lista de pratos como vazia
    novoPedido->prox = NULL; // inicializa o próximo pedido como NULL, pois ainda não está ligado a nada

    // Adiciona os pratos à lista de pratos do pedido
    for(int i=0; i < qntdPratos; i++){
        PratoNode *novoPrato = malloc(sizeof(PratoNode));

        if(novoPrato == NULL){
            printf("Erro ao alocar memória para o prato!\n");
            continue;
        }

        strcpy(novoPrato->dadosPrato.nome, prato[i]); // copia o nome do prato
        novoPrato->prox = novoPedido->listaPratos; // adiciona o novo prato no início da lista de PRATOS de um único pedido
        novoPedido->listaPratos = novoPrato; // atualiza o ponteiro da lista de pratos do pedido
    }

    if(*cabeca == NULL){ // caso a lista de pedidos esteja vazia
        *cabeca = novoPedido; // o novo pedido se torna o primeiro da lista
        printf("Pedido adicionado com sucesso!\n");
        return;
    }
    
    Pedido *atual = *cabeca;

    while(atual->prox != NULL){ // percorre a lista de pedidos até o final
        atual = atual->prox; // atualiza o ponteiro para o próximo pedido
    }

    atual->prox = novoPedido; // adiciona o novo pedido no final da lista
    printf("Pedido adicionado com sucesso!\n");
}

void removerPrato(Pedido **cabeca, int idPedido, const char *nomePrato){
    // Verifica se a lista de pedidos está vazia
    if(*cabeca == NULL){
        printf("Nenhum pedido encontrado.\n");
        return;
    }

    // Percorre a lista de pedidos para encontrar o pedido com o idPedido especificado
    Pedido *pedidoAtual = *cabeca;
    while(pedidoAtual != NULL && pedidoAtual->idPedido != idPedido){
        pedidoAtual = pedidoAtual->prox; // avança para o próximo pedido    
    }

    // Se o pedido não foi encontrado, exibe uma mensagem e retorna
    if(pedidoAtual == NULL){
        printf("Pedido com ID %d não encontrado.\n", idPedido);
        return;
    }

    // PedidoAtual aponta para o pedido correto
    // Removemos o prato da lista de pratos dentro deste pedido
    
    //verifica se a lista de pratos dentro do pedido está vazia
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

    // Se o prato não foi encontrado, exibe uma mensagem e retorna
    if(pratoAtual == NULL){
        printf("Prato %s não encontrado no pedido %d.\n", nomePrato, idPedido);
        return;
    }

    // Remove o nó do prato encontrado da lista interna do pedido
    if(pratoAnterior == NULL){ // o prato a ser removido é o primeiro da lista
        pedidoAtual->listaPratos = pratoAtual->prox; // atualiza o ponteiro da lista de pratos
    } else {
        pratoAnterior->prox = pratoAtual->prox; // o prato a ser removido não é o primeiro, ou seja, está no meio ou no final da lista
    }

    // Libera a memória do nó do prato removido
    free(pratoAtual);
    printf("Prato %s removido do pedido %d com sucesso!\n", nomePrato, idPedido);


    // EXTRA!!!
    // Se a lista de pratos do pedido estiver vazia após a remoção, podemos remover o pedido também
    if(pedidoAtual->listaPratos == NULL){
        // Se o pedido for o primeiro da lista de pedidos
        if(*cabeca == pedidoAtual){
            *cabeca = pedidoAtual->prox; // atualiza o ponteiro da lista de pedidos
        } else {
            Pedido *pedidoAnterior = *cabeca;
            while(pedidoAnterior->prox != pedidoAtual){
                pedidoAnterior = pedidoAnterior->prox; // avança para o próximo pedido
            }
            pedidoAnterior->prox = pedidoAtual->prox; // remove o pedido da lista de pedidos
        }
        free(pedidoAtual); // libera a memória do pedido removido
        printf("Pedido %d removido com sucesso!\n", idPedido);
    }
}

void listarPedidosPendentes(Pedido *cabeca){
    if(cabeca == NULL){ // verifica se a lista de pedidos está vazia
        printf("Nenhum pedido pendente.\n");
        return;
    }

    Pedido *atual = cabeca; // inicializa o ponteiro atual para percorrer a lista de pedidos

    while(atual != NULL){ // percorre a lista de pedidos
        printf("Mesa: %d, ID do Pedido: %d\n", atual->numMesa, atual->idPedido);
        printf("Pratos:\n");
    
        PratoNode *pratoAtual = atual->listaPratos; // inicializa o ponteiro para percorrer a lista de pratos do pedido
        if(pratoAtual == NULL){ // verifica se a lista de pratos está vazia
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


