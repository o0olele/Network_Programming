aim: client.out server.out

client.out: client.c
	gcc -o client.out client.c

server.out: server.c
	gcc -o server.out server.c


.PHONY: clean
clean: 
	-rm -rf *.out