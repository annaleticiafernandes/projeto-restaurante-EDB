#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salao.h"
#include "cardapio.h"
#include "cozinha.h"

void limparBuffer(); 
void menuPrincipal();
void InterfaceAdicionarPedido(Pedido **cabeca);
void interfaceRemoverPrato(Pedido **cabeca);
void processarPedido(Pedido **cabeca);

int main() {
    Pedido *cabecaSalao = NULL;
    int opcao;
    
    printf("Bem-vindo ao Restaurante Algoritmo do Sabor!\n");
    
    do {
        menuPrincipal();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                InterfaceAdicionarPedido(&cabecaSalao);
                break;
                
            case 2:
                interfaceRemoverPrato(&cabecaSalao);
                break;
                
            case 3:
                printf("\n--- PEDIDOS PENDENTES NO SALAO ---\n");
                listarPedidosPendentes(cabecaSalao);
                break;
                
            case 4:
                exibirCardapio();
                break;
                
            case 5:
                processarPedido(&cabecaSalao);
                break;
                
            case 0:
                printf("Encerrando o sistema...\n");
                break;
                
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
        
    } while (opcao != 0);

    printf("Sistema encerrado com sucesso!\n");
    
    return 0;
}

void limparBuffer(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

void menuPrincipal(){
    printf("\n");
    printf("-------- MENU PRINCIPAL --------\n");
    printf("1. Adicionar Pedido\n");
    printf("2. Remover Prato de um Pedido\n");
    printf("3. Listar Pedidos Pendentes\n");
    printf("4. Exibir Cardapio\n");
    printf("5. Processar Pedido (Enviar para a Cozinha)\n");
    printf("0. Sair\n");
    printf("--------------------------------\n");
    printf("Escolha uma opcao: ");
}

// Função para adicionar um pedido com interface
void InterfaceAdicionarPedido(Pedido **cabeca){
    int numMesa, idPedido, qntdPratos, indicePrato;
    char prato[20][50];
    char nomePrato[50];

    printf("\n------- ADICIONAR PEDIDO -------\n");

    printf("Numero da Mesa: ");
    scanf("%d", &numMesa);

    printf("ID do Pedido: ");
    scanf("%d", &idPedido);

    printf("Quantidade de Pratos: ");
    scanf("%d", &qntdPratos);   

    if(qntdPratos <= 0 || qntdPratos > 20){
        printf("Quantidade invalida de pratos!\n");
        return;
    }

    exibirCardapio();

    for(int i=0; i<qntdPratos; i++){
        printf("Escolha o prato %d (1-15): ", i+1);
        scanf("%d", &indicePrato);

        if(indicePrato < 1 || indicePrato > 15){
            printf("Opçao invalida! Tente novamente.\n");
            i--; 
            continue;
        }

        obterNomePrato(indicePrato, nomePrato);
        strcpy(prato[i], nomePrato);
        printf("Prato adiconado: %s\n", nomePrato);
    }

    adicionarPedido(cabeca, numMesa, idPedido, prato, qntdPratos);
}

// Função para remover um prato de um pedido com interface
void interfaceRemoverPrato(Pedido **cabeca) {
    int idPedido, indiceSelecionado;
    
    printf("\n---- REMOVER PRATO DO PEDIDO ----\n");
    
    // Verifica se existem pedidos
    if (*cabeca == NULL) {
        printf("Nenhum pedido pendente encontrado.\n");
        return;
    }
    
    printf("Pedidos pendentes:\n");
    listarPedidosPendentes(*cabeca);
    
    printf("Digite o ID do pedido: ");
    scanf("%d", &idPedido);
    
    // Encontra o pedido específico
    Pedido *pedidoAtual = *cabeca;
    while(pedidoAtual != NULL && pedidoAtual->idPedido != idPedido) {
        pedidoAtual = pedidoAtual->prox;
    }
    
    // Verifica se o pedido foi encontrado
    if(pedidoAtual == NULL) {
        printf("Pedido com ID %d nao encontrado.\n", idPedido);
        return;
    }
    
    // Verifica se o pedido tem pratos
    if(pedidoAtual->listaPratos == NULL) {
        printf("Nenhum prato encontrado no pedido %d.\n", idPedido);
        return;
    }
    
    // Lista os pratos do pedido com índices
    printf("\nPratos no pedido %d:\n", idPedido);
    PratoNode *pratoAtual = pedidoAtual->listaPratos;
    int contador = 1;
    
    while(pratoAtual != NULL) {
        printf("%d. %s\n", contador, pratoAtual->dadosPrato.nome);
        pratoAtual = pratoAtual->prox;
        contador++;
    }
    
    printf("\nDigite o indice correspondente ao prato que deseja remover (1-%d): ", contador-1);
    scanf("%d", &indiceSelecionado);
    
    if(indiceSelecionado < 1 || indiceSelecionado >= contador) {
        printf("Indice invalido! Operacao cancelada.\n");
        return;
    }
    
    // Encontra e remove o prato pelo índice
    PratoNode *pratoAnterior = NULL;
    pratoAtual = pedidoAtual->listaPratos;
    int indiceAtual = 1;
    
    while(pratoAtual != NULL && indiceAtual != indiceSelecionado) {
        pratoAnterior = pratoAtual;
        pratoAtual = pratoAtual->prox;
        indiceAtual++;
    }
    
    if(pratoAnterior == NULL) {
        pedidoAtual->listaPratos = pratoAtual->prox;
    } else {
        pratoAnterior->prox = pratoAtual->prox;
    }
    
    char nomePratoRemovido[50];
    strcpy(nomePratoRemovido, pratoAtual->dadosPrato.nome);
    
    free(pratoAtual);
    printf("Prato '%s' removido do pedido %d com sucesso!\n", nomePratoRemovido, idPedido);
    
    // Remove o pedido se não há mais pratos
    if(pedidoAtual->listaPratos == NULL) {
        if(*cabeca == pedidoAtual) {
            *cabeca = pedidoAtual->prox;
        } else {
            Pedido *pedidoAnterior = *cabeca;
            while(pedidoAnterior->prox != pedidoAtual) {
                pedidoAnterior = pedidoAnterior->prox;
            }
            pedidoAnterior->prox = pedidoAtual->prox;
        }
        
        free(pedidoAtual);
        printf("Pedido %d removido completamente (nao tinha mais pratos).\n", idPedido);
    }
}

// Função para processar pedido
void processarPedido(Pedido **cabeca) {
    int idPedido;
    printf("\n--- ENVIAR PEDIDO PARA COZINHA ---\n");

    if (*cabeca == NULL) {
        printf("Nenhum pedido pendente no salao.\n");
        return;
    }

    listarPedidosPendentes(*cabeca);

    printf("Digite o ID do pedido a ser enviado: ");
    scanf("%d", &idPedido);

    Pedido *anterior = NULL;
    Pedido *atual = *cabeca;

    while (atual != NULL && atual->idPedido != idPedido) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Pedido com ID %d nao encontrado no salao.\n", idPedido);
        return;
    }

    // Remove da lista do salão
    if (anterior == NULL) {
        *cabeca = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    enfileirarPedido(atual);
    free(atual); // Libera o pedido original (pois a cozinha já tem sua cópia)
}