.PHONY:all
all:mykill myproc

myproc:myproc.cc
	g++ -o $@ $^ -std=c++11
mykill:mykill.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f mykill myproc
