#ifndef CARDAPIO_H
#define CARDAPIO_H

void exibirCardapio();

void obterNomePrato(int indice, char *nomePrato);

void exibirEntradas();

void exibirPratosPrincipais();

void exibirSobremesas();

int obterIndicePrato(const char *nomePrato);
#endif