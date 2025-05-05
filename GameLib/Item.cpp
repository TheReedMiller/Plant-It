/**
 * @file Item.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"images/";


/**
 * Constructor
 * @param game The game this item is a member of
 */
Item::Item(Game *game, const wxString& filename) : mGame(game), mImageFileName(filename)
{
    //Set Image and Bitmap
    mItemImage = std::make_unique<wxImage>( ImagesDirectory + filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
}

/**
 * This function sets the positions of the item
 * @param x X coordinate we want to set
 * @param y Y coordinate we want to set
 */
void Item::SetPosition(double x, double y)
{
    //Get stuff
    mX = x;
    mY = y;
}

/**
 * Destructor for this item
 */
Item::~Item()
{

}

/**
 * Function to draw this item
 * @param dc dc to draw on
 */
void Item::Draw(wxDC* dc)
{
    dc->DrawBitmap(*mItemBitmap, mX, mY);
}