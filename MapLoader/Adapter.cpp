//
// Created by Giselle Martel on 2019-11-26.
//

#include "Adapter.h"


//Adapter class --------------------------------------------------------------------------------------------------------

Adapter::Adapter(ConquestMapLoader *conquest_map_loader) : MapLoader() {
    conquest_map_loader_ = conquest_map_loader;
}

Adapter::Adapter(const Adapter &adapter) : MapLoader(adapter) {
    *conquest_map_loader_ = *adapter.conquest_map_loader_;
    delete adapter.conquest_map_loader_;
}

Adapter::~Adapter() {
    delete conquest_map_loader_;
    conquest_map_loader_ = nullptr;
}

Adapter &Adapter::operator=(const Adapter &adapter) {
    *conquest_map_loader_ = *adapter.conquest_map_loader_;
    delete adapter.conquest_map_loader_;
    return *this;
}

bool Adapter::ParseMap() {
    return conquest_map_loader_->ParseConquestMap();
}