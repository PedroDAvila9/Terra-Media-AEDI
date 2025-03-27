# -- compilador
CC = gcc
# -- flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -g
# -- nome do executável
TARGET = terra_media
# -- arquivos fonte
SRC = main.c terra_media.c fila.c pilha.c inventario.c
# -- arquivos objeto
OBJ = $(SRC:.c=.o)
# -- headers
HEADERS = terra_media.h fila.h pilha.h

# -- regra principal
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# -- regra para cada arquivo objeto
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# -- limpeza
clean:
	rm -f $(OBJ) $(TARGET)

# -- execução (opcional)
run: all
	./$(TARGET)

# -- regras especiais
.PHONY: all clean run