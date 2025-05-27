/**
 * @file Game.cpp
 * @author Reed Miller
 */

#include "pch.h"

#include "Game.h"
#include "Item.h"
#include "Background.h"
#include "Plant.h"
#include "Rose.h"
#include "Flytrap.h"
#include "Cactus.h"
#include "Sunflower.h"
#include "Fern.h"
#include "Fertilizer.h"

using namespace std;

/**
 * Constructor
 */
Game::Game()
{   //Add background to Items
    mBackground = std::make_unique<Background>(this, L"background.png");

    //Create the Bank
    mBank = std::make_shared<Bank>();

    //Create Watering can
    ResetWateringCan(true);     //Bool is true, because we want to create and add the watering can

    //Try adding Fertilizer
    auto fert = std::make_shared<Fertilizer>(this);
    fert->SetPosition(150,150);
    Add(fert);
}

/**
 * Draw all the items within our game
 * @param gc The graphics we are drawing on
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> gc)
{
    //Draw the background
    mBackground->Draw(gc);

    //Draw the Bank
    mBank->Draw(gc);

    //Iterate over the collection of game items
    for (auto item : mItems)
    {
        item->Draw(gc);
    }
}

/**
 * Update function for animation within the game
 * @param elampsed time elapsed since last update
 */
void Game::Update(double elapsed)
{
    //Call the Update function on each item within the game
    for (auto item : mItems)
    {
        item->Update(elapsed);
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
 * @param childNode XML node
 */
void Game::CreateItem(wxXmlNode* childNode)
{
    // A pointer for the item we are loading
    shared_ptr<Item> item;

    // We have an item. What type?
    auto type = childNode->GetAttribute(L"type");

    //Rose Plant
    if (type == L"rose")
    {
        item = make_shared<Rose>(this);
    }

    //Sunflower Plant
    else if (type == L"sunflower")
    {
        item = make_shared<Sunflower>(this);
    }

    //Sunflower Plant
    else if (type == L"fern")
    {
        item = make_shared<Fern>(this);
    }

    //Cactus Plant
    else if (type == L"cactus")
    {
        item = make_shared<Cactus>(this);
    }

    //Flytrap Plant
    else if (type == L"flytrap")
    {
        item = make_shared<Flytrap>(this);
    }

    if (item != nullptr)
    {
        //Add the Item to the game
        Add(item);

        //Finish Loading the Item's attributes
        item->Load(childNode);
    }
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

    //Add the Watering Can Back
    ResetWateringCan(true);
}

/**
 * Function to add an item to the game
 * @param item item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
    item->SetPosition(580,300);
}

/**
 * Function to Remove a given item from this game
 * @param item item to remove
 */
void Game::Remove(std::shared_ptr<Item> item)
{
    //Remove the Given Task
    mItems.erase(std::remove(mItems.begin(), mItems.end(), item),mItems.end());
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

/**
 * This function finds if there is a plant that can be watered
 * @param x x coord of Watering action
 * @param y y coord of Watering action
 */
void Game::WaterPlant(double x, double y)
{
    //Pointer to the found item
    std::shared_ptr<Item> foundItem = nullptr;

    //Iterate over items and see if we found an item(SPECIAL VERSION OF HIT TEST)
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        //If the Hit is Successful
        if ((*i)->HitTest(x, y))
        {
            //Make sure this item is not the watering can
            if ((*i)->IsWaterable())
            {
                //Set the found item
                foundItem =*i;
            }

        }
    }

    //If item was found
    if (foundItem != nullptr)
    {
        //Check if this Item is Dry
        if (foundItem->IsDry())
        {
            //If it is, then water it
            foundItem->Toggle();
        }
    }
}

/**
 * A Function to Reset the Creation and Placement of the Watering Can
 * @param isCreate tells if we need to create the Watering can, or just reset it placement
 */
void Game::ResetWateringCan(bool isCreate)
{
    //If bool is set, create a new watering can
    if (isCreate)
    {
        mWateringCan = make_shared<WateringCan>(this);
        Add(mWateringCan);
    }

    //Reset Positioning
    mWateringCan->SetPosition(580,780);
}

/**
 * Event Function to attempt to fertilize a plant item
 * @param x x coord of the event to fertilize plants
 * @param y y coord of the event to fertilize plants
 * @return bool representing if the fertilize action was successful
 */
bool Game::FertilizePlant(double x, double y)
{
    //Pointer to the found item
    std::shared_ptr<Item> foundItem = nullptr;

    //Iterate over items and see if we found an item(SPECIAL VERSION OF HIT TEST)
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        //If the Hit is Successful
        if ((*i)->HitTest(x, y))
        {
            //Make sure this item is a plant
            if ((*i)->IsWaterable())
            {
                //Set the found item
                foundItem =*i;
            }

        }
    }

    //If item was found
    if (foundItem != nullptr)
    {
        //Fertilize the Plant
        foundItem->Click();

        //Return the Success State
        return true;
    }
    //Didn't find a Plant to fertilize
    return false;
}