#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/label.h>

#include <iostream>

#include "Client.cpp"

class MyApp: public Gtk::Window {
    public:
        MyApp();
        virtual ~MyApp();
    protected:
        Client client;
        void onButtonClicked();
        Gtk::Box container;
        Gtk::Entry msg_entry;
        Gtk::Button send_button;
        Gtk::Label msg_label;

};

MyApp::MyApp(): container(Gtk::ORIENTATION_VERTICAL), send_button("Enviar") {
    set_default_size(300, 150);
    set_title("C++ Sockets");
    set_border_width(10);
    send_button.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::onButtonClicked));
    container.set_spacing(15);
    container.add(msg_entry);
    container.add(msg_label);
    container.add(send_button);
    add(container);
    show_all_children();
}

MyApp::~MyApp() {
}

void MyApp::onButtonClicked() {
    //std::cout << "Button clicked!" << std::endl;
    string text = msg_entry.get_text();
    if (text != "") {
        std::cout << "Message to send: " << text << endl;
        char *response = client.start(text.c_str());

        msg_entry.set_text("");
        msg_label.set_text(response);
    }
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.tec.datos2");
    MyApp window;
    return app->run(window);
}