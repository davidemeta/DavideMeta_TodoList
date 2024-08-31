//
// Created by Davide Meta on 27/08/24.
//
#include "MyApp.h"
#include "MyFrame.h"

MyFrame::MyFrame(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(450, 340)) {
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    listBox = new wxListBox(panel, wxID_ANY);
    vbox->Add(listBox, 1, wxEXPAND | wxALL, 10);

    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *addButton = new wxButton(panel, ID_Add, wxT("Add"));
    hbox1->Add(addButton, 0);
    wxButton *removeButton = new wxButton(panel, ID_Remove, wxT("Remove"));
    hbox1->Add(removeButton, 0, wxLEFT | wxBOTTOM, 5);

    vbox->Add(hbox1, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *saveButton = new wxButton(panel, ID_Save, wxT("Save"));
    hbox2->Add(saveButton, 0);
    wxButton *loadButton = new wxButton(panel, ID_Load, wxT("Upload"));
    hbox2->Add(loadButton, 0, wxLEFT | wxBOTTOM, 5);

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

void MyFrame::OnAdd(wxCommandEvent &event) {
    wxString descrizione = wxGetTextFromUser("Inserisci la descrizione dell'attività:", "Aggiungi Attività");
    if (!descrizione.IsEmpty()) {
        todoList.aggiungiAttivita(Attivita(std::string(descrizione.mb_str())));
        UpdateListBox();
    }
}

void MyFrame::OnRemove(wxCommandEvent &event) {
    int sel = listBox->GetSelection();
    if (sel != wxNOT_FOUND) {
        todoList.rimuoviAttivita(sel);
        UpdateListBox();
    }
}

void MyFrame::OnSave(wxCommandEvent &event) {
    wxFileDialog saveFileDialog(this, _("Salva elenco attività"), "", "",
                                "File di testo (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    todoList.salvaSuDisco(saveFileDialog.GetPath().ToStdString());
}

void MyFrame::OnLoad(wxCommandEvent &event) {
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
    for (const auto &attivita: attivita) {
        listBox->Append(attivita.getDescrizione());
    }
}