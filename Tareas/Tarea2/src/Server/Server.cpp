#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <ctime>
#include <iostream>
using namespace std;

int main() {
	Server *server = new Server();
	server->start();
}

class Server {
	public:
		Server();
		bool active;
		int PORT;
		void start();
	private:
		int file_desc, client_conn;
		sockaddr_in server_address;
		int address_len;
		int opt;
		char buffer[2048];
		int prepare();
		void cleanBuffer();
		char *process();
};

Server::Server() {
	address_len = sizeof(server_address);
	opt = 1;
	buffer[2048] = {0};
	active = false;
	PORT = 8080;
}

void Server::start() {
	if (prepare() != -1) {
		active = true;
		listen(file_desc, 1);
		cout << "Server started successfully\n";
		while (active) {
			cout << "Waiting connection \n";
			client_conn = accept(file_desc, (struct sockaddr *) &server_address, (socklen_t *) &address_len);
			cout << "Connected to client..\n";
			cleanBuffer();

			//Data read stored in buffer.
			read(client_conn, buffer, 2048);

			char *msg = process();

			//Send data to client.
			send(client_conn, msg, strlen(msg), 0);
		}
	} else {
		cerr << "An error ocurred during socket initialization" << endl;
	}
}

int Server::prepare() {
	try {
		file_desc = socket(AF_INET, SOCK_STREAM, 0);
		setsockopt(file_desc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = INADDR_ANY;
		server_address.sin_port = htons(PORT);
		bind(file_desc, (struct sockaddr *) &server_address, sizeof(server_address));
		return 0;
	} catch (exception) {
		return -1;
	}
}

void Server::cleanBuffer() {
	char a = '\0';
	for (int i = 0; i < 2048; i++) {
		buffer[i] = a;
	}
}

char *Server::process() {
	cout << "Data received: " << buffer << "\n";
	static char msg[] = "Received successfully";
	return msg;
}

