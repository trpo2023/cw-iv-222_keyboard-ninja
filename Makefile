all: game

game: 
	gcc src/main.c src/libs/ninja.c -o obj/main

obj:
	mkdir -p $@

clean:
	rm -rf obj/main