/**
 * @file Rose.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Rose.h"

/**
 * Constructor
 * @param game Game this rose belongs to
 */
Rose::Rose(Game* game) : Plant(game, L"rose_1.png")
{
    //Simple up-call
}

/**
 * Function to save the state of this Rose
 * @param gameNode root node of XML
 * @return a completed xmlNode for this object
 */
wxXmlNode* Rose::Save(wxXmlNode *gameNode)
{
    //Up-call to item class
    auto itemNode = Item::Save(gameNode);

    //Add type of plant
    itemNode->AddAttribute(L"type", L"rose");

    //Return the Node
    return itemNode;
}

/**
 * A Function to Toggle The State of the Plant
 */
void Rose::Click()
{

}