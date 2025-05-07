/**
 * @file MainFrame.h
 * @author Reed Miller
 *The Main Frame of the GUI
 *
 */
 
#ifndef MAINFRAME_H
#define MAINFRAME_H

//Forward References
class GameView;
class TaskView;


class MainFrame : public wxFrame{
private:
    ///Game View Object
    GameView* mGameView = nullptr;
    ///Task View Object
    TaskView* mTaskView = nullptr;

    void OnAbout(wxCommandEvent &event);
    void OnLoad(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnExit(wxCommandEvent &event);

public:
    void Initialize();
};



#endif //MAINFRAME_H
