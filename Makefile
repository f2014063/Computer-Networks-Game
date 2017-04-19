all:
	gcc -g tcp_client.c -o client
	gcc -g tcp_server.c -o server

clean:
	rm -fv client server
