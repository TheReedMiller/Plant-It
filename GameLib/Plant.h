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
    ///File name for the Current Plant image - used for altering from dry/watered states
    std::wstring mPlantImageFile;
public:
    Plant(Game* game, const wxString& filename);
    void SetImage(const std::wstring& file);

    /**
     * Getter for the Underlying plant image name
     * @return filename for this plant image
     */
    std::wstring GetImage(){return  mPlantImageFile; }

    /**
     * A Function to Toggle the State of the Plant
     */
    virtual void Toggle() = 0;  //MUST be overwritten by Derived Classes
};



#endif //PLANT_H
