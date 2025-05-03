/**
 * @file Game.cpp
 * @author Reed Miller
 */

#include "pch.h"

#include "Game.h"
#include "Item.h"
#include "Background.h"

using namespace std;

/**
 * Constructor
 */
Game::Game()
{
    mBackground = make_unique<wxBitmap>(
            L"images/background.png", wxBITMAP_TYPE_ANY);

}

/**
 * Draw al the items within our game
 * @param graphics The graphics we are drawing on
 */
void Game::OnDraw(wxDC* graphics)
{
    graphics->DrawBitmap(*mBackground, 0, 0);
}


/**
 * Load the game level from a saved XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the game from.
 */
void Game::Load(const wxString &filename)
{
    //Create XML document, try and load it
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Game file");
        return;
    }

    Clear();       //Clear any current date

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"item")
        {
            XmlItem(child);
        }
    }
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Game::XmlItem(wxXmlNode *node)
{
    // A pointer for the item we are loading
    shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetAttribute(L"type");
    if (type == L"beta")
    {
        item = make_shared<Background>(this);
    }

    else if (type == L"")
    {
        //CODE HERE
    }


    if (item != nullptr)
    {
        // //Add the Item to the game
        // Add(item);
        //
        // //Finish Loading the Item's attributes
        // item->XmlLoad(node);
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