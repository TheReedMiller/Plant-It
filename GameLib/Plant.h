/**
 * @file Plant.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef PLANT_H
#define PLANT_H

#include "Item.h"

//Forward References
class Game;

/**
 * A class that describes a Plant object
 */
class Plant : public Item{
private:

public:
    Plant(Game* game, const wxString& filename);
};



#endif //PLANT_H
