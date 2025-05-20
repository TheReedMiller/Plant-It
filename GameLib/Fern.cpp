/**
 * @file Fern.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Fern.h"
#include "Game.h"


/**
 * Constructor
 * @param game Game this Flytrap belongs to
 */
Fern::Fern(Game* game) : Plant(game, L"fern_1.png")
{
    //Simple up-call
}

/**
 * Function to save the state of this Fern
 * @param gameNode root node of XML
 * @return a completed xmlNode for this object
 */
wxXmlNode* Fern::Save(wxXmlNode *gameNode)
{
    //Up-call to item class
    auto itemNode = Item::Save(gameNode);

    //Add type of plant
    itemNode->AddAttribute(L"type", L"fern");

    //Return the Node
    return itemNode;
}

/**
 * A Function to Toggle The State of the Plant
 */
void Fern::Toggle()
{

}