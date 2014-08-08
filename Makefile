SRC = $(wildcard source/*.cpp)
LIB = -lGL -lGLU -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_gfx

all: 
	g++ $(SRC) -o WriteSmart $(LIB) 

clean:
	@echo Cleaning up...
	@rm WriteSmart
	@echo Done.
