#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

const int PORT = 8080;

class Client {
    public:
        int PORT = 8080;
        char *start(const char *msg);
        Client();
        ~Client();
    protected:
        char buffer[2048] = {0};
        int file_desc, val_read;
        sockaddr_in server_address;
        int prepare();
        char *getData();
        void sendData(const char *msg);
		void cleanBuffer();
};

Client::Client() {
    std::cout << "Initializing client.." << endl;
}

Client::~Client() {
    std::cout << "Destroying client.." << endl;
}

char *Client::start(const char *msg) {
    if (prepare() != -1) {
        connect(file_desc, (struct sockaddr *) &server_address, sizeof(server_address));
        sendData(msg);
		cleanBuffer();
        char *response = getData();
        return response;
    } else {
        std::cerr << "Error during socket initialization" << endl;
        return (char *) "[Error]";
    }
}

int Client::prepare() {
	try {
		file_desc = socket(AF_INET, SOCK_STREAM, 0);
		server_address.sin_family = AF_INET;
        server_address.sin_port = htons(PORT);
        inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
		return 0;
	} catch (exception) {
		return -1;
	}
}

char *Client::getData() {
	val_read = read(file_desc, buffer, 2048);
	//cout << val_read << " bytes read" << endl;
	cout << "Message received: " << buffer << endl;
	return buffer;
}

void Client::sendData(const char *msg) {
	send(file_desc, msg, strlen(msg), 0);
	//cout << "Message sent!" << endl;
}

void Client::cleanBuffer() {
	char a = '\0';
	for (int i = 0; i < 2048; i++) {
		buffer[i] = a;
	}
}

int main() {
    Client *client = new Client();
    char msg[] = "Hello server!";
    client->start(msg);
}
