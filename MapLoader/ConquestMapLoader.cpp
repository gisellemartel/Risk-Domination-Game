//
// Created by Giselle Martel on 2019-11-26.
//

#include "ConquestMapLoader.h"


//ConquestMapLoader class (ADAPTEE)-------------------------------------------------------------------------------------
ConquestMapLoader::ConquestMapLoader(string file_name) {

    cout << "Creating ConquestMapLoader object for file: " << file_name << endl;
    string map_name = Utility::StripString(file_name, "/", ".");
    file_name_ = file_name;
    parsed_map_ = new Map(map_name);
}

ConquestMapLoader::ConquestMapLoader(const ConquestMapLoader &conquest_map_loader) {
    file_name_ = conquest_map_loader.file_name_;
    *parsed_map_ = *conquest_map_loader.parsed_map_;
    delete conquest_map_loader.parsed_map_;
}

ConquestMapLoader::~ConquestMapLoader() {
    delete parsed_map_;
    parsed_map_ = nullptr;
}

ConquestMapLoader &ConquestMapLoader::operator=(const ConquestMapLoader &conquest_map_loader) {

    if(this != &conquest_map_loader) {
        file_name_ = conquest_map_loader.file_name_;
        *parsed_map_ = *conquest_map_loader.parsed_map_;
        delete conquest_map_loader.parsed_map_;
    }
    return *this;
}

Map* ConquestMapLoader::GetParsedConquestMap() const {
    return parsed_map_;
}

bool ConquestMapLoader::ParseConquestMap() {
    cout << "Starting to parse conquest map file...\n";

    string line;
    vector< string> neighbours;
    char line_delim = '\n';
    ifstream file_to_load(file_name_);
    if (file_to_load.peek() == ifstream::traits_type::eof()) {
        cout << "File is empty! Please load a another file\n";
        return false;
    }

    map<int, string> country_neighbours_map;

    if (file_to_load.is_open()) {
        int border_entry_count = 0;
        //read contents of .map file line by line
        while (getline(file_to_load, line, line_delim)) {
            //if line is empty or line is comment, skip it
            if (line.length() == 0) {
                continue;
            }

            //parse the data in the continents section
            if (line.find("[Continents]") == 0) {
                //get the next line
                int current_id = 1;
                while (getline(file_to_load, line, line_delim)) {
                    bool line_is_valid = line.find('[') == -1 && line[0] != '\r';
                    //we have reached the end of the continents section
                    if (!line_is_valid) {
                        break;
                    } else if (line[0] == '\n' || line.length() == 0) {
                        continue;
                    } else {
                        string continent_data = line;
                        string delim = "=";
                        //parse the name of the continent
                        string continent_name = Utility::StripString(continent_data, "", delim);
                        continent_data.erase(0, continent_name.length() + delim.length());

                        if (continent_data.length() == 0) {
                            cout << "continent " << continent_name
                                 << " is missing an army value. Please load a valid file\n\n";
                            return false;
                        }

                        //parse the army value of the continent

                        int army_value;

                        try {
                            army_value = stoi(continent_data);
                        } catch (const invalid_argument &e) {
                            cout << "the army value for continent " << continent_name
                                 << " is invalid. Please load a valid file.\n\n";
                            return false;
                        }

                        //debug string
                        //cout << continent_name << " " << army_value << endl;

                        parsed_map_->AddContinentToMap(continent_name, army_value, current_id);
                        if(parsed_map_->GetNumContinents() > 32) {
                            cout << file_name_ << " contains too many continents! Please load a valid map file!\n";
                            return false;
                        }
                        ++current_id;
                    }
                }
            }

            //parse the data in the countries  section
            if (line.find("[Territories]") == 0) {
                if (parsed_map_->GetNumContinents() == 0) {
                    cout << "Failed to generate map, file was missing continents!\n";
                    return false;
                }
                int current_index = 1;
                map<int, string> country_neighbours_map;

                //get the next line
                while (getline(file_to_load, line, line_delim)) {
                    bool line_is_valid = line.find('[') == -1;
                    //we have reached the end of the continents section
                    if (!line_is_valid) {
                        break;
                    } else if (line[0] == '\r' || line[0] == '\n' || line.length() == 0) {
                        continue;
                    } else {
                        string country_data = line;
                        string delim = ",";

                        // remove last char "\r" from the string
                        if(country_data.at(country_data.length() - 1) == '\r') {
                            country_data.erase(country_data.size() - 1);
                        }

                        int country_num = current_index;

                        string country_name = Utility::StripString(country_data, "", delim);
                        country_data.erase(0, country_name.length() + delim.length());

                        if (country_data.length() == 0) {
                            cout << "country " << country_num
                                 << " Country Data is not complete. Please load a valid file\n";
                            return false;
                        }


                        string x_coordinate_str = Utility::StripString(country_data, "", delim);
                        int x_coordinate;

                        try {
                            x_coordinate = stoi(x_coordinate_str);
                        } catch (const invalid_argument &e) {
                            cout << "the X coordinate for country" << country_num
                                 << " is invalid. Please load a valid file.\n";
                            return false;
                        }
                        country_data.erase(0, x_coordinate_str.length() + delim.length());

                        if (country_data.length() == 0) {
                            //throw error
                            cout << "country " << country_num
                                 << " is missing its Y coordinate. Please load a valid file\n";
                            return false;
                        }

                        string y_coordinate_str = Utility::StripString(country_data, "", delim);
                        int y_coordinate;

                        try {
                            y_coordinate = stoi(y_coordinate_str);
                        } catch (const invalid_argument &e) {
                            cout << "the Y coordinate for country" << country_name
                                 << " is invalid. Please load a valid file.\n";
                            return false;
                        }
                        country_data.erase(0, y_coordinate_str.length() + delim.length());

                        string continent_name = Utility::StripString(country_data, "", delim);
                        country_data.erase(0, continent_name.length() + delim.length());

                        Continent* continent = parsed_map_->GetContinentByName(continent_name);

                        if(!continent) {
                            cout << "the name given for continent " << continent_name << " for country " << country_name
                                 << " is invalid. Please load a valid file.\n";
                            return false;
                        }

                        int continent_index = continent->GetContinentID();

                        if (country_data.length() == 0) {
                            cout << "country " << country_num
                                 << " is missing its neighbours. Please load a valid file\n";
                            return false;
                        }

                        country_data.append(delim);

                        if(country_data.length() > 0) {
                            country_neighbours_map.insert({country_num, country_data});
                        }

                        //debug string
                        //cout << country_num << " " << continent_name << " " << continent_index << " " << x_coordinate << " " << y_coordinate << endl;

                        parsed_map_->AddCountryToMap(country_num, country_name, continent_index, x_coordinate,
                                                     y_coordinate);

                        if(parsed_map_->GetNumCountries() > 255) {
                            cout << file_name_ << " contains too many territories! Please load a valid map file!\n";
                            return false;
                        }
                        ++current_index;
                    }
                }

                if (parsed_map_->GetNumCountries() > 0) {
                    parsed_map_->CreateAdjacencyMatrix();
                } else {
                    cout << "File contains no territories!\n";
                    return false;
                }

                for(auto& entry : country_neighbours_map) {
                    Country* country = parsed_map_->GetCountryById(entry.first);

                    if(!country) {
                        return false;
                    }

                    string neighbours_list = entry.second;

                    if(neighbours_list.empty()) {
                        cout << "No neighbours found for " << *country->GetCountryName() << endl;
                        return false;
                    }

                    int country_counter = 0;
                    string delim = ",";
                    auto start = 0U;
                    auto end = neighbours_list.find(delim);
                    while(end != string::npos) {
                        string neighbour_name = neighbours_list.substr(start, end - start);
                        Country* neighbour = parsed_map_->GetCountryByName(neighbour_name);

                        if(!neighbour) {
                            cout << "Invalid neighbour found in file!\n";
                            return false;
                        }

                        int neighbour_index = neighbour->GetCountryID() - 1;
                        parsed_map_->SetTwoCountriesAsNeighbours(true, (entry.first - 1), (neighbour_index));

                        start = end + delim.length();
                        end = neighbours_list.find(delim, start);

                        ++country_counter;
                        if(country_counter > 10) {
                            cout << *parsed_map_->GetCountryById(entry.first)->GetCountryName() << " has more than 10 neighbours! Invalid file\n";
                            return false;
                        }
                    }
                }

            }
        }

        file_to_load.close();

        if (parsed_map_->GetNumCountries() == 0 || parsed_map_->GetNumContinents() == 0) {
            cout << "Failed to generate map for file " << file_name_ << ". It is missing territories or continents.\n";
            return false;
        }

        return true;

    } else {
        cout << "unable to open the file " << file_name_ << ". Please try again\n";
        return false;
    }
}
