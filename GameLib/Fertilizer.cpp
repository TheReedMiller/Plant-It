/**
 * @file Fertilizer.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Fertilizer.h"
#include "Game.h"

Fertilizer::Fertilizer(Game* game) : Item(game, L"fertilizer.png")
{

}


/**
 * Function to save the state of this fertilizer
 * @param gameNode root node of XML
 * @return a completed xmlNode for this object
 */
wxXmlNode* Fertilizer::Save(wxXmlNode *gameNode)
{
    //Up-call to item class
    auto itemNode = Item::Save(gameNode);

    //Add type of plant
    itemNode->AddAttribute(L"type", L"fertilizer");

    //Return the Node
    return itemNode;
}