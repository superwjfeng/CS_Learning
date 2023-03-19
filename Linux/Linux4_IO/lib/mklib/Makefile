.PHONY:all
all:libhello.so libhello.a

libhello.so:mymath_d.o myprint_d.o
	gcc -std=c99 -shared mymath_d.o myprint_d.o -o libhello.so
mymath_d.o:mymath.c
	gcc -std=c99 -c -fPIC mymath.c -o mymath_d.o
myprint_d.o:myprint.c
	gcc -std=c99 -c -fPIC myprint.c -o myprint_d.o

libhello.a: mymath.o myprint.o
	ar -rc libhello.a mymath.o myprint.o
mymath.o:mymath.c
	gcc -std=c99 -c mymath.c -o mymath.o
myprint.o:myprint.c
	gcc -std=c99 -c myprint.c -o myprint.o

.PHONY:output
output:
	mkdir -p output/lib
	mkdir -p output/include
	cp -rf *.h output/include
	cp -rf *.a output/lib
	cp -rf *.so output/lib

.PHONY:clean
clean:
	rm -rf *.o *.a *.so output
