//
// Created by Giselle Martel on 2019-11-26.
//

#include "ConquestMapLoader.h"
#include "MapLoader.h"

class ConquestMapLoader;

//Adapter class --------------------------------------------------------------------------------------------------------
class Adapter : public MapLoader {
private:
    ConquestMapLoader* conquest_map_loader_;

public:
    Adapter() = default;
    explicit Adapter(ConquestMapLoader* conquest_map_loader);
    Adapter(const Adapter& adapter);
    ~Adapter() override;

    Adapter& operator=(const Adapter& adapter);


    bool ParseMap() override;
};
