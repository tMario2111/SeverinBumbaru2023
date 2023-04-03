#pragma once

#include <nlohmann/json.hpp> 

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

class GameData
{
public:
    GameData();
    nlohmann::json& operator[](const std::string& str);
private:
    std::unordered_map<std::string, nlohmann::json> data;
};