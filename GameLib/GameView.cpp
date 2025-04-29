/**
 * @file GameView.cpp
 * @author Reed Miller
 */
 
#include "pch.h"

#include "ids.h"
#include "GameView.h"

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

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);


    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    mStopWatch.Start();
}

/**
 * A function to add timer functionality
 * @param event event we are handling
 */
void GameView::OnTimer(wxTimerEvent& event)
{
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
    Refresh();
}