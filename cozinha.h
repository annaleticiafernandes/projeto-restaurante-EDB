#ifndef COZINHA_H
#define COZINHA_H

#include "salao.h"

// Enfileira um pedido vindo do salão para a cozinha
void enfileirarPedido(Pedido *pedido);

// Processa o próximo pedido da fila (remove da fila)
void processarProximoPedido();

// Lista todos os pedidos atualmente na cozinha
void listarPedidosCozinha();

#endif
