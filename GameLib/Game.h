/**
 * @file Game.h
 * @author Reed Miller
 *
 */
 
#ifndef GAME_H
#define GAME_H


/**
 * This class describes the Game Itself
 */
class Game {
private:
    ///Temporary pointer to Background
    std::shared_ptr<wxBitmap> mBackground;

public:
    Game();
    void OnDraw(wxDC* graphics);
};



#endif //GAME_H
