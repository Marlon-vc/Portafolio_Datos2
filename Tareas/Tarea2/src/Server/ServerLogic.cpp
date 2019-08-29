#include "Server.cpp"
#include "../Structures/BinaryTree.cpp"
#include "../Structures/LinkedList.cpp"

class StructuresLogic: public ServerLogic {
	public:
		StructuresLogic();
		BinaryTree *tree;
		LinkedList *list;
		virtual json_t *process(json_t *json);
		virtual json_t *on_decode_error(const char *error_msg);
		void check(bool *valid, json_t *s, json_t *o, json_t *n, json_t *i);
};

StructuresLogic::StructuresLogic() {
	tree = new BinaryTree();
	list = new LinkedList();
}

json_t *StructuresLogic::process(json_t *json) {
	json_t *response = json_object();
	bool valid = true;
	json_t *json_structure = json_object_get(json, "structure");
	json_t *json_operation = json_object_get(json, "operation");
	json_t *json_number = json_object_get(json, "number");
	json_t *json_index = json_object_get(json, "index");

	check(&valid, json_structure, json_operation, json_number, json_index);

	if (valid) {
		const char *structure = json_string_value(json_structure);
		const char *operation = json_string_value(json_operation);
		int number = json_integer_value(json_number);
		int index = json_integer_value(json_index);

		if (strcmp(structure, "binaryTree") == 0) {
			//Binary operations
			if (strcmp(operation, "insert") == 0) {
				tree->insert(number);
			} else {
				tree->remove(number);
			}
			json_object_set_new(response, "structure", json_string(&tree->getString()[0]));
			json_object_set_new(response, "status", json_string("success"));
			json_object_set_new(response, "return_value", json_boolean(false));
		} else {
			//List operations
			if (strcmp(operation, "insert") == 0) {
				list->insertStart(number);
				json_object_set_new(response, "return_value", json_boolean(false));
			} else if (strcmp(operation, "delete") == 0) {
				list->deleteStart();
				json_object_set_new(response, "return_value", json_boolean(false));
			} else if (strcmp(operation, "modify") == 0) {
				list->modify(number, index);
				json_object_set_new(response, "return_value", json_boolean(false));
			} else {
				int number_got = list->get(number);
				json_object_set_new(response, "return_value", json_boolean(true));
				json_object_set_new(response, "number", json_integer(number_got));
			}
			json_object_set_new(response, "structure", json_string(&list->getString()[0]));
			json_object_set_new(response, "status", json_string("success"));
		}
	} else {
		return on_decode_error("Bad argument types");
	}
	return response;
}

json_t *StructuresLogic::on_decode_error(const char *msg) {
	json_t *json = json_object();
	json_object_set_new(json, "Status", json_string("Error"));
	json_object_set_new(json, "Msg", json_string(msg));
	return json;
}

void StructuresLogic::check(bool *valid, json_t *s, json_t *o, json_t *n, json_t *i) {
	if (!json_is_string(s)) {
		*valid = false;
	}
	if (!json_is_string(o)) {
		*valid = false;
	}
	if (!json_is_integer(n)) {
		*valid = false;
	}
	if (!json_is_integer(i)) {
		*valid = false;
	}
}