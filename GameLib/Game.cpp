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
    auto background = std::make_shared<Background>(this, L"background.png");
    Add(background);

    //Add plant to items
    auto plant = std::make_shared<Plant>(this, L"plant1.png");
    plant->SetPosition(40,220);
    Add(plant);
}

/**
 * Draw all the items within our game
 * @param graphics The graphics we are drawing on
 */
void Game::OnDraw(wxDC* graphics)
{
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
void Game::Load(wxXmlNode* root)
{
    //Clear current data from game
    Clear();

    // Traverse the children of the root
    auto child = root->GetChildren();
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
 * @param root root node of XML
 */
void Game::Save(wxXmlNode *root)
{

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