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

public:
    WateringCan(Game *game);
    bool CanDelete() override;
    void Click() override;
};



#endif //WATERINGCAN_H
