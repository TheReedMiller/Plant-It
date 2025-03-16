/**
 * @file GameApp.h
 * @author Reed Miller
 *This is the overarching app of the project
 *
 */
 
#ifndef GAMEAPP_H
#define GAMEAPP_H


/**
 * Main Application Class for the Game
 */
class GameApp :public wxApp{
private:

public:
    bool OnInit() override;
};



#endif //GAMEAPP_H
