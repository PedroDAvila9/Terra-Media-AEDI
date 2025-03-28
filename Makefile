# -- compilador
CC = gcc
# -- flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -g -Iincludes
# -- nome do executável
TARGET = terra_media
# -- arquivos fonte
SRC = main.c src/terra_media.c src/fila.c src/pilha.c src/inventario.c
# -- arquivos objeto
OBJ = $(SRC:.c=.o)
# -- headers
HEADERS = includes/terra_media.h includes/fila.h includes/pilha.h includes/inventario.h

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