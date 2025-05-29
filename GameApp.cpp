/**
 * @file GameApp.cpp
 * @author Reed Miller
 */

#include "pch.h"

#include <wx/stdpaths.h>

#include "GameApp.h"
#include "MainFrame.h"

/**
 * Initialize the application.
 * @return bool representing the success of running the app
 */
bool GameApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto standardPaths = wxStandardPaths::Get();
    auto frame = new MainFrame(standardPaths.GetResourcesDir().ToStdWstring());
    frame->Initialize();

    frame->SetFocus();
    frame->Raise();
    frame->Show(true);

    return true;
}