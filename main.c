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
                printf("\033[31mOpcao invalida! Tente novamente.\033[0m\n");
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
    printf("\033[1m-------- MENU PRINCIPAL --------\033[0m\n");
    printf("\033[1m1. Adicionar Pedido\033[0m\n");
    printf("\033[1m2. Remover Prato de um Pedido\033[0m\n");
    printf("\033[1m3. Listar Pedidos Pendentes\033[0m\n");
    printf("\033[1m4. Exibir Cardapio\033[0m\n");
    printf("\033[1m5. Processar Pedido (Enviar para a Cozinha)\033[0m\n");
    printf("\033[1m0. Sair\033[0m\n");
    printf("\033[1m--------------------------------\033[0m\n");
    printf("\033[1mEscolha uma opcao: \033[0m");
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
        printf("\033[31mQuantidade invalida de pratos!\033[0m\n");
        return;
    }

    exibirCardapio();

    for(int i=0; i<qntdPratos; i++){
        printf("Escolha o prato %d (1-15): ", i+1);
        scanf("%d", &indicePrato);

        if(indicePrato < 1 || indicePrato > 15){
            printf("\033[31mOpçao invalida! Tente novamente.\033[0m\n");
            i--; 
            continue;
        }

        obterNomePrato(indicePrato, nomePrato);
        strcpy(prato[i], nomePrato);
        printf("\033[32mPrato adicionado: %s\033[0m\n", nomePrato);
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
        printf("\033[31mPedido com ID %d nao encontrado.\033[0m\n", idPedido);
        return;
    }
    
    // Verifica se o pedido tem pratos
    if(pedidoAtual->listaPratos == NULL) {
        printf("\033[31mNenhum prato encontrado no pedido %d.\033[0m\n", idPedido);
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
        printf("\033[31mIndice invalido! Operacao cancelada.\033[0m\n");
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
    printf("\033[32mPrato '%s' removido do pedido %d com sucesso!\033[0m\n", nomePratoRemovido, idPedido);
    
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
        printf("\033[32mPedido %d removido completamente (nao tinha mais pratos).\033[0m\n", idPedido);
    }
}

// Função para processar pedido
void processarPedido(Pedido **cabeca) {
    printf("\033[32m\n--- PEDIDO ENVIADO PARA COZINHA ---\033[0m\n");

    if (*cabeca == NULL) {
        printf("Nenhum pedido pendente no salao.\n");
        return;
    }

    Pedido *atual = *cabeca;

    *cabeca = atual->prox;
    atual->prox = NULL;

    Pedido *copia = copiarPedido(atual);
    enfileirarPedido(copia);

    printf("\033[32mPedido processado:\033[0m\n");
    imprimirPedido(atual);

    liberarPedido(atual);   
}