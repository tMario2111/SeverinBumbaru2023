#include "GameData.hpp"

GameData::GameData()
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator("data"))
    {
        if (!std::filesystem::is_regular_file(entry))
            continue;

        std::ifstream file{ entry.path().string() };
        file >> data[entry.path().stem().string()];
        file.close();
    }
}

nlohmann::json& GameData::operator[](const std::string& str)
{
    if (data.count(str) == 0)
    {
        std::cerr << "Json file " << str << " not found\n";
        exit(-1);
    }
    return data[str];
}