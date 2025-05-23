#include <stdio.h>
#include <string.h>
#include "cardapio.h"

void exibirEntradas(){
    printf("---- ENTRADAS ----\n");
    printf("1. Sopa de Cebola\n");
    printf("2. Salada Caesar\n");
    printf("3. Bruschetta\n");
    printf("4. Carpaccio de Carne\n");
    printf("5. Camarão ao Alho\n");
}

void exibirPratosPrincipais(){
    printf("---- PRATOS PRINCIPAIS ----\n");
    printf("6. Lasanha à Bolonhesa\n");
    printf("7. Filé Mignon com Fritas\n");
    printf("8. Frango Grelhado com Legumes\n");
    printf("9. Bacalhau à Gomes de Sá\n");
    printf("10. Risoto de Cogumelos\n");
}

void exibirSobremesas(){
    printf("---- SOBREMESAS ----\n");
    printf("11. Tiramisu\n");
    printf("12. Cheesecake de Frutas Vermelhas\n");
    printf("13. Mousse de Chocolate\n");
    printf("14. Pudim de Leite\n");
    printf("15. Sorvete de Baunilha com Calda de Morango\n");
}

void exibirCardapio(){
    printf("---- CARDÁPIO ----\n");
    exibirEntradas();
    printf("\n");
    exibirPratosPrincipais();
    printf("\n");
    exibirSobremesas();
    printf("----------------------\n");
}

void obterNomePrato(int indice, char *nomePrato){
    switch(indice){
        case 1:
            strcpy(nomePrato, "Sopa de Cebola");
            break;
        case 2:
            strcpy(nomePrato, "Salada Caesar");
            break;  
        case 3: 
            strcpy(nomePrato, "Bruschetta");
            break;
        case 4:
            strcpy(nomePrato, "Carpaccio de Carne");
            break;
        case 5:
            strcpy(nomePrato, "Camarão ao Alho");
            break;
        case 6:
            strcpy(nomePrato, "Lasanha à Bolonhesa");
            break;
        case 7:
            strcpy(nomePrato, "Filé Mignon com Fritas");
            break;
        case 8:
            strcpy(nomePrato, "Frango Grelhado com Legumes");
            break;
        case 9:
            strcpy(nomePrato, "Bacalhau à Gomes de Sá");
            break;
        case 10:
            strcpy(nomePrato, "Risoto de Cogumelos");
            break;
        case 11:
            strcpy(nomePrato, "Tiramisu");
            break;
        case 12:   
            strcpy(nomePrato, "Cheesecake de Frutas Vermelhas");
            break;
        case 13:
            strcpy(nomePrato, "Mousse de Chocolate");
            break;
        case 14:
            strcpy(nomePrato, "Pudim de Leite");
            break;
        case 15:
            strcpy(nomePrato, "Sorvete de Baunilha com Calda de Morango");
            break;
        default:
            printf("Prato não encontrado.\n");
            break;
    }
}