.PHONY:all
all:tcpClient tcpServerd

tcpClient: tcpClient.cc
	g++ -o $@ $^ -std=c++11
tcpServerd: tcpServer.cc
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY:clean
clean:
	rm -f tcpClient tcpServerd