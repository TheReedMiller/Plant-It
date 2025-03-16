/**
 * @file MainFrame.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Plant-It", wxDefaultPosition, wxSize(1000, 800));

    // create a sizer that will lay out child windows vertically
    auto sizer = new wxBoxSizer(wxVERTICAL);

    // Create the view class object as a child of MainFrame
    auto gameView = new GameView();
    gameView->Initialize(this);

    //Add it to the sizer
    sizer->Add(gameView, 1, wxEXPAND | wxALL);

    // Set the sizer for this frame
    SetSizer( sizer );

    Layout();

    // The top bar containing all the menu options
    auto menuBar = new wxMenuBar( );

    // Menu options
    auto fileMenu = new wxMenu();
    auto loadMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    // Append the menu options to the bar.
    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(loadMenu, L"&Load" );
    menuBar->Append(helpMenu, L"&Help");

    SetMenuBar( menuBar );

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to !",
                 L"About this ",
                 wxOK,
                 this);
}
