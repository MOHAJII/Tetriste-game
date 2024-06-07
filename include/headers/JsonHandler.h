#pragma once
#include "json.hpp"
#include <fstream>
// #include <iostream>
using json = nlohmann::json;

class JsonHandler
{
public:
    static json ReadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return json();
        }

        json data;
        file >> data;
        file.close();

        return data;
    }

    static void WriteToFile(const json &data, const std::string &filename)
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file for writing: " << filename << std::endl;
            return;
        }

        file << std::setw(4) << data << std::endl;
        file.close();
    }
};
