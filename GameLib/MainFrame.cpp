/**
 * @file MainFrame.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "TaskView.h"
#include "ids.h"


/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Plant-It", wxDefaultPosition, wxSize(1300, 800));

    // create a sizer that will lay out child windows Horizontally
    auto sizer = new wxBoxSizer(wxHORIZONTAL);

    //Create Game View as well as Task view
    mGameView = new GameView();
    mTaskView = new TaskView(this);

    //Call to initialize
    mGameView->Initialize(this);

    //Add Views to the Sizer
    sizer->Add(mGameView, 1, wxEXPAND | wxALL);
    sizer->Add(mTaskView, 0, wxEXPAND | wxALL);

    //Set the sizer for this frame
    SetSizer( sizer );
    Layout();

    // The top bar containing all the menu options
    auto menuBar = new wxMenuBar( );

    // Menu options
    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    // Append the menu options to the bar.
    menuBar->Append(helpMenu, L"&Help");
    menuBar->Append(fileMenu, L"&File");

    //Add to menus
    fileMenu->Append(wxID_SAVEAS, "Save", "Save the Program");
    fileMenu->Append(wxID_OPEN, "Load", "Load a Program");

    SetMenuBar( menuBar );

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnSave, this, wxID_SAVEAS);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLoad, this, wxID_OPEN);

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

/**
 * Event handler for loading file
 * @param event event to handle
 */
void MainFrame::OnLoad(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, _("Load Game file"), "", "",
            "Game Files (*.game)|*.game", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    //Get filename and create XML node
    auto filename = loadFileDialog.GetPath();
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Animation file");
        return;
    }

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //Game View and Task view nodes
    wxXmlNode* gameNode = nullptr;
    wxXmlNode* taskNode = nullptr;

    //Iterate to find nodes
    auto childNode = root->GetChildren();
    while(childNode)
    {
        //Check for Game View Node
        if (childNode->GetName() == L"Game")
        {
            gameNode = childNode;
        }

        //Check for Task View Node
        if (childNode->GetName() == L"Task")
        {
            taskNode = childNode;
        }

        //Get Next Child
        childNode = childNode->GetNext();
    }

    //Load both Views
    mGameView->Load(gameNode);
    mTaskView->Load(taskNode);
}

/**
 * Event Handler for saving files
 * @param event event to handle
 */
void MainFrame::OnSave(wxCommandEvent& event)
{
    //Create Dialog Box to get filepath
    wxFileDialog saveFileDialog(this, _("Save Game file"), "", "",
            "Game Files (*.game)|*.game", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    auto filename = saveFileDialog.GetPath();

    //create XML document to save
    wxXmlDocument xmlDoc;
    //Create <game> root
    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"TaskManager");
    xmlDoc.SetRoot(root);

    //Call to Views to save
    mGameView->Save(root);
    mTaskView->Save(root);

    //Final action ->Save the File itself
    if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}