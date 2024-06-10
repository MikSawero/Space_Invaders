#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <ctime>
#include <chrono>

namespace ms
{
    struct info
    {
        std::string name;
        int score;
        std::string date;
    };

    class FileManager
    {
    public:

        FileManager();

        static void CreateFile();
        static bool CheckIfExists();

        static std::vector<info> GetScores();
        static void SaveScore(const std::string& name, int points);

        static std::filesystem::path directory_path;
        static std::filesystem::path file_path;
        static std::vector<info> scores;

    };
}
