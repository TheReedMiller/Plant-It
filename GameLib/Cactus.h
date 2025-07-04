/**
 * @file Cactus.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef CACTUS_H
#define CACTUS_H

#include "Plant.h"

/**
 * A Class that describes a Cactus Plant
 */
class Cactus : public Plant {
private:

public:
    Cactus(Game* game, const std::wstring &resourseDir);
    wxXmlNode* Save(wxXmlNode* gameNode) override;
    void Toggle() override;
    void Load(wxXmlNode* childNode) override;
};



#endif //CACTUS_H
