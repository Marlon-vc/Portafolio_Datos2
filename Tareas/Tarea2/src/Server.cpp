#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <ctime>
#include <iostream>
using namespace std;

bool active = false;
const int PORT = 8080;

int file_desc, client_conn, val_read;
sockaddr_in server_address;
int address_len = sizeof(server_address);
int opt = 1;
char buffer[2048] = {0};

int prepare();
void cleanBuffer();
char * getData();
void sendData(char msg[]);

int main() {
	cout << "Initializing server.." << endl;
	if (prepare() != -1) {
		active = true;
		cout << "Waiting connection" << endl;
		listen(file_desc, 1);

		while (active) {
			client_conn = accept(file_desc, (struct sockaddr *) &server_address, (socklen_t *) &address_len);
			cout << "Connected" << endl;
			cleanBuffer();
			string clientMsg = getData();
			if (clientMsg == "hola") {
				sendData("Hola, cómo estás?");
			} else if (clientMsg == "hora") {
				time_t now = time(0);
				tm *ltm = localtime(&now);
				char time_msg[6];
				strncat(time_msg, (char *) ltm->tm_hour, 2);
				strncat(time_msg, ":", 1);
				strncat(time_msg, (char *) ltm->tm_min, 2);
				sendData(time_msg);
			} else if (clientMsg == "adios") {
				sendData("Hasta luego.");
			} else {
				sendData("No he entendido.");
			}
		}
	} else {
		cerr << "An error ocurred during socket initialization" << endl;
		return -1;
	}
	return 0;
}

int prepare() {
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

char * getData() {
	val_read = read(client_conn, buffer, 2048);
	//cout << val_read << " bytes read" << endl;
	cout << "Message received: " << buffer << endl;

	return buffer;
}

void sendData(char msg[]) {
	send(client_conn, msg, strlen(msg), 0);
	cout << "Message sent: " << msg << endl;
}

void cleanBuffer() {
	char a = '\0';
	for (int i = 0; i < 2048; i++) {
		buffer[i] = a;
	}
}

