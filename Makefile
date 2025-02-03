# Variáveis
CC = g++                # Compilador (para C++, use g++)
CFLAGS = -Wall -Werror -g       # Flags de compilação (avisos e debug)
TARGET = myavl          # Nome do executável
SRC = main.cpp         # Código-fonte
OBJ = $(SRC:.cpp=.o)    # Arquivo objeto correspondente

# Regra padrão: compilar o executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Regra para compilar o arquivo .o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza (remove arquivos gerados)
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: clean