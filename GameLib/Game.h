/**
 * @file Game.h
 * @author Reed Miller
 *
 */
 
#ifndef GAME_H
#define GAME_H

#include "Item.h"

/**
 * This class describes the Game Itself
 */
class Game {
private:
    ///Temporary pointer to Background
    std::shared_ptr<wxBitmap> mBackground;

    ///Container to hold all the game's Items
    std::vector<std::shared_ptr<Item>> mItems;

public:
    Game();
    void OnDraw(wxDC* graphics);
    void Load(wxXmlNode* root);
    void CreateItem(wxXmlNode *node);
    void Save(wxXmlNode* root);
    void Clear();
    void Add(std::shared_ptr<Item> item);
};



#endif //GAME_H
