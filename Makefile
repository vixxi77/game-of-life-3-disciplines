CC = gcc
CFLAGS = $(shell sdl2-config --cflags --libs)


golsdl:
	$(CC) $(CFLAGS) gol_sdl2.c -o golsdl  

clean:
	rm golsdl
