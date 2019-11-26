//
// Created by Giselle Martel on 2019-11-26.
//

#ifndef TEAMPROJECT_COMP345_ADAPTER_H
#define TEAMPROJECT_COMP345_ADAPTER_H

#include "MapLoader.h"
#include "ConquestMapLoader.h"

class ConquestMapLoader;
class MapLoader;

//Adapter class --------------------------------------------------------------------------------------------------------
class Adapter : public MapLoader {
private:
    ConquestMapLoader* conquest_map_loader_;

public:
    Adapter(ConquestMapLoader* conquest_map_loader);
    Adapter(const Adapter& adapter);
    ~Adapter();

    Adapter& operator=(const Adapter& adapter);


    bool ParseMap() override;
};


#endif //TEAMPROJECT_COMP345_ADAPTER_H
