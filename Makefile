CC=g++
CFLAGS=-c -Wall -Isrc -std=c++0x -g
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf
SOURCESCPP=src/graphicsViewer.cpp src/main.cpp src/ltexture.cpp src/tank.cpp
SOURCESC=
SOURCES=$(SOURCESC) $(SOURCESCPP)
OBJECTS=$(SOURCESCPP:.cpp=.o) $(SOURCESC:.c=.o)
EXECUTABLE=Tanks.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@
