#include "ServerLogic.cpp"

int main() {
    StructuresLogic *logic = new StructuresLogic();
    Server *server = new Server(logic);
    server->start();
}