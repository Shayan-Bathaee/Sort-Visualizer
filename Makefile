CFLAGS = -Wall -Wextra -Werror -pthread
LFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CC = g++

OBJS = sort.cpp
OBJ_NAME = sort

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(OBJ_NAME)

clean: 
	rm sort