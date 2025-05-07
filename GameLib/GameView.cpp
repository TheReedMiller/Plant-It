/**
 * @file GameView.cpp
 * @author Reed Miller
 */
 
#include "pch.h"

#include "ids.h"
#include "GameView.h"

#include "Cactus.h"
#include "Flytrap.h"
#include "Plant.h"
#include "Item.h"
#include "Sunflower.h"
#include "Rose.h"

///Frame Duration Constant
const int FrameDuration = 30;

/**
 * Initialize the Game view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    //Bind Event Handlers
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    //Menu Event Handlers
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddSunflower, this, IDM_ADDSUNFLOWER);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddRose, this, IDM_ADDROSE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddCactus, this, IDM_ADDCACTUS);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddFlytrap, this, IDM_ADDFLYTRAP);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mTime = 0;
    mStopWatch.Start();
}

/**
 * A function to add timer functionality
 * @param event event we are handling
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    mTime = mStopWatch.Time() / 1000;
    Refresh();
}

/**
 * A function to handle the paint event
 * @param event event we are handling
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    mGame.OnDraw(&dc);
}

/**
 * Handle the left mouse button down event
 * @param event The mouse click event
 */
void GameView::OnLeftDown(const wxMouseEvent &event)
{
    mGrabbedItem = mGame.HitTest(event.GetX(), event.GetY());
    if (mGrabbedItem != nullptr)
    {
        // Move to Back of List
        mGame.MoveToBack(mGrabbedItem);

    }
}

/**
* Handle the left mouse button down event
* @param event
*/
void GameView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse movement event
* @param event
*/
void GameView::OnMouseMove(wxMouseEvent &event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetPosition(event.GetX(), event.GetY());
        }
        else
        {
            // When the left button is released, we release the
            // item.
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }
}

/**
 * save function for this view
 * @param root root node of xml
 */
void GameView::Save(wxXmlNode* root)
{
    //Create game node
    auto gameNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"Game");

    auto value = wxString::Format(wxT("%d"), mTime);
    gameNode->AddAttribute(L"time", value);
    root->AddChild(gameNode);

    //Call to game to save
    mGame.Save(gameNode);
}

/**
 *Load function for this view
 * @param gameNode game root node of xml
 */
void GameView::Load(wxXmlNode* gameNode)
{
    //Set Time/Stopwatch
    gameNode->GetAttribute(L"time").ToInt(&mTime);
    mStopWatch.Start(mTime * 1000);

    //Load game
    mGame.Load(gameNode);
}

/**
 * Function to add a sunflower to our game
 */
void GameView::OnAddSunflower(wxCommandEvent& event)
{
    auto item = std::make_shared<Sunflower>(&mGame);
    mGame.Add(item);
    Refresh();
}
/**
 * Function to add a rose to our game
 */
void GameView::OnAddRose(wxCommandEvent& event)
{
    auto item = std::make_shared<Rose>(&mGame);
    mGame.Add(item);
    Refresh();
}
/**
 * Function to add a cactus to our game
 */
void GameView::OnAddCactus(wxCommandEvent& event)
{
    auto item = std::make_shared<Cactus>(&mGame);
    mGame.Add(item);
    Refresh();
}
/**
 * Function to add a flytrap to our game
 */
void GameView::OnAddFlytrap(wxCommandEvent& event)
{
    auto item = std::make_shared<Flytrap>(&mGame);
    mGame.Add(item);
    Refresh();
}