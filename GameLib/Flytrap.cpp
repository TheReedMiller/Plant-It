/**
 * @file Flytrap.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Flytrap.h"

///Constant for Watered FileName
const std::wstring RegFlytrapImage = L"flytrap_1.png";
///Constant for Dry FileName
const std::wstring DryFlytrapImage = L"flytrap_2.png";

/**
 * Constructor
 * @param game Game this Flytrap belongs to
 */
Flytrap::Flytrap(Game* game) : Plant(game,RegFlytrapImage )
{
    //Set the MaxLevel for Flytrap
    SetMaxLevel(1000);
}

/**
 * Function to save the state of this Flytrap
 * @param gameNode root node of XML
 * @return a completed xmlNode for this object
 */
wxXmlNode* Flytrap::Save(wxXmlNode *gameNode)
{
    //Up-call to item class
    auto itemNode = Item::Save(gameNode);

    //Add type of plant
    itemNode->AddAttribute(L"type", L"flytrap");

    //Return the Node
    return itemNode;
}

/**
 * A Function to Toggle The State of the Plant
 */
void Flytrap::Click()
{
    //First we get the state
    auto state = GetState();

    //State is currently watered, flip it
    if (state == L"watered")
    {
        //Set New State
        SetState(L"dry");

        //Set new image and Bitmap
        SetImage(DryFlytrapImage);
    }

    //Otherwise state is Dry, flip it
    else
    {
        //Set New State
        SetState(L"watered");

        //Set ne Image and Bitmap
        SetImage(RegFlytrapImage);
    }
}