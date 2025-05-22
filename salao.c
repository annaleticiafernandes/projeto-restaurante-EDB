#include <stdio.h>
#include <stdlib.h>
#include "salao.h"


void adicionarPedido(Pedido **cabeca, int numMesa, int idPedido, char prato[][50], int qntdPratos){
    Pedido *novoPedido = malloc(sizeof(Pedido)); // aloca um novo nó do tipo Pedido
    // inicializa os dados do novo pedido
    novoPedido->numMesa = numMesa;
    novoPedido->idPedido = idPedido;
    novoPedido->listaPratos = NULL; // inicializa a lista de pratos como vazia
    novoPedido->prox = NULL; // inicializa o próximo pedido como NULL, pois ainda não está ligado a nada

    // Adiciona os pratos à lista de pratos do pedido
    for(int i=0; i < qntdPratos; i++){
        Pedido *novoPrato = malloc(sizeof(PratoNode));
        styrcpy(novoPrato->dadosPrato.nome, prato[i]); // copia o nome do prato
        novoPrato->prox = novoPedido->listaPratos; // adiciona o novo prato no início da lista de PRATOS de um único pedido
        novoPedido->listaPratos = novoPrato; // atualiza o ponteiro da lista de pratos do pedido
    }

    if(*cabeca == NULL){ // caso a lista de pedidos esteja vazia
        *cabeca = novoPedido; // o novo pedido se torna o primeiro da lista
        return;
    }
    
    Pedido *atual = *cabeca;

    while(atual->prox != NULL){ // percorre a lista de pedidos até o final
        atual = atual->prox; // atualiza o ponteiro para o próximo pedido
    }

    atual->prox = novoPedido; // adiciona o novo pedido no final da lista
    printf("Pedido adicionado com sucesso!\n");
}

oid removerPrato(Pedido **cabeca, int idPedido, const char *nomePrato){
    // Verifica se a lista de pedidos está vazia
    if(*cabeca_salao == NULL){
        printf("Nenhum pedido encontrado.\n");
        return;
    }

    // Percorre a lista de pedidos para encontrar o pedido com o idPedido especificado
    Pedido *pedidoAtual = *cabeca_salao;
    while(pedidoAtual != NULL && pedidoAtual->idPedido != idPedido){
        pedidoAtual = pedidoAtual->prox; // avança para o próximo pedido    
    }

    // Se o pedido não foi encontrado, exibe uma mensagem e retorna
    if(pedidoAtual == NULL){
        pruntf("Pedido com ID %d não encontrado.\n", idPedido);
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
        if(*cabeca_salao == pedidoAtual){
            *cabeca_salao = pedidoAtual->prox; // atualiza o ponteiro da lista de pedidos
        } else {
            Pedido *pedidoAnterior = *cabeca_salao;
            while(pedidoAnterior->prox != pedidoAtual){
                pedidoAnterior = pedidoAnterior->prox; // avança para o próximo pedido
            }
            pedidoAnterior->prox = pedidoAtual->prox; // remove o pedido da lista de pedidos
        }
        free(pedidoAtual); // libera a memória do pedido removido
        printf("Pedido %d removido com sucesso!\n", idPedido);
    }
}