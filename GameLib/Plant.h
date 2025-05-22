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
    ///A level of Dryness so that we can
    int mLevel = 0;

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
    bool IsDry() override;

    /**
     * A function that tells if this item can be watered or not
     * @return Bool representing if it can be watered or not
     */
    bool IsWaterable() override {return true;}

    /**
     * A function that updates the dry-level of this plant
     */
    void Update(){ mLevel++; }

    /**
     * Setter for dryness-level
     * @param level level to set
     */
    void SetLevel(int level){mLevel = level;}

    /**
     * Getter for Dryness-level
     * @return Level of this plant
     */
    int GetLevel(){return mLevel;}
};



#endif //PLANT_H
