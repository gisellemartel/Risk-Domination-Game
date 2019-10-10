/**
 * Assignment #1 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <stdexcept>
#include <string>
#include <iostream>

#include "MapLoader.h"

using namespace std;

MapLoader::MapLoader(string file_name) {
    cout << "Creating MapLoader object for file: " << file_name << endl;
    string map_name = StripString(file_name, "/", ".");
    file_name_ = file_name;
    parsed_map_ = new Map(map_name);
}

MapLoader::MapLoader(const MapLoader &map) {
    file_name_ = map.file_name_;
    parsed_map_ = map.parsed_map_;
}

MapLoader::~MapLoader() {
    delete parsed_map_;
}

MapLoader& MapLoader::operator=(const MapLoader &map) {
    file_name_ = map.file_name_;
    parsed_map_ = map.parsed_map_;
    return *this;
}

Map* MapLoader::GetParsedMap() const {
    return parsed_map_;
}

//returns a substring in between 2 specified delimiters
string MapLoader::StripString(string string_to_strip, string left_delim, string right_delim) {
    if((left_delim.length() == 0 && right_delim.length() == 0) || string_to_strip.length() < 2) {
        return string_to_strip;
    }

    if(left_delim.length() == 0) {
        return string_to_strip.substr(0, string_to_strip.find(right_delim));
    }

    if(right_delim.length() == 0) {
        return string_to_strip.substr(string_to_strip.find(left_delim) + 1, string_to_strip.length() - 1);
    }

    if (string_to_strip.length() > 2){
        string stripped_string = string_to_strip.substr(string_to_strip.find(left_delim));
        return stripped_string.substr(1, stripped_string.find(right_delim) - 1);
    }

    else {
        return string_to_strip;
    }
}

void MapLoader::ParseMap() {
    string line;
    ifstream file_to_load(file_name_);
    if(file_to_load.peek() == ifstream::traits_type::eof()) {
        cout << "File is empty! Please load a another file\n\n";
        return;
    }

    if(file_to_load.is_open()) {
        int border_entry_count = 0;
        //read contents of .map file line by line
        while (getline (file_to_load,line, '\n'))
        {
            //if line is empty or line is comment, skip it
           if(line.length() == 0 ||  line.at(0) == ';') {
               continue;
           }

           //parse the data in the continents section
           if(line.find("[continents]") == 0) {
               //get the next line
               int current_id = 0;
               while(getline (file_to_load,line, '\n')) {
                   bool line_is_valid = line.find("[") == -1 && line[0] != '\r';
                   //we have reached the end of the continents section
                   if(!line_is_valid) {
                       break;
                   } else if (line[0] == '\n' || line.length() == 0) {
                       continue;
                   } else {
                       string continent_data = line;
                       string delim = " ";
                       //parse the name of the continent
                       string continent_name = StripString(continent_data, "", delim);
                       continent_data.erase(0, continent_name.length() + delim.length());

                       if(continent_data.length() == 0) {
                           cout << "continent " << continent_name << " is missing an army value. Please load a valid file\n\n";
                           return;
                       }

                       //parse the army value of the continent
                       string army_value_str = StripString(continent_data, "", delim);
                       int army_value;

                       try {
                           army_value = stoi(army_value_str);
                       } catch (const invalid_argument& e) {
                           cout << "the army value for continent " << continent_name << " is invalid. Please load a valid file.\n\n";
                           return;
                       }

                       //debug string
                      //cout << continent_name << " " << army_value << endl;

                       parsed_map_->AddContinentToMap(continent_name, army_value, current_id);
                       ++current_id;
                   }
               }
           }

            //parse the data in the countries  section
            if(line.find("[countries]") == 0) {
                if(parsed_map_->GetNumContinents() == 0) {
                    cout << "Failed to generate map, file was missing continents!\n\n";
                    return;
                }
                int current_index = 0;
                //get the next line
                while(getline (file_to_load,line, '\n')) {
                    bool line_is_valid = line.find("[") == -1 && line[0] != '\r';
                    //we have reached the end of the continents section
                    if(!line_is_valid) {
                      break;
                    } else if (line[0] == '\n' || line.length() == 0) {
                        continue;
                    } else {
                        string country_data = line;
                        string delim = " ";
                        //parse the name of the continent
                        string country_num_str = StripString(country_data, "", delim);
                        int country_num;

                        try {
                            country_num = stoi(country_num_str);
                        } catch (const invalid_argument& e) {
                            cout << "the country number is invalid. Please load a valid file.\n\n";
                            return;
                        }

                        Country* country = parsed_map_->GetCountryById(current_index);
                        //ensure countries are in order
                        if(country_num !=0 && parsed_map_->GetNumCountries() > 0 && country && country_num < country->GetCountryID()) {
                            cout << "Countries are not in order in the file. Please load a valid file\n\n";
                            return;
                        }

                        country_data.erase(0, country_num_str.length() + delim.length());

                        if(country_data.length() == 0) {
                            cout << "country " << country_num << " is not associated to any continent. Please load a valid file\n\n";
                            return;
                        }

                        string continent_name = StripString(country_data, "", delim);
                        country_data.erase(0, continent_name.length() + delim.length());

                        if(country_data.length() == 0) {
                            cout << "country " << country_num << " continent is missing its index value. Please load a valid file\n\n";
                            return;
                        }

                        string continent_index_str = StripString(country_data, "", delim);
                        int continent_index;

                        try {
                            continent_index = stoi(continent_index_str);
                        } catch (const invalid_argument& e) {
                            cout << "the index given for continent " << continent_name << " for country " << country_num << " is invalid. Please load a valid file.\n\n";
                            return;
                        }
                        country_data.erase(0, continent_index_str.length() + delim.length());

                        if(country_data.length() == 0) {
                            cout << "country " << country_num << " is missing its X coordinate. Please load a valid file\n\n";
                            return;
                        }

                        string x_coordinate_str = StripString(country_data, "", delim);
                        int x_coordinate;

                        try {
                            x_coordinate = stoi(x_coordinate_str);
                        } catch (const invalid_argument& e) {
                            cout << "the X coordinate for country" << country_num << " is invalid. Please load a valid file.\n\n";
                            return;
                        }
                        country_data.erase(0, x_coordinate_str.length() + delim.length());

                        if(country_data.length() == 0) {
                            //throw error
                            cout << "country " << country_num << " is missing its Y coordinate. Please load a valid file\n\n";
                            return;
                        }

                        string y_coordinate_str = StripString(country_data, "", delim);
                        int y_coordinate;

                        try {
                            y_coordinate =  stoi(y_coordinate_str);
                        } catch (const invalid_argument& e) {
                            cout << "the Y coordinate for country" << country_num << " is invalid. Please load a valid file.\n\n";
                            return;
                        }
                        country_data.erase(0, y_coordinate_str.length() + delim.length());

                        //debug string
                        //cout << country_num << " " << continent_name << " " << continent_index << " " << x_coordinate << " " << y_coordinate << endl;

                        parsed_map_->AddCountryToMap(country_num, continent_name, continent_index, x_coordinate, y_coordinate);
                        ++current_index;
                    }
                }

                if(parsed_map_->GetNumCountries() > 0) {
                    parsed_map_->CreateAdjacencyMatrix();
                }
            }

            //parse the data in the borders section
            if(line.find("[borders]") == 0) {

                if(parsed_map_->GetNumCountries() == 0) {
                    cout << "Failed to generate map, file was missing countries!\n\n";
                    return;
                }
                //get the next line
                int current_country = 0;
                while(getline (file_to_load,line, '\n')) {
                    bool line_is_valid = line.find("[") == -1 && line[0] != '\r';
                    //we have reached the end of the border section
                    if(!line_is_valid) {
                        break;
                    } else if (line[0] == '\n' || line.length() == 0) {
                        continue;
                    } else {
                        string border_data = line;
                        vector<int> borders;

                        while(border_data.length() > 0 && border_data[0] != '\r') {
                            string delim = " ";
                            string border_str = StripString(border_data, "", delim);
                            border_data.erase(0, border_str.length() + delim.length());

                            int border;
                            try{
                                border = stoi(border_str);
                                //border values start from 1 and end at last country
                                if(border < 0 || border > parsed_map_->GetNumCountries()) {
                                    cout << "invalid values given for border. Please load a valid file\n\n";
                                    return;
                                }
                                borders.push_back(border);
                            } catch( const invalid_argument& e) {
                                cout << "invalid values given for border. Please load a valid file\n\n";
                                return;
                            }

                            //debug string
                           // cout << border << " ";
                        }

                        if(borders.size() == 0) {
                            cout << "No borders specified for entry in borders section. Please load a valid file\n\n";
                            return;

                        } else if(borders.size() > parsed_map_->GetNumCountries()) {
                            cout << "File contains more border than there are countries. Please load a valid file.\n\n";
                            return;
                        } else {

                            for(int i = 1; i < borders.size(); ++i) {

                                if(borders[i] -1 == -1) {
                                    cout << "invalid values given for border. Please load a valid file\n\n";
                                    return;
                                }
                                if(i == current_country) {
                                    continue;
                                }
                                parsed_map_->SetTwoCountriesAsNeighbours(true, borders[0] - 1, borders[i] - 1);
                            }
                            ++current_country;
                            ++border_entry_count;
                        }

                        //debug string
                        //cout << endl;
                    }
                }
            }
        }
        file_to_load.close();

        if(border_entry_count == 0) {
            cout << "Failed to generate map, file was missing borders!\n\n";
            return;
        }

        if(border_entry_count != parsed_map_->GetNumCountries()) {
            cout << "Invalid values given for border. Please load a valid file!\n\n";
            return;
        }

        if(parsed_map_->GetNumCountries() == 0 && parsed_map_->GetNumContinents() == 0) {
            cout << "Failed to generate map for file " << file_name_ << "! Please try again\n\n";
            return;
        }

        cout << "Success! Generated map for file " << file_name_ << "!" << endl << "\nHere is the resulting graph:\n";
        parsed_map_->DisplayAdjacencyMatrix();
        cout << "**************************************************************************************************\n\n\n";

    } else {
        cout << "unable to open the file " << file_name_ << ". Please try again\n\n";
    }
}

