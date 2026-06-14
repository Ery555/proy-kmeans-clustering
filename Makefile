# Compilador y banderas
CC = gcc
CFLAGS = -Wall -O3 -fopenmp -I./include
LDFLAGS = -lm

# Directorios
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Detección de Sistema Operativo
ifeq ($(OS),Windows_NT)
    # Configuración para Windows
    EXEC_SEC = $(BINDIR)/secuencial.exe
    EXEC_PAR = $(BINDIR)/paralelo.exe
    # Comando para crear directorios en Windows CMD/PowerShell si no existen
    MKDIR_OBJ = if not exist $(OBJDIR) mkdir $(OBJDIR)
    MKDIR_BIN = if not exist $(BINDIR) mkdir $(BINDIR)
else
    # Configuración para Linux/Lubuntu
    EXEC_SEC = $(BINDIR)/secuencial
    EXEC_PAR = $(BINDIR)/paralelo
    MKDIR_OBJ = mkdir -p $(OBJDIR)
    MKDIR_BIN = mkdir -p $(BINDIR)
endif

all: directories $(EXEC_SEC) $(EXEC_PAR)

directories:
	@$(MKDIR_OBJ)
	@$(MKDIR_BIN)

$(EXEC_SEC): $(OBJDIR)/main_secuencial.o $(OBJDIR)/kmeans_secuencial.o $(OBJDIR)/utils.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(EXEC_PAR): $(OBJDIR)/main_paralelo.o $(OBJDIR)/kmeans_paralelo.o $(OBJDIR)/utils.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	rmdir /S /Q $(OBJDIR) $(BINDIR)
else
	rm -rf $(OBJDIR) $(BINDIR)
endif