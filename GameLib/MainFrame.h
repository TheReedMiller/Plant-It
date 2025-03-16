/**
 * @file MainFrame.h
 * @author Reed Miller
 *The Main Frame of the GUI
 *
 */
 
#ifndef MAINFRAME_H
#define MAINFRAME_H



class MainFrame : public wxFrame{
private:
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);

public:
    void Initialize();
};



#endif //MAINFRAME_H
