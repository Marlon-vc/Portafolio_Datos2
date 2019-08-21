#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/grid.h>
#include <gtkmm-3.0/gtkmm/stack.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include "JsonGenerator.cpp"

enum OperationType {
    bInsert,
    bDelete,
    lInsert,
    lDelete,
    lModify,
    lGet
};

class MyApp: public Gtk::Window {
    public:
        MyApp();
        virtual ~MyApp();
    private:
        OperationType operationType;
        Gtk::Stack mainContainer;
        //Start window
        Gtk::Label startMsg;
        Gtk::Grid startGrid;
        Gtk::Button binaryButton, listButton;
        //Binary Tree
        Gtk::Label binaryTitle, bLabel;
        Gtk::Grid binaryGrid;
        Gtk::Button bInsertButton, bDeleteButton, bBackButton, bSubmit;
        Gtk::Entry bEntry;
        //LinkedList
        Gtk::Label listTitle, lLabel;
        Gtk::Grid listGrid;
        Gtk::Button lInsertStartButton, lDeleteStartButton, lModifyButton, lGetButton, lBackButton, lSubmit;
        Gtk::Entry lEntry, lIndexEntry;
        //Signal Handlers
        void showBinaryWindow();
        void showListWindow();
        void toStart();
        void process();
        //Operation Types
        void _bInsert();
        void _bDelete();
        void _lInsert();
        void _lDelete();
        void _lModify();
        void _lGet();
};

MyApp::MyApp(): 
//start
startMsg("Bienvenido\nSelecciona una estructura"), 
binaryButton("Árbol Binario"), 
listButton("Lista Enlazada"),
//binary
binaryTitle("Árbol Binario"),
bInsertButton("Insertar"),
bDeleteButton("Eliminar"),
bBackButton("Atrás"),
bLabel(),
bEntry(),
bSubmit(),
//List
listTitle("Lista Enlazada"),
lInsertStartButton("Insertar al inicio"), 
lDeleteStartButton("Eliminar al inicio"),
lModifyButton("Modificar"), 
lGetButton("Obtener por posición"),
lBackButton("Atrás")
{
    //Start window
    startMsg.set_vexpand(true);
    startMsg.set_justify(Gtk::JUSTIFY_CENTER);
    binaryButton.set_hexpand(true);
    binaryButton.set_vexpand(true);

    listButton.set_hexpand(true);
    listButton.set_vexpand(true);
    startGrid.attach(startMsg, 0, 0, 2);
    startGrid.attach(binaryButton, 0, 1);
    startGrid.attach(listButton, 1, 1);
    binaryButton.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::showBinaryWindow));
    listButton.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::showListWindow));

    //Binary Tree Window
    binaryGrid.attach(binaryTitle, 0, 0);
    binaryGrid.attach(bInsertButton, 0, 1);
    binaryGrid.attach(bDeleteButton, 0, 2);
    binaryGrid.attach(bBackButton, 1, 3);
    binaryGrid.attach(bLabel, 1, 0);
    binaryGrid.attach(bEntry, 1, 1);
    binaryGrid.attach(bSubmit, 1, 2);

    bEntry.set_placeholder_text("Número..");
    bLabel.set_vexpand(true);
    bLabel.set_hexpand(true);
    binaryGrid.set_margin_start(10);
    binaryGrid.set_margin_end(10);
    binaryGrid.set_margin_top(10);
    binaryGrid.set_margin_bottom(10);
    binaryGrid.set_row_spacing(15);
    binaryGrid.set_column_spacing(15);
    bDeleteButton.set_vexpand(true);
    bInsertButton.set_vexpand(true);

    bInsertButton.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::_bInsert));
    bDeleteButton.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::_bDelete));
    bSubmit.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::process));
    bBackButton.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::toStart));

    //Linked List Window
    listGrid.attach(listTitle, 0, 0);
    listGrid.attach(lInsertStartButton, 0, 1);
    listGrid.attach(lDeleteStartButton, 0, 2);
    listGrid.attach(lModifyButton, 0, 3);
    listGrid.attach(lGetButton, 0, 4);
    listGrid.attach(lBackButton, 1, 5);
    listGrid.attach(lLabel, 1, 0);
    listGrid.attach(lEntry, 1, 1);
    listGrid.attach(lIndexEntry, 1, 2);
    listGrid.attach(lSubmit, 1, 3, 1, 2);

    lEntry.set_placeholder_text("Número..");
    lIndexEntry.set_placeholder_text("Índice a modificar");
    listGrid.set_row_spacing(15);
    listGrid.set_column_spacing(15);
    listGrid.set_margin_start(10);
    listGrid.set_margin_end(10);
    listGrid.set_margin_top(10);
    listGrid.set_margin_bottom(10);
    listTitle.set_vexpand(true);
    lInsertStartButton.set_vexpand(true);
    lDeleteStartButton.set_vexpand(true);
    lModifyButton.set_vexpand(true);
    lGetButton.set_vexpand(true);
    lLabel.set_vexpand(true);
    lLabel.set_hexpand(true);
    
    lInsertStartButton.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::_lInsert));
    lDeleteStartButton.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::_lDelete));
    lModifyButton.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::_lModify));
    lGetButton.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::_lGet));
    lBackButton.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::toStart));
    lSubmit.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::process));

    //Add to main container
    mainContainer.add(startGrid, "start");
    mainContainer.add(binaryGrid, "binary");
    mainContainer.add(listGrid, "list");
    mainContainer.set_hexpand(true);
    mainContainer.set_vexpand(true);

    mainContainer.set_visible_child("start");
    
    set_title("Estructuras");
    set_default_size(620, 400);
    set_resizable(false);
    add(mainContainer);
    show_all_children();
}

void MyApp::showBinaryWindow() {
    std::cout << "Show binary tree operations..\n";
    operationType = bInsert;
    bLabel.set_text("Ingresa el número a insertar");
    bSubmit.set_label("Insertar");
    mainContainer.set_visible_child("binary");
}

void MyApp::showListWindow() {
    std::cout << "show linked list operations..\n";
    operationType = lInsert;
    lLabel.set_text("Ingresa el número a insertar");
    lSubmit.set_label("Insertar");
    lIndexEntry.hide();
    mainContainer.set_visible_child("list");
}
void MyApp::toStart() {
    std::cout << "Back to start menu..\n";
    mainContainer.set_visible_child("start");
}

MyApp::~MyApp() {}

void MyApp::process() {
    std::string structure;
    std::string operation;
    std::string number;
    std::string index;

    switch(operationType) {
        case bInsert:
            structure = "binaryTree";
            operation = "insert";
            number = bEntry.get_text();
            bEntry.set_text("");
            break;
        case bDelete:
            structure = "binaryTree";
            operation = "delete";
            number = bEntry.get_text();
            bEntry.set_text("");
            break;
        case lInsert:
            structure = "linkedList";
            operation = "insert";
            number = lEntry.get_text();
            lEntry.set_text("");
            lIndexEntry.set_text("");
            break;
        case lDelete:
            structure = "linkedList";
            operation = "delete";
            lEntry.set_text("");
            lIndexEntry.set_text("");
            break;
        case lModify:
            structure = "linkedList";
            operation = "modify";
            number = lEntry.get_text();
            index = lIndexEntry.get_text();
            lEntry.set_text("");
            lIndexEntry.set_text("");
            break;
        case lGet:
            structure = "linkedList";
            operation = "get";
            number = lEntry.get_text();
            lEntry.set_text("");
            lIndexEntry.set_text("");
            break;
    }

    std::cout << "Calling createJson()\n";
    json_t *json = createJson((char *) &structure[0], (char *) &operation[0], (char *) &number[0], (char *) &index[0]);
    if (json != nullptr) {
    std::cout << json_dumps(json, JSON_INDENT(4));
    } else {
        std::cout << "Failed to create json object\n";
    }
}

void MyApp::_bInsert() {
    operationType = bInsert;
    bLabel.set_text("Ingresa el número a insertar");
    bSubmit.set_label("Insertar");
}
void MyApp::_bDelete() {
    operationType = bDelete;
    bLabel.set_text("Ingresa eñ número a eliminar");
    bSubmit.set_label("Eliminar");
}
void MyApp::_lInsert() {
    operationType = lInsert;
    lLabel.set_text("Ingresa el número a insertar al inicio");
    lEntry.show();
    lIndexEntry.hide();
    lSubmit.set_label("Insertar");
}
void MyApp::_lDelete() {
    operationType = lDelete;
    lLabel.set_text("Eliminar el primer elemento de la lista");
    lEntry.hide();
    lIndexEntry.hide();
    lSubmit.set_label("Eliminar");
}
void MyApp::_lModify() {
    operationType = lModify;
    lLabel.set_text("Ingresa el indice a modificar");
    lEntry.show();
    lIndexEntry.show();
    lSubmit.set_label("Modificar");
}
void MyApp::_lGet() {
    operationType = lGet;
    lLabel.set_text("Ingresa el índice para obtener su valor");
    lEntry.show();
    lIndexEntry.hide();
    lSubmit.set_label("Obtener");
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "tec.org");
    MyApp window;
    return app->run(window);
}