#include <wx/wx.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class Attivita {
public:
    Attivita(const std::string &descrizione, bool completata = false)
        : descrizione(descrizione), completata(completata) {
    }

    std::string getDescrizione() const {
        return descrizione;
    }

    bool isCompletata() const {
        return completata;
    }

    void setCompletata(bool completata) {
        this->completata = completata;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << descrizione << "," << completata;
        return ss.str();
    }

    static Attivita fromString(const std::string &str) {
        std::stringstream ss(str);
        std::string descrizione;
        std::string completataStr;
        std::getline(ss, descrizione, ',');
        std::getline(ss, completataStr);
        bool completata = (completataStr == "1");
        return Attivita(descrizione, completata);
    }

private:
    std::string descrizione;
    bool completata;
};

class TodoList {
public:
    void aggiungiAttivita(const Attivita &attivita) {
        attivitaList.push_back(attivita);
    }

    void rimuoviAttivita(int index) {
        if (index >= 0 && index < attivitaList.size()) {
            attivitaList.erase(attivitaList.begin() + index);
        }
    }

    std::vector<Attivita> getAttivita() const {
        return attivitaList;
    }

    void salvaSuDisco(const std::string &filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto &attivita: attivitaList) {
                file << attivita.toString() << std::endl;
            }
            file.close();
        } else {
            std::cerr << "Impossibile aprire il file per la scrittura." << std::endl;
        }
    }

    void caricaDaDisco(const std::string &filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            attivitaList.clear();
            std::string line;
            while (std::getline(file, line)) {
                attivitaList.push_back(Attivita::fromString(line));
            }
            file.close();
        } else {
            std::cerr << "Impossibile aprire il file per la lettura." << std::endl;
        }
    }

private:
    std::vector<Attivita> attivitaList;
};

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnAdd(wxCommandEvent& event);
    void OnRemove(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnLoad(wxCommandEvent& event);
    void UpdateListBox();

    wxListBox* listBox;
    TodoList todoList;
};

enum {
    ID_Add = 1,
    ID_Remove = 2,
    ID_Save = 3,
    ID_Load = 4
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame("Todo List");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(450, 340)) {

    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    listBox = new wxListBox(panel, wxID_ANY);
    vbox->Add(listBox, 1, wxEXPAND | wxALL, 10);

    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *addButton = new wxButton(panel, ID_Add, wxT("Aggiungi"));
    hbox1->Add(addButton, 0);
    wxButton *removeButton = new wxButton(panel, ID_Remove, wxT("Rimuovi"));
    hbox1->Add(removeButton, 0, wxLEFT | wxBOTTOM , 5);

    vbox->Add(hbox1, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *saveButton = new wxButton(panel, ID_Save, wxT("Salva"));
    hbox2->Add(saveButton, 0);
    wxButton *loadButton = new wxButton(panel, ID_Load, wxT("Carica"));
    hbox2->Add(loadButton, 0, wxLEFT | wxBOTTOM , 5);

    vbox->Add(hbox2, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    panel->SetSizer(vbox);

    Connect(ID_Add, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(MyFrame::OnAdd));
    Connect(ID_Remove, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(MyFrame::OnRemove));
    Connect(ID_Save, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(MyFrame::OnSave));
    Connect(ID_Load, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(MyFrame::OnLoad));

    Centre();
}

void MyFrame::OnAdd(wxCommandEvent& event) {
    wxString descrizione = wxGetTextFromUser("Inserisci la descrizione dell'attività:", "Aggiungi Attività");
    if (!descrizione.IsEmpty()) {
        todoList.aggiungiAttivita(Attivita(std::string(descrizione.mb_str())));
        UpdateListBox();
    }
}

void MyFrame::OnRemove(wxCommandEvent& event) {
    int sel = listBox->GetSelection();
    if (sel != wxNOT_FOUND) {
        todoList.rimuoviAttivita(sel);
        UpdateListBox();
    }
}

void MyFrame::OnSave(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, _("Salva elenco attività"), "", "",
                                "File di testo (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    todoList.salvaSuDisco(saveFileDialog.GetPath().ToStdString());
}

void MyFrame::OnLoad(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("Carica elenco attività"), "", "",
                                "File di testo (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    todoList.caricaDaDisco(openFileDialog.GetPath().ToStdString());
    UpdateListBox();
}

void MyFrame::UpdateListBox() {
    listBox->Clear();
    std::vector<Attivita> attivita = todoList.getAttivita();
    for (const auto& attivita : attivita) {
        listBox->Append(attivita.getDescrizione());
    }
}
