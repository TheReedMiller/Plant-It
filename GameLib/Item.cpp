/**
 * @file Item.cpp
 * @author Reed Miller
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"
#include <memory>

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/Images/";


/**
 * Constructor
 * @param game The game this item is a member of
 */
Item::Item(Game *game, const wxString& filename, const std::wstring &resourseDir) : mGame(game),
mImageFileName(filename), mResourseDir(resourseDir)
{
    //Set Image and Bitmap
    mItemImage = std::make_unique<wxImage>( mResourseDir + ImagesDirectory + filename, wxBITMAP_TYPE_ANY);
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
 * @param gc graphics to draw on
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
    gc->DrawBitmap(*mItemBitmap,int(GetX() - wid / 2),int(GetY() - hit / 2), wid, hit);
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
    // return !mItemImage->IsTransparent((int)testX, (int)testY);
    return true;
}

/**
 * Function to save the state of this Item
 * @param gameNode root node of XML
 * @return a completed xmlNode for this object
 */
wxXmlNode* Item::Save(wxXmlNode *gameNode)
{
    //Create Child node and Append
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");
    gameNode->AddChild(itemNode);

    //Add Position Attributes
    itemNode->AddAttribute(L"x", wxString::FromDouble(mX));
    itemNode->AddAttribute(L"y", wxString::FromDouble(mY));

    //Return the Completed Node
    return itemNode;
}

/**
 * Load in this item from xml
 * @param childNode node to load xml data from
 */
void Item::Load(wxXmlNode *childNode)
{
    childNode->GetAttribute(L"x", L"0").ToDouble(&mX);
    childNode->GetAttribute(L"y", L"0").ToDouble(&mY);
}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void Item::SetImage(const std::wstring &file)
{
    if (!file.empty())
    {
        std::wstring filename = mResourseDir + ImagesDirectory + file;
        mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
        mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
    }
    else
    {
        mItemImage.release();
        mItemBitmap.release();
    }
}