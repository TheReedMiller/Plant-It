/**
 * @file Rose.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Rose.h"

///Constant for Watered FileName
const std::wstring RegRoseImage = L"rose_1.png";
///Constant for Dry FileName
const std::wstring DryRoseImage = L"rose_2.png";

/**
 * Constructor
 * @param game Game this rose belongs to
 */
Rose::Rose(Game* game) : Plant(game, RegRoseImage)
{
    //Set the MaxLevel for Rose
    SetMaxLevel(1000);
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
    //First we get the state
    auto state = GetState();

    //State is currently watered, flip it
    if (state == L"watered")
    {
        //Set New State
        SetState(L"dry");

        //Set new image and Bitmap
        SetImage(DryRoseImage);
    }

    //Otherwise state is Dry, flip it
    else
    {
        //Set New State
        SetState(L"watered");

        //Set the Image and Bitmap
        SetImage(RegRoseImage);

        //Reset the Level
        SetLevel(0);
    }
}
