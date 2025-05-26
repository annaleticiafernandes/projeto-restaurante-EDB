
# 📋 Sistema de Gerenciamento de Pedidos – Restaurante (Simulação em C)

Este projeto simula o funcionamento de um sistema de pedidos em um restaurante. Ele permite o controle dos pedidos realizados no salão e o envio desses pedidos para a cozinha para serem processados.

---

## 🧱 Estrutura do Projeto

O sistema está organizado em módulos:

- **main.c** – Interface principal do programa, com o menu e fluxo geral.
- **salao.c / salao.h** – Lógica da lista ligada de pedidos feita no salão.
- **cardapio.c / cardapio.h** – Exibição do cardápio e nome dos pratos.
- **cozinha.c / cozinha.h** – Gerencia a fila de pedidos processados na cozinha.
- **fila.c / fila.h** – Implementação auxiliar de estrutura de fila para uso interno na cozinha.

### Estruturas usadas:

- **Pedido** – Cada pedido contém o número da mesa, ID, lista de pratos e ponteiro para o próximo pedido.
- **PratoNode** – Lista ligada interna com os pratos de um pedido.

---

## ▶️ Como o Sistema Funciona

O sistema apresenta o seguinte menu principal:

```
1. Adicionar Pedido
2. Remover Prato de um Pedido
3. Listar Pedidos Pendentes
4. Exibir Cardápio
5. Processar Pedido (Enviar para a Cozinha)
6. Listar Pedidos na Cozinha
0. Sair
```

---

### 1. Adicionar Pedido
Permite ao usuário inserir:

- Número da mesa  
- ID do pedido  
- Quantidade de pratos  
- Escolher pratos com base em um cardápio (entradas, principais e sobremesas)  

Os pratos escolhidos são adicionados à lista ligada de pedidos do salão.

---

### 2. Remover Prato de um Pedido
- Exibe os pedidos pendentes  
- Solicita o ID do pedido  
- Solicita o nome exato do prato a ser removido  
- Se o prato for removido e o pedido ficar sem pratos, o pedido também é removido.

---

### 3. Listar Pedidos Pendentes
- Mostra todos os pedidos atualmente no salão  
- Exibe o número da mesa, ID do pedido e os pratos associados

---

### 4. Exibir Cardápio
Mostra todas as opções disponíveis separadas por categoria:

- Entradas  
- Pratos Principais  
- Sobremesas  

---

### 5. Processar Pedido
- Solicita o ID do pedido que será enviado para a cozinha  
- Remove o pedido do salão  
- Copia os dados do pedido e adiciona à fila da cozinha  
- Exibe confirmação do envio

---

### 6. Listar Pedidos na Cozinha
- Mostra todos os pedidos que foram processados e estão na fila da cozinha  
- Exibe o número da mesa, ID e os pratos de cada pedido  

---

## 🛠️ Compilação e Execução

### Compilar:
```bash
gcc main.c salao.c cardapio.c cozinha.c fila.c -o restaurante
```

### Executar:
```bash
./restaurante
```

---

## ✅ Requisitos

- Compilador C (GCC ou compatível)  
- Terminal para interação com o usuário  
