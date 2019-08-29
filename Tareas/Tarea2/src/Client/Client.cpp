#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <jansson.h>

const int PORT = 8080;

class Client {
    public:
        int PORT = 8080;
        json_t *start(json_t *msg);
        json_t *createJson(const char *structure, const char *operation, const char *numberPtr, const char *indexPtr = "-");
        Client();
        ~Client();
    protected:
        char buffer[2048] = {0};
        int file_desc, val_read;
        sockaddr_in server_address;
        int prepare();
        json_t *getData();
        void sendData(json_t *data);
		void cleanBuffer();
};

Client::Client() {
    std::cout << "Initializing Client..\n";
}

Client::~Client() {
    std::cout << "Destroying Client..\n";
}

json_t *Client::start(json_t *msg) {
    if (prepare() != -1) {
        connect(file_desc, (struct sockaddr *) &server_address, sizeof(server_address));
        sendData(msg);
		cleanBuffer();
        return getData();
    } else {
        std::cout << "Error during socket initialization\n";
        json_t *error = json_object();
        json_object_set_new(error, "status", json_string("connection_error"));
        return error;
    }
}

int Client::prepare() {
	try {
		file_desc = socket(AF_INET, SOCK_STREAM, 0);
		server_address.sin_family = AF_INET;
        server_address.sin_port = htons(PORT);
        inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
		return 0;
	} catch (std::exception) {
		return -1;
	}
}

json_t *Client::getData() {
	val_read = read(file_desc, buffer, 2048);
	std::cout << "Response from server:\n" << buffer << "\n";
    json_error_t error;
    json_t *response = json_loads(buffer, JSON_INDENT(4), &error);
    if (!response) {
        json_t *error_json = json_object();
        json_object_set_new(error_json, "status", json_string("invalid_response_from_server")); 
        return error_json;
    } else {
        return response;
    }
}

void Client::sendData(json_t *data) {
    char *charData = json_dumps(data, JSON_INDENT(4));
    std::cout << "json to send\n" << charData << "\n";
    size_t dataLength = strlen(charData);
	send(file_desc, charData, dataLength, 0);
}

void Client::cleanBuffer() {
	char a = '\0';
	for (int i = 0; i < 2048; i++) {
		buffer[i] = a;
	}
}

json_t *Client::createJson(const char *structure, const char *operation, const char *numberPtr, const char *indexPtr) {
    // std::cout << "Creating object..\n";
    json_t *obj = json_object();
    json_object_set_new(obj, "structure", json_string(structure));
    json_object_set_new(obj, "operation", json_string(operation));
    // std::cout << "Performing string to number conversion..\n";
    int number;
    int index;
    try {
        number = strtol(numberPtr, 0, 10);
        if (strcmp(indexPtr, "-") != 0) {
            index = strtol(indexPtr, 0, 10);
        }
    } catch (std::exception) {
        std::cout << "Number from string convertion failed.\n";
        return nullptr;
    }
    // std::cout << "..done.\n";
    json_object_set_new(obj, "number", json_integer(number));
    json_object_set_new(obj, "index", json_integer(index));
    return obj;
}