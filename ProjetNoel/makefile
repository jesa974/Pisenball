pinBall : pinBall.o imageSF.o calcul.o gereBouton.o affichage.o debug.o libisentlib.a
	gcc -Wall -o pinBall imageSF.o calcul.o pinBall.o gereBouton.o affichage.o debug.o libisentlib.a -lm -lglut -lGL -lX11

pinBall.o : pinBall.c GfxLib.h BmpLib.h ESLib.h affichage.h gereBouton.h calcul.h debug.h
	gcc -c -Wall pinBall.c
	
gereBouton.o : gereBouton.c BmpLib.h affichage.h gereBouton.h 
	gcc -c -Wall gereBouton.c

debug.o : debug.h
	gcc -c -Wall debug.c
	
calcul.o : calcul.c calcul.h affichage.h debug.h
	gcc -c -Wall calcul.c
	
imageSF.o : imageSF.c imageSF.h
	gcc -c -Wall imageSF.c
	
affichage.o : affichage.c BmpLib.h calcul.h gereBouton.h affichage.h imageSF.h debug.h 
	gcc -c -Wall affichage.c

libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o 
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o
	ranlib libisentlib.a

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc -Wall -O2 -c BmpLib.c

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -c ESLib.c

ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc -Wall -O2 -c ErreurLib.c

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL

OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -c OutilsLib.c

zip:
	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile

clean:
	rm -f *~ *.o *.a

deepclean: clean
	rm -f exemple exempleTortue libisentlib.a

