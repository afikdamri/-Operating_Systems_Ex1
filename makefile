CC = gcc
FLAGS= 
all: server main

server: server.o
	$(CC) $(FLAGS)  $^ -o server

main: main.o client.o
	$(CC) $(FLAGS) $^ -o main	

%.o: %.c
	$(CC) -c $< -o $@
clean:
	rm *.o server main