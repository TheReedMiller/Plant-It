/**
 * @file Item.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef ITEM_H
#define ITEM_H

class Game;

/**
 * This BASE class describes items found within the game
 */
class Item {
protected:
    Item(Game *game, const wxString& filename);   //Constructor

private:
    ///Game object that this item belongs to
    Game *mGame = nullptr;

    ///X-coordinate of this item
    double mX = 0;
    ///Y-coordinate of this item
    double mY = 0;

    /// The image file name
    std::wstring mImageFileName;
    /// The underlying item image
    std::unique_ptr<wxImage> mItemImage;
    /// The bitmap we can display for this item
    std::unique_ptr<wxBitmap> mItemBitmap;

public:

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    virtual ~Item();
    virtual void Draw(std::shared_ptr<wxGraphicsContext> gc);
    virtual bool HitTest(int x, int y);
    virtual wxXmlNode* Save(wxXmlNode* root);
    virtual void Load(wxXmlNode* childNode);
    void SetImage(const std::wstring& file);

    /**
     * Function to determine what Item this is
     * @return string representing what this item is
     */
    virtual std::wstring GetItemName(){return L"Item";}
    /**
     * Function to activate an item when clicked on
     */
    virtual void Click(){}
    /**
     * A function to toggle the state of this item
     */
    virtual void Toggle(){}
    virtual void Update(double elapsed){}
    /// Assignment Operator
    Item &operator=(const Item &) = delete;

    /**
     * Getter for mX
     * @return the Value of mX
     */
    double getX() const { return mX; }

    /**
     * Getter for mY
     * @return value for mY
     */
    double getY() const { return mY; }

    void SetPosition(double x, double y);

    /**
     * Getter for X coord
     * @return x coord
     */
    double GetX() const { return mX; }

    /**
     * Getter for Y coord
     * @return Y coord
     */
    double GetY() const { return mY; }

    /**
     * Getter for the bitmap
     * @return Bitmap for this item
     */
    wxBitmap* GetBitmap() const { return mItemBitmap.get(); }

    /**
     * Getter for the game
     * @return Game that this item belongs to
     */
    Game* GetGame() const { return mGame; }

    /**
     * Checks if this item is in the dry state
     * @return bool if this object is currently is the dry state
     */
    virtual bool IsDry() { return false; }

    /**
     * A function that tells if this item can be watered or not
     * @return Bool representing if it can be watered or not
     */
    virtual bool IsWaterable(){return false;}
};



#endif //ITEM_H
