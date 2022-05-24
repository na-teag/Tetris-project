

exec : main.o display.o functions.o tetriminos.o tutorial.o
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

clear :
	rm -f *.o
	rm -f bin/exec

#save :
#	rm -f save1/oldsave/*
#	cp save1/*.c save1/oldsave/
#	cp save1/*.h save1/oldsave/
#	cp save1/*.txt save1/oldsave/
#	rm -f save1/*.c
#	rm -f save1/*.h
#	rm -f save1/*.txt
#	cp src/*.c save1/
#	cp src/*.h save1/
#	cp src/*.txt save1/
#	cp Makefile save1/
