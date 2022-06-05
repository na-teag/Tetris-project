

exec : main.o display.o functions.o tetriminos.o tutorial.o beta.o -lcurses
	gcc $^ -o bin/$@
main.o : src/main.c src/header.h src/color.h
	gcc -c $< -o $@ 

display.o: src/display.c src/header.h src/color.h
	gcc -c $< -o $@ 

functions.o: src/functions.c src/header.h src/color.h
	gcc -c $< -o $@ 

tetriminos.o: src/tetriminos.c src/header.h src/color.h
	gcc -c $< -o $@ 

tutorial.o: src/tutorial.c src/header.h src/color.h
	gcc -c $< -o $@ 

beta.o: src/beta.c src/header.h src/color.h
	gcc -c $< -o $@ 


clear :
	rm -f *.o
	rm -f bin/exec

