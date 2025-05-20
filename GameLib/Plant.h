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
    /// Possible Plant states
    enum class State {Watered, Dry};
    /// The current Plant state
    State mState = State::Watered;

public:
    Plant(Game* game, const wxString& filename);
    void SetImage(const std::wstring& file);

    /**
     * Getter for the Underlying plant image name
     * @return filename for this plant image
     */
    std::wstring GetImage(){return  mPlantImageFile; }

    void SetState(std::wstring state);
    std::wstring GetState();
};



#endif //PLANT_H
