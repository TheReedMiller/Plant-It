/**
 * @file Game.h
 * @author Reed Miller
 *
 */
 
#ifndef GAME_H
#define GAME_H

#include "Item.h"
#include "Background.h"
#include "Bank.h"
#include "WateringCan.h"

//forward references

/**
 * This class describes the Game Itself
 */
class Game {
private:
    ///Background for game
    std::unique_ptr<Background> mBackground;

    ///Bank for game
    std::shared_ptr<Bank> mBank = nullptr;

    ///WateringCan for game
    std::shared_ptr<WateringCan> mWateringCan = nullptr;

    ///Container to hold all the game's Items
    std::vector<std::shared_ptr<Item>> mItems;

public:
    Game();
    void OnDraw(std::shared_ptr<wxGraphicsContext> gc);
    void Update(double elapsed);
    void Load(wxXmlNode* gameNode);
    void CreateItem(wxXmlNode *childNode);
    void Save(wxXmlNode* root);
    void Clear();
    void Add(std::shared_ptr<Item> item);
    void Remove(std::shared_ptr<Item> item);
    std::shared_ptr<Item> HitTest(int x, int y);
    void MoveToBack(std::shared_ptr<Item> item);
    void WaterPlant(int x, int y);

    /**
     * Getter for the Bank
     * @return Bank of this game
     */
    std::shared_ptr<Bank> GetBank(){return mBank;}
};



#endif //GAME_H
