//
// Created by Davide Meta on 27/08/24.
//

#ifndef MYFRAME_H
#define MYFRAME_H
#include <wx/wx.h>
#include "TodoList.h"

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString &title);

private:
    void OnAdd(wxCommandEvent &event);

    void OnRemove(wxCommandEvent &event);

    void OnSave(wxCommandEvent &event);

    void OnLoad(wxCommandEvent &event);

    void UpdateListBox();

    wxListBox *listBox;
    TodoList todoList;
};

#endif //MYFRAME_H
