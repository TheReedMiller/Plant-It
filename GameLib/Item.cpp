/**
 * @file Item.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"Images/";


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
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
    dc->DrawBitmap(*mItemBitmap,
            int(GetX() - wid / 2),
            int(GetY() - hit / 2));
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(int x, int y)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to the image top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    return !mItemImage->IsTransparent((int)testX, (int)testY);
}