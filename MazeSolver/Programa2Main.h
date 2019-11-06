/***************************************************************
 * Name:      Programa2Main.h
 * Purpose:   Defines Application Frame
 * Author:    Angelo Ramirez Ortega/Guilliano D'Ambrosio Soza ()
 * Created:   2017-11-16
 * Copyright: Angelo Ramirez Ortega/Guilliano D'Ambrosio Soza ()
 * License:
 **************************************************************/

#ifndef PROGRAMA2MAIN_H
#define PROGRAMA2MAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "Programa2App.h"

class Programa2Frame: public wxFrame
{
    public:
        Programa2Frame(wxFrame *frame, const wxString& title);
        ~Programa2Frame();
    protected:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout,
            idBtnCrearLaberinto,
            idBtnCargarLaberinto
        };
        wxButton* CrearLaberinto;

    private:
         DECLARE_EVENT_TABLE()
         void OnClose(wxCloseEvent& event);
         void OnQuit(wxCommandEvent& event);
         void OnAbout(wxCommandEvent& event);
         void onCrearLaberinto(wxCommandEvent& event);
         void onCargarLaberinto(wxCommandEvent& event);
};


#endif // PROGRAMA2MAIN_H
