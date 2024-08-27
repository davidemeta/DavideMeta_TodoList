//
// Created by Davide Meta on 27/08/24.
//
#include "MyApp.h"
#include "MyFrame.h"

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame("Todo List");
    frame->Show(true);
    return true;
}