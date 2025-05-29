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
    Create(nullptr, wxID_ANY, L"Plant-It", wxDefaultPosition, wxSize(1100, 800));

    // create a sizer that will lay out child windows Horizontally
    auto sizer = new wxBoxSizer(wxHORIZONTAL);

    //Create Game View as well as Task view
    mGameView = new GameView();
    mTaskView = new TaskView(this, mGameView->GetBank());

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
    auto plantMenu = new wxMenu();
    auto taskMenu = new wxMenu();

    // Append the menu options to the bar.
    menuBar->Append(fileMenu, L"&File");
    menuBar->Append(helpMenu, L"&Help");
    menuBar->Append(plantMenu, L"&Plants");
    menuBar->Append(taskMenu, L"&Tasks");

    //File Menu
    fileMenu->Append(IDM_LOAD1, "Load Save 1", "Load Save 1");
    fileMenu->Append(IDM_LOAD2, "Load Save 2", "Load Save 2");
    fileMenu->Append(IDM_LOAD3, "Load Save 3", "Load Save 3");
    fileMenu->AppendSeparator();
    fileMenu->Append(IDM_SAVECURRENT, "Save Current Game", "Save Current Game");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_SAVEAS, "Save", "Save the Program");
    fileMenu->Append(wxID_OPEN, "Load", "Load a Program");

    //Help Menu
    helpMenu->Append(wxID_ABOUT, "Game Controls", "View game controls and rules");
    helpMenu->Append(IDM_CHEATCODE, "Cheat Code", "Super Secret Cheat Code");

    //Plant Menu
    plantMenu->Append(IDM_ADDSUNFLOWER, "Buy Sunflower [150]", "Buy Sunflower [150]");
    plantMenu->Append(IDM_ADDROSE, "Buy Rose [200]", "Buy Rose [200]");
    plantMenu->Append(IDM_ADDFERN, "Buy Fern [250]", "Buy Fern [250]");
    plantMenu->Append(IDM_ADDCACTUS, "Buy Cactus [400]", "Buy Cactus [400]");
    plantMenu->Append(IDM_ADDFLYTRAP, "Buy Flytrap [1000]", "Buy Flytrap [1000]");
    plantMenu->AppendSeparator();
    plantMenu->Append(IDM_ADDFERTILIZER, "Buy Fertilizer [200]", "Buy Fertilizer [200]");

    //Task Menu
    taskMenu->Append(IDM_ADDTASK, "Add New Task", "Add New Task");

    SetMenuBar( menuBar );

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnSave, this, wxID_SAVEAS);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLoad, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainFrame::OnShowControls, this, wxID_ABOUT);

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
    auto result = saveFileDialog.ShowModal();

    if (result == wxID_CANCEL)
    {
        return;
    }
    auto filename = saveFileDialog.GetPath();

    //create XML document to save
    wxXmlDocument xmlDoc;
    //Create <game> root
    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"Plant-It");
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

/**
 * Function that Gives the user a description of the Game Controls
 * @param event event to handle
 */
void MainFrame::OnShowControls(wxCommandEvent& event)
{
    wxMessageBox(
        "Plants:\n"
        " - You can Purchase Plants from the Plant Menu Option\n"
        " - Click and Drag your plants where you want\n"
        " - Click on a Plant and Press Backspace/Delete to Sell it\n"
        " - Purchase Fertilizer from the Plant Menu, to increase the \namount of time a plant will stay watered\n"
        " - When a Plant is 'Dry', Click and Drag the Watering Can over\n"
        "   the Plant, then Double-Click the Watering Can to water it\n\n"
        "Tasks:\n"
        " - Tasks can be added from the menu bar.\n"
        " - You can Edit Tasks by right clicking them.\n"
        " - You can Mark Tasks completed by double-clicking them.\n"
        " - Click and Drag your Task to organize how you'd like.\n"
        " - Complete tasks to earn coins for your plant bank! The harder\n"
        "   the difficulty, the more coins you'll earn!\n"
        " - Click a Task and press Backspace/Delete to remove it from the Task Manager\n\n"
        "Save/Load:\n"
        " - Game states can be saved and loaded via the File menu option.\n",
        "Controls",
        wxOK | wxICON_INFORMATION,
        this
    );
}

/**
 * Function that loads the load 1 game state
 * @param event event to handle
 */
void MainFrame::OnLoad1(wxCommandEvent& event)
{
    //Save current state
    //CODE HERE

    //Load in this state
    mLoadState = LoadState::Load1;
    LoadState();
}

/**
 * Function that loads the load 2 game state
 * @param event event to handle
 */
void MainFrame::OnLoad2(wxCommandEvent& event)
{
    //Save current state
    //CODE HERE

    //Load in this state
    mLoadState = LoadState::Load2;
    LoadState();
}

/**
 * Function that loads the load 3 game state
 * @param event event to handle
 */
void MainFrame::OnLoad3(wxCommandEvent& event)
{
    //Save current state
    //CODE HERE

    //Load in this state
    mLoadState = LoadState::Load3;
    LoadState();
}

/**
 * Function to load from a specific game state
 */
void MainFrame::LoadState()
{
    //Get the Correct FileName
    auto filename = L"Levels/load1.game";

    //Game State 2
    if (mLoadState == LoadState::Load2)
    {
        filename = L"Levels/load2.game";
    }

    //Game 3 state
    if (mLoadState == LoadState::Load3)
    {
        filename = L"Levels/load3.game";
    }

    //Create xml document and load from it
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