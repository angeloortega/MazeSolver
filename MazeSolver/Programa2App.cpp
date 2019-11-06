/***************************************************************
 * Name:      Programa2App.cpp
 * Purpose:   Code for Application Class
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

#include "Programa2App.h"
#include "Programa2Main.h"
#include "wx/wx.h"
#include "wx/sizer.h"

IMPLEMENT_APP(Programa2App);

bool Programa2App::OnInit()
{
    Programa2Frame* dlg = new Programa2Frame(0L, _("MazeSolver 2017"));
    dlg->Show();

    return true;
}
