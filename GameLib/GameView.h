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

    ///The Current Time within the game
    int mTime = 0;

    ///Current Time for Animation
    int mAnimationTime = 0;

    ///Pointer to a Grabbed Item
    std::shared_ptr<Item> mGrabbedItem = nullptr;

    ///Pointer to Most Recently Selected Item
    std::shared_ptr<Item> mSelectedItem = nullptr;

    ///Bool to track if the game is currently saving the game
    bool mIsSaving = false;

    ///Animation time for the 'saving' icon on screen
    int mSaveTime = 0;

    void OnTimer(wxTimerEvent& event);

public:
    void Initialize(wxFrame *parent);
    void OnPaint(wxPaintEvent& event);
    void OnLeftDown(const wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnDoubleClick(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void Save(wxXmlNode* root);
    void Load(wxXmlNode* root);
    void OnAddSunflower(wxCommandEvent& event);
    void OnAddRose(wxCommandEvent& event);
    void OnAddCactus(wxCommandEvent& event);
    void OnAddFlytrap(wxCommandEvent& event);
    void OnAddFertilizer(wxCommandEvent& event);
    void OnAddFern(wxCommandEvent& event);
    void OnKeyDown(wxKeyEvent& event);

    /**
     * Getter for the Bank within Game
     * @return Bank of the underlying game
     */
    std::shared_ptr<Bank> GetBank(){return mGame.GetBank();}

    /**
     * Function to toggle the saving state of the game(for animation)
     */
    void GameSaved(){mIsSaving = true;}
};



#endif //GAMEVIEW_H
