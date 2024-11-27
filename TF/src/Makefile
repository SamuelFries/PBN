# Nome do executável
TARGET = App

# Compilador
CC = gcc

# Diretórios
INCLUDE_DIR = /opt/homebrew/include/SDL2
LIB_DIR = /opt/homebrew/lib

# Flags de compilação
CFLAGS = -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR) -lSDL2 -lSDL2_image

# Fonte
SRC = App.c

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Regra para limpar arquivos gerados
clean:
	rm -f $(TARGET)

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)