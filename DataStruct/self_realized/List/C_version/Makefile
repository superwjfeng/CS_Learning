.PHONY:all
all: main list

main:main.c
	gcc -o $@ $^ -std=c99
list:List.c
	gcc -o $@ $^ -std=c99

.PHONY:clean
clean:
	rm -f main list
	

