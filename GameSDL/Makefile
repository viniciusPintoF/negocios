OBJS = ./src/*.cpp ./outside/*.cpp
OBJ_NAME = jogo
CC = g++-6
PATH_F = -I./extern/linux/include -L./extern/linux/lib
COMPILER_F = 
LINKER_F = -lSDL2main -lSDL2 -lSDL2_image

all: $(OBJS)
		$(CC) $(OBJS) $(PATH_F) $(COMPILER_F) $(LINKER_F) -o $(OBJ_NAME)
