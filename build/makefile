SERVER_DIR = ../source/server/*
CLIENT_DIR = ../source/client/*

all: server client

server: $(SERVER_DIR)
	g++ $(SERVER_DIR) -O0 -Wall -o server

client: $(CLIENT_DIR)
	g++ $(CLIENT_DIR) -o client

clear:
	rm server client *.o
