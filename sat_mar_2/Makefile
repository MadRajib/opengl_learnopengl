SRC_DIR := src
ASSET_DIR := assets
OBJ_DIR := obj
BIN_DIR := build
CC := gcc

EXE := $(BIN_DIR)/opengl
SRC := $(wildcard $(SRC_DIR)/*.c)

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CPPFLAGS := -Iinclude							# -I is a preprocessor flag, not a compiler flag
CFLAGS   := -Wall -g3
LDFLAGS  :=										# -L is a linker flag
LDLIBS   := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

all: $(EXE) copy_assets

$(EXE): $(OBJ) | $(BIN_DIR)
		$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
		mkdir -p $@

copy_assets:
	cp -r $(ASSET_DIR) $(BIN_DIR)

clean:
		@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
