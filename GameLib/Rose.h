/**
 * @file Rose.h
 * @author Reed Miller
 *
 *
 */
 
#ifndef ROSE_H
#define ROSE_H

#include "Plant.h"

/**
 * A Class that Describes a Rose Plant
 */
class Rose : public Plant{
private:

public:
    Rose(Game* game);
    wxXmlNode* Save(wxXmlNode* gameNode) override;
    void Toggle() override;
    void Load(wxXmlNode* childNode) override;
};



#endif //ROSE_H
