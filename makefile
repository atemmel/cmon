SRC_FILES := $(wildcard src/*.cpp external/*/*.cpp) 
LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS := -Wall

INCLUDES := -Iexternal/tinyxml/

build: $(SRC_FILES)
	g++ $(SRC_FILES) $(INCLUDES) $(LIBS) $(CFLAGS) 
run: build
	./a.out
