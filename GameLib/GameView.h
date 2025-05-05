/**
 * @file GameView.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "Game.h"



class GameView : public wxWindow {
private:
    /// An object that describes our Game
    Game mGame;
    /// The timer that allows for animation
    wxTimer mTimer;
    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;
    int mTime = 0;

    void OnTimer(wxTimerEvent& event);

public:
    void Initialize(wxFrame *parent);
    void OnPaint(wxPaintEvent& event);
    void OnLeftDown(const wxMouseEvent &event);
    void Save(wxXmlNode* root);
};



#endif //GAMEVIEW_H
