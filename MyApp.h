//
// Created by Davide Meta on 27/08/24.
//

#ifndef MYAPP_H
#define MYAPP_H
#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

enum {
    ID_Add = 1,
    ID_Remove = 2,
    ID_Save = 3,
    ID_Load = 4
};

#endif //MYAPP_H
