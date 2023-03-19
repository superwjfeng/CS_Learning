CC=g++
FLAGS=-std=c++11
LD=-lpthread
bin=test
src=Test.cc

$(bin):$(src)
	$(CC) -o $@ $^ $(LD) $(FLAGS)

.PHONY:clean
clean:
	rm -f $(bin)
