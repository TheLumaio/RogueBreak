SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))
CLFAGS = --std=c++11 -w -fpermissive
OUT = build/roguebreak

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
LIBS = 
CC = g++

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBS) -o $(OUT)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
