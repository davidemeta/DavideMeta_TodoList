//
// Created by Davide Meta on 27/08/24.
//

#ifndef MYFRAME_H
#define MYFRAME_H

#include <wx/wx.h>
#include <wx/checklst.h>
#include "TodoList.h"

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString &title);

private:
    void OnAdd(wxCommandEvent &event);
    void OnRemove(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnLoad(wxCommandEvent &event);
    void OnCheck(wxCommandEvent &event);   // New method to handle check box
    void OnSearch(wxCommandEvent &event);  // New method to handle search
    void UpdateListBox();

    wxCheckListBox *listBox;
    wxTextCtrl *searchCtrl;  // Member variable for the search control
    wxStaticText *remainingText;
    TodoList todoList;

    enum {
        ID_Add = 1,
        ID_Remove,
        ID_Save,
        ID_Load
    };
};

#endif // MYFRAME_H