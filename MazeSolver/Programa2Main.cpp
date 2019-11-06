/***************************************************************
 * Name:      Programa2Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    Angelo Ramirez Ortega/Guilliano D'Ambrosio Soza ()
 * Created:   2017-11-16
 * Copyright: Angelo Ramirez Ortega/Guilliano D'Ambrosio Soza ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "Programa2Main.h"
#include "DrawingPane.h"
#include "ChargingPane.h"
//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(Programa2Frame, wxFrame)
    EVT_CLOSE(Programa2Frame::OnClose)
    EVT_MENU(idMenuQuit, Programa2Frame::OnQuit)
    EVT_MENU(idMenuAbout, Programa2Frame::OnAbout)
    EVT_BUTTON(idBtnCargarLaberinto, Programa2Frame::onCargarLaberinto)
    EVT_BUTTON(idBtnCrearLaberinto, Programa2Frame::onCrearLaberinto)
END_EVENT_TABLE()

Programa2Frame::Programa2Frame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    //Creacion de los componentes de la ventana principal
    #if wxUSE_MENUS
        // create a menu bar
        wxMenuBar* mbar = new wxMenuBar();
        wxMenu* fileMenu = new wxMenu(_T(""));
        fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
        mbar->Append(fileMenu, _("&File"));

        wxMenu* helpMenu = new wxMenu(_T(""));
        helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
        mbar->Append(helpMenu, _("&Help"));

        SetMenuBar(mbar);
    #endif // wxUSE_MENUS

    #if wxUSE_STATUSBAR
        // create a status bar with some information about the used wxWidgets version
        CreateStatusBar(2);
        SetStatusText(_("Bienvenido a MazeSolver 2017"),0);
        SetStatusText((wxString)"V.1.0", 1);
    #endif // wxUSE_STATUSBAR
    this->SetSizeHints(400, 380);
    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer(wxVERTICAL);
    new wxStaticText(this, wxID_ANY, wxT("Por favor seleccione una opcion"), wxPoint(50,50), wxDefaultSize, 0);
    wxButton* BtnCrearLaberinto = new wxButton(this, idBtnCrearLaberinto, wxT("&Generar Laberinto"), wxPoint(105,150), wxDefaultSize, 0);
    wxButton* BtnCargarLaberinto = new wxButton(this, idBtnCargarLaberinto, wxT("&Cargar Un Laberinto"), wxPoint(95,200), wxDefaultSize, 0);
    this->SetSizer(bSizer1);
    this->Layout();
    bSizer1->Fit(this);
}


Programa2Frame::~Programa2Frame()
{
}

void Programa2Frame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void Programa2Frame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void Programa2Frame::OnAbout(wxCommandEvent &event)
{
    //Despliega infomracion acerca de los autores del proyecto
    wxMessageBox(_("Angelo Ramirez Ortega-2017080055\nGuilliano D'Ambrosio-2017158561"), _("Acerca de"));
}

void Programa2Frame::onCrearLaberinto(wxCommandEvent &event){
    LaberintoView* wframe = new LaberintoView(this,_("Generacion de Laberinto"));
    wframe->ShowWindowModal();
}
void Programa2Frame::onCargarLaberinto(wxCommandEvent &event){
    CargarView* wframe = new CargarView(this,_("Carga de Laberintos"));
    wframe->ShowWindowModal();
}
