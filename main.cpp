#include <iostream>

#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm.h>

#include <Python.h>

class Window : public Gtk::Window {
public:
    Window();
    virtual ~Window();
protected:
    void on_button_file_clicked();
    void read_PDF(std::string filename);
    
    Gtk::ButtonBox m_ButtonBox;
    Gtk::Button m_Button;
};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    Window window;

    app->run(window);

    return 0;
}

Window::Window() : m_ButtonBox(Gtk::ORIENTATION_VERTICAL), m_Button("Choose File") {
    set_title("Reader");
    
    add(m_ButtonBox);
    
    m_ButtonBox.pack_start(m_Button);
    m_Button.signal_clicked().connect(sigc::mem_fun(*this, &Window::on_button_file_clicked) );
    
    show_all_children();
}

Window::~Window() {}

void Window::on_button_file_clicked() {
    Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);
    
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    
    auto filter_pdf = Gtk::FileFilter::create();
    filter_pdf->set_name("PDF files");
    filter_pdf->add_mime_type("application/pdf");
    dialog.add_filter(filter_pdf);
    
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);
    
    if (dialog.run() == Gtk::RESPONSE_OK) {
        std::string filename = dialog.get_filename();
        
        std::cout << "File selected: " << filename << "\n";

	read_PDF(filename);
    }
}

void Window::read_PDF(std::string filename) {
    char scriptname[] = "../recorder.py";
    FILE* fp;
    
    Py_Initialize(); 
    
    fp = _Py_fopen(scriptname, "r");
    PyRun_SimpleFile(fp, scriptname);
    
    Py_Finalize();
}
