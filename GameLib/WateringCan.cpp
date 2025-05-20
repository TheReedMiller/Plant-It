/**
 * @file WateringCan.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "WateringCan.h"

///Constant for headbutt speed
const double HeadbuttSpeed = 200;
///Constant for Headbutt angle
const double HeadButtAngle = 90;


/**
 * Constructor
 */
WateringCan::WateringCan(Game *game) : Item(game, L"wateringcan.png")
{
    //Simple Up-call
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
        gc->Rotate(wxDegToRad(mCurrentAngle));
        gc->Translate(-GetX(), -GetY());

        //Draw the Item
        Item::Draw(gc);

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
            }
        }
    }
}