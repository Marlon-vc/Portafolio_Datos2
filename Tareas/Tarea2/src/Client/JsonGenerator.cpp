#include <jansson.h>
#include <iostream>
#include <string>

json_t *createJson(const char *structure, const char *operation, const char *numberPtr, const char *indexPtr = "-") {
    std::cout << "Creating object..\n";

    json_t *obj = json_object();

    json_object_set_new(obj, "structure", json_string(structure));
    json_object_set_new(obj, "operation", json_string(operation));
    std::cout << "Performing string to number conversion..\n";
    
    int number;
    int index;
    try {
        number = strtol(numberPtr, 0, 10);
        index = strtol(indexPtr, 0, 10);
    } catch (std::exception) {
        std::cout << "..conversion failed.\n";
        return nullptr;
    }
    std::cout << "..done.\n";

    json_object_set_new(obj, "number", json_integer(number));
    if (indexPtr != "-") {
        json_object_set_new(obj, "index", json_integer(index));
    }

    return obj;
}
