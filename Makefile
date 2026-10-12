# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -g

# Dossiers
OBJ_DIR = obj
SRC_DIR = .
MODEL_DIR = models

# Nom de l'exécutable généré à la racine
TARGET = moulinette.exe

# Liste de tous les objets (les modifiables + les précompilés figés)
OBJS = $(OBJ_DIR)/CreerStructure.o \
       $(OBJ_DIR)/CreerUnArc.o \
       $(OBJ_DIR)/CreerUnePlace.o \
       $(OBJ_DIR)/CreerUneTransition.o \
       $(OBJ_DIR)/ExtraireJetons.o \
       $(OBJ_DIR)/GenerateurCode.o \
       $(OBJ_DIR)/GenererLog.o \
       $(OBJ_DIR)/NettoyerLaChaine.o \
       $(OBJ_DIR)/NettoyerMemoire.o \
       $(OBJ_DIR)/strsplit.o \
       $(OBJ_DIR)/main.o

# Règle principale
all: $(OBJ_DIR) $(MODEL_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MODEL_DIR):
	mkdir -p $(MODEL_DIR)

# Édition de liens (crée l'exécutable à la racine)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 1. Règle spécifique pour recompiler GenerateurCode.c s'il change
$(OBJ_DIR)/GenerateurCode.o: $(SRC_DIR)/GenerateurCode.c types.h
	$(CC) $(CFLAGS) -c $< -o $@

# 2. Règle spécifique pour recompiler GenererLog.c s'il change
$(OBJ_DIR)/GenererLog.o: $(SRC_DIR)/GenererLog.c types.h
	$(CC) $(CFLAGS) -c $< -o $@

# 3. Règle spécifique pour recompiler main.c s'il change
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c types.h fonctions.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage sécurisé : supprime uniquement l'exécutable, les .o précompilés restent intacts
clean:
	rm -f $(TARGET)

.PHONY: all clean
