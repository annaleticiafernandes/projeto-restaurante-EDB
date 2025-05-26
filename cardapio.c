#include <stdio.h>
#include <string.h>
#include "cardapio.h"

void exibirEntradas(){
    printf("\033[3m----------- ENTRADAS -----------\033[0m\n");
    printf("\033[3m1. Sopa de Cebola\033[0m\n");
    printf("\033[3m2. Salada Caesar\033[0m\n");
    printf("\033[3m3. Bruschetta\033[0m\n");
    printf("\033[3m4. Carpaccio de Carne\033[0m\n");
    printf("\033[3m5. Camarao ao Alho\033[0m\n");
}

void exibirPratosPrincipais(){
    printf("\033[3m------- PRATOS PRINCIPAIS -------\033[0m\n");
    printf("\033[3m6. Lasanha a Bolonhesa\033[0m\n");
    printf("\033[3m7. File Mignon com Fritas\033[0m\n");
    printf("\033[3m8. Frango Grelhado com Legumes\033[0m\n");
    printf("\033[3m9. Bacalhau a Gomes de Sa\033[0m\n");
    printf("\033[3m10. Risoto de Cogumelos\033[0m\n");
}

void exibirSobremesas(){
    printf("\033[3m---------- SOBREMESAS ----------\033[0m\n");
    printf("\033[3m11. Tiramisu\033[0m\n");
    printf("\033[3m12. Cheesecake de Frutas Vermelhas\033[0m\n");
    printf("\033[3m13. Mousse de Chocolate\033[0m\n");
    printf("\033[3m14. Pudim de Leite\033[0m\n");
    printf("\033[3m15. Sorvete de Baunilha com Calda de Morango\033[0m\n");
}

void exibirCardapio(){
    printf("\n");
    printf("\033[3m----------- CARDAPIO -----------\033[0m\n");
    printf("\n");
    exibirEntradas();
    printf("\n");
    exibirPratosPrincipais();
    printf("\n");
    exibirSobremesas();
    printf("\033[3m--------------------------------\033[0m\n");
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
            strcpy(nomePrato, "Camarao ao Alho");
            break;
        case 6:
            strcpy(nomePrato, "Lasanha a Bolonhesa");
            break;
        case 7:
            strcpy(nomePrato, "File Mignon com Fritas");
            break;
        case 8:
            strcpy(nomePrato, "Frango Grelhado com Legumes");
            break;
        case 9:
            strcpy(nomePrato, "Bacalhau a Gomes de Sa");
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
            printf("Prato nao encontrado.\n");
            break;
    }
}

