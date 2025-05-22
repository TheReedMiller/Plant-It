/**
 * @file WateringCan.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef WATERINGCAN_H
#define WATERINGCAN_H

#include "Item.h"

/**
 * A Class that Describes a Watering Can within our Game
 */
class WateringCan : public Item{
private:
    ///Bool representing if this watering can is currently active
    bool mIsActive = false;
    ///Bool saying if the watering can is heading down
    bool mIsDown = true;
    ///Current angle of this item
    double mCurrentAngle = 0;
    /// The underlying droplet image
    std::unique_ptr<wxImage> mDropImage = nullptr;
    ///Bitmap for water Droplet image
    std::unique_ptr<wxBitmap> mDropBitmap = nullptr;

public:
    WateringCan(Game *game);
    bool CanDelete() override;
    void Click() override;
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;
    void Update(double elapsed) override;
    wxXmlNode* Save(wxXmlNode* gameNode);
    void Water();

    /**
     * A function that tells if this item can be watered or not
     * @return Bool representing if it can be watered or not
     */
    virtual bool IsWaterable(){return false;}
};



#endif //WATERINGCAN_H
