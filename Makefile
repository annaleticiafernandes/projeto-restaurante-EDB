# Nome do executável
TARGET = restaurante

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99

# Arquivos fonte
SRCS = main.c salao.c cardapio.c cozinha.c

# Arquivos objeto (gerados a partir dos .c)
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Linka os objetos para formar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compila os .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa arquivos gerados
# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /Q
else
    RM = rm -f
endif

# Arquivos a serem removidos
OBJS = main.o salao.o cardapio.o cozinha.o
TARGET = restaurante

.PHONY: clean

clean:
	$(RM) $(OBJS) $(TARGET)

# Facilita a reconstrução completa
rebuild: clean all