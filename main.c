#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salao.h"
#include "cardapio.h"
#include "cozinha.h"

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
    char prato[20][50]; // Supondo que o máximo de pratos por pedido seja 10
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
            printf("Opção invalida! Tente novamente.\n");
            i--; // Decrementa o contador para repetir a escolha
            continue;
        }

        obterNomePrato(indicePrato, nomePrato);
        strcpy(prato[i], nomePrato); // Copia o nome do prato escolhido
        printf("Prato adiconado: %s\n", nomePrato);
    }

    adicionarPedido(cabeca, numMesa, idPedido, prato, qntdPratos);
}


void interfaceRemoverPrato(Pedido **cabeca) {
    int idPedido;
    char nomePrato[50];
    
    printf("\n---- REMOVER PRATO DO PEDIDO ----\n");
    
    // Primeiro mostra os pedidos pendentes
    printf("Pedidos pendentes:\n");
    listarPedidosPendentes(*cabeca);
    
    printf("Digite o ID do pedido: ");
    scanf("%d", &idPedido);
    
    limparBuffer(); // limpa o buffer antes de usar fgets
    
    printf("Digite o nome exato do prato a ser removido: ");
    fgets(nomePrato, sizeof(nomePrato), stdin);
    
    // Remove a quebra de linha do fgets
    nomePrato[strcspn(nomePrato, "\n")] = 0;
    
    removerPrato(cabeca, idPedido, nomePrato);
}


// Função para processar pedido (placeholder para futuro desenvolvimento)
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

int main() {
    Pedido *cabecaSalao = NULL; // inicializa a lista de pedidos do salão como vazia
    int opcao;
    
    printf("Bem-vindo ao Sistema de Gerenciamento de Pedidos do Restaurante!\n");
    
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
                // Aqui você pode adicionar código para liberar a memória
                break;
                
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
        
    } while (opcao != 0);
    
    // Liberar memória antes de sair (implementar se necessário)
    printf("Sistema encerrado com sucesso!\n");
    
    return 0;
}

