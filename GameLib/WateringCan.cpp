/**
 * @file WateringCan.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "WateringCan.h"
#include "Game.h"

///Constant for headbutt speed
const double HeadbuttSpeed = 5;
///Constant for Headbutt angle
const double HeadButtAngle = 1.5;
/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"Images/";
///Constant for Droplet Offset X
const int DropXOffset = 110;
///Constant for Droplet Offset Y
const int DropYOffset = 40;


/**
 * Constructor
 */
WateringCan::WateringCan(Game *game) : Item(game, L"wateringcan.png")
{
    //Create Bitmap and Image for Water Drop
    mDropImage = std::make_unique<wxImage>( ImagesDirectory +L"waterdrop.png", wxBITMAP_TYPE_ANY);
    mDropBitmap = std::make_unique<wxBitmap>(*mDropImage);
}

/**
 * Removes the Ability to delete this item
 * @return Bool telling that this item cannot be deleted
 */
bool WateringCan::CanDelete()
{
    return false;
}

/**
 * Click this item, and begin 'watering' rotation
 */
void WateringCan::Click()
{
    //Activate the Watering can for animation
    mIsActive = true;
}

/**
 * Special Draw function for this watering can
 * @param gc object we are drawing on
 */
void WateringCan::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    //Get the Bitmap Pointer
    auto bitmap = Item::GetBitmap();

    //If this object is in the Active Animation state, rotate and draw
    if (mIsActive)
    {
        //Perform the Rotation of the Object
        gc->PushState();
        gc->Translate(GetX(), GetY());
        gc->Rotate(mCurrentAngle);
        gc->Translate(-GetX(), -GetY());

        //Draw the Item
        Item::Draw(gc);

        //Draw Droplet
        wxDouble x = GetX() - DropXOffset;
        wxDouble y = GetY() - DropYOffset;
        gc->DrawBitmap(*mDropBitmap, x, y, mDropBitmap->GetWidth(), mDropBitmap->GetHeight());

        //Pop the GC
        gc->PopState();
    }

    //otherwise just draw
    else
    {
        //Call to base Class to Draw
        Item::Draw(gc);
    }
}

/**
 * Updates the watering can for animation
 * @param elapsed time elapsed since last update
 */
void WateringCan::Update(double elapsed)
{
    if (mIsActive)
    {
        //Check which part of the animation state it is in
        if (mIsDown)
        {

            mCurrentAngle -= elapsed * HeadbuttSpeed;
            if (mCurrentAngle <= -HeadButtAngle)
            {
                mIsDown = false;
            }
        }
        else
        {
            mCurrentAngle += elapsed * HeadbuttSpeed;
            if (mCurrentAngle >= 0)
            {
                //Reset all Variables
                mIsActive = false;
                mIsDown = true;
                mCurrentAngle = 0;

                //Call to game to actually water
                Water();
            }
        }
    }
}

/**
 * Function to save the state of this Watering Can
 * @param gameNode root node of XML
 * @return a completed xmlNode for this object
 */
wxXmlNode* WateringCan::Save(wxXmlNode *gameNode)
{
    //Don't save this item
}

/**
 * This function completed the 'watering' action at the end of animation
 */
void WateringCan::Water()
{
    //Call to Game to Try and Water a plant
    GetGame()->WaterPlant(GetX(), GetY());
}