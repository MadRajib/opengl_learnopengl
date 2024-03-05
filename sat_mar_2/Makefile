SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := build

CC := gcc
CXX := g++

EXE := $(BIN_DIR)/opengl

SRC_C := $(wildcard $(SRC_DIR)/*.c)
SRC_CPP := $(wildcard $(SRC_DIR)/*.cpp)

OBJ_C := $(SRC_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_CPP := $(SRC_CPP:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude							# -I is a preprocessor flag, not a compiler flag

CFLAGS   := -Wall -g3
CXXFLAGS := -Wall -g3

LDFLAGS  :=										# -L is a linker flag
LDLIBS   := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: $(EXE)

$(EXE): $(OBJ_C) $(OBJ_CPP)| $(BIN_DIR)
		$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
		mkdir -p $@

clean:
		@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
