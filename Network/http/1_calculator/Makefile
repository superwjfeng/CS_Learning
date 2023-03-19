.PHONY:all
all:tcpClient tcpServerd
Method=#-DMY_SELF

tcpClient: tcpClient.cc
	g++ -o $@ $^ $(Method) -std=c++11 -ljsoncpp
tcpServerd: tcpServer.cc
	g++ -o $@ $^ $(Method) -std=c++11 -ljsoncpp -lpthread

.PHONY:clean
clean:
	rm -f tcpClient tcpServerd