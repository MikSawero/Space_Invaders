#include "FileManager.hpp"

namespace ms
{
    std::filesystem::path FileManager::directory_path = "Scores";
    std::filesystem::path FileManager::file_path = directory_path / "scores.txt";
    std::vector<info> FileManager::scores;

    FileManager::FileManager()
    {

        try {
            CreateFile();

            std::ifstream file(file_path);
            std::string line;

            if (file.is_open()) {
                while (std::getline(file, line)) {
                    std::istringstream iss(line);
                    std::string name, data, string_score;            
                    std::getline(iss, name, ' ');
                    std::getline(iss, string_score, ' ');
                    std::getline(iss, data, ' ');
                    info temp = { name, std::stoi(string_score), data};
                    scores.emplace_back(temp);
                }
                file.close();
            }
            else {
                std::cerr << "Unable to open file for reading: " << file_path << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception in FileManager constructor: " << e.what() << std::endl;
        }
    }

    void FileManager::CreateFile() {
        try {
            if (!CheckIfExists()) {
                std::filesystem::create_directory(directory_path);
                std::ofstream file(file_path); // This creates the file
                if (file) {
                    std::cout << "File created: " << file_path << std::endl;
                }
                else {
                    std::cerr << "Failed to create file: " << file_path << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception in CreateFile: " << e.what() << std::endl;
        }
    }

    bool FileManager::CheckIfExists() {
        return std::filesystem::exists(directory_path) && std::filesystem::exists(file_path);
    }

    std::vector<info> FileManager::GetScores()
    {
        return scores;
    }

    void FileManager::SaveScore(const std::string& name, int points) {
        try {
            time_t _tm = time(nullptr);
            struct tm curtime;
            localtime_s(&curtime, &_tm);
            std::ostringstream oss;
            oss << std::put_time(&curtime, "%Y-%m-%d %H:%M:%S");
            std::string data = oss.str();
            scores.emplace_back(name, points, data);
            std::ofstream file(file_path, std::ios::app);
            if (file.is_open()) {
                file << name << " " << points << " " << data << std::endl;
                file.close();
            }
            else {
                std::cerr << "Unable to open file for writing: " << file_path << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception in SaveScore: " << e.what() << std::endl;
        }
    }
}