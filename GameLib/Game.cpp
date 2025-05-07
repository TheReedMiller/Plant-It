/**
 * @file Game.cpp
 * @author Reed Miller
 */

#include "pch.h"

#include "Game.h"
#include "Item.h"
#include "Background.h"
#include "Plant.h"

using namespace std;

/**
 * Constructor
 */
Game::Game()
{   //Add background to Items
    mBackground = std::make_unique<Background>(this, L"background.png");

    //Create the Bank
    mBank = std::make_shared<Bank>();

}

/**
 * Draw all the items within our game
 * @param graphics The graphics we are drawing on
 */
void Game::OnDraw(wxDC* graphics)
{
    //Draw the background
    mBackground->Draw(graphics);

    //Draw the Bank
    mBank->Draw(graphics);

    //Iterate over the collection of game items
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}


/**
 * Load the game level from a saved XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the game from.
 */
void Game::Load(wxXmlNode* gameNode)
{
    //Clear current data from game
    Clear();

    //Get Root attribute for Bank Amount
    int coins = 0;
    gameNode->GetAttribute(L"coins").ToInt(&coins);
    mBank->SetCoins(coins);

    // Traverse the children of the root
    auto child = gameNode->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"item")
        {
            CreateItem(child);
        }
    }
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Game::CreateItem(wxXmlNode *node)
{
    // // A pointer for the item we are loading
    // shared_ptr<Item> item;
    //
    // // We have an item. What type?
    // auto type = node->GetAttribute(L"type");
    // if (type == L"beta")
    // {
    //     item = make_shared<Background>(this);
    // }
    //
    // else if (type == L"")
    // {
    //     //CODE HERE
    // }
    //
    //
    // if (item != nullptr)
    // {
    //     // //Add the Item to the game
    //     // Add(item);
    //     //
    //     // //Finish Loading the Item's attributes
    //     // item->XmlLoad(node);
    // }
}

/**
 * Function to save the state of the game
 * @param gameNode game root node of XML
 */
void Game::Save(wxXmlNode *gameNode)
{
    //Save Bank Amount of coins
    auto coins = wxString::Format(wxT("%d"), mBank->GetCoins());
    gameNode->AddAttribute(L"coins", coins);

    //Save Each item within the game
    for (auto item : mItems)
    {
        item->Save(gameNode);
    }
}

/**
 * Clears the game data
 *
 * Deletes all known items in the game
 */
void Game::Clear()
{
    //Clear the Vector - making sure to reset size and deallocate memory
    mItems = vector<shared_ptr<Item>>();
}

/**
 * Function to add an item to the game
 * @param item item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}

/**
 *A function to move a grabbed item to the back of the item-list
 *@param item the item to move
 */
void Game::MoveToBack(std::shared_ptr<Item> item)
{
    //First We Find the Location of the clicked item
    auto loc = find(begin(mItems), end(mItems), item);
    if (loc != end(mItems))
    {
        //Remove the original element from the vector
        mItems.erase(loc);
        //Add it back to the end of the list
        mItems.push_back(item);
    }
}