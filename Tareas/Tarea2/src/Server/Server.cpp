#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <jansson.h>

#include <ifaddrs.h>
#include <arpa/inet.h>

class ServerLogic {
	public:
		virtual json_t *process(json_t *json) = 0;
		virtual json_t *on_decode_error(const char *error_msg) = 0;
};

class Server {
	public:
		Server(ServerLogic *logicProcessor);
		bool active;
		int PORT;
		void start();
	private:
		ServerLogic *logicProcessor;
		int file_desc, client_conn;
		sockaddr_in server_address;
		int address_len;
		int opt;
		char buffer[2048];
		int prepare();
		void cleanBuffer();
		char *getServerIp();
};

Server::Server(ServerLogic *logicProcessor) {
	this->logicProcessor = logicProcessor;
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
		std::cout << "Server started successfully\n";
		while (active) {
			std::cout << "Waiting connection..\n";
			client_conn = accept(file_desc, (struct sockaddr *) &server_address, (socklen_t *) &address_len);
			std::cout << "Connected to client\n";

			//Clean the buffer
			cleanBuffer();

			//Data read stored in clean buffer.
			read(client_conn, buffer, 2048);

			std::cout << "Json received from client\n" << buffer << "\n";

			json_error_t error;
			json_t *client_msg = json_loads(buffer, JSON_INDENT(4), &error);
			json_t *msg_to_send;

			if (!client_msg) {
				//Generate error json
				msg_to_send = logicProcessor->on_decode_error(error.text);
			} else {
				//Send the data from client to the serverLogic class to handle it
				msg_to_send = logicProcessor->process(client_msg);
			}

			//Convert the json to a char * to send it
			char *json_to_send = json_dumps(msg_to_send, JSON_INDENT(4));
			size_t json_bytes = strlen(json_to_send);

			std::cout << "Json to send\n" << json_to_send << "\n";

			//Send data to client.
			send(client_conn, json_to_send, json_bytes, 0);
		}
	} else {
		std::cerr << "An error ocurred during socket initialization\n";
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
		std::cout << "Server started in address " << getServerIp();
		std::cout << " at port " << PORT << "\n";
		return 0;
	} catch (std::exception) {
		return -1;
	}
}

char *Server::getServerIp() {
	struct ifaddrs *ifap, *ifa;
	struct sockaddr_in *sa;
	char *addr;
	getifaddrs(&ifap);
	for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET) {
			sa = (struct sockaddr_in *) ifa->ifa_addr;
			addr = inet_ntoa(sa->sin_addr);
			if (strcmp(addr, "127.0.0.1") != 0) {
				return addr;
			}
		}
	}
	static char not_found[] = "[not found]";
	return not_found;
}

void Server::cleanBuffer() {
	char a = '\0';
	for (int i = 0; i < 2048; i++) {
		buffer[i] = a;
	}
}
