#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <iostream>

class MyApp: public Gtk::Window {
    public:
        MyApp();
        virtual ~MyApp();
    private:
        Gtk::Box container;
        Gtk::Button button1;

        void buttonPressed();
};

void MyApp::buttonPressed() {
    std::cout << "Button pressed!\n";
}

MyApp::MyApp(): container(Gtk::ORIENTATION_VERTICAL), button1("Press Me!") {
    container.add(button1);
    button1.signal_clicked().connect(sigc::mem_fun(*this, &MyApp::buttonPressed));
    add(container);
    show_all_children();
}

MyApp::~MyApp() {
    
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "tec");
    MyApp window;
    return app->run(window);
}