#include "Server.cpp"
#include <yajl/yajl_parse.h>
#include <yajl/yajl_gen.h>

class StructuresLogic: public ServerLogic { };

char *StructuresLogic::ServerLogic::process(char *data) {
	
	return "response";
}

int main() {
	StructuresLogic *logic = new StructuresLogic();
	Server *server = new Server(logic);
	server->start();
}