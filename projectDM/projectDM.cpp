#include "Graphs.h"
#include "TeamManager.h"
#include <filesystem>   // Подключение файловой системы
#include <fstream>      // Для работы с файлами
#include <iostream>     // Для ввода/вывода
#include <string>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    // Проверка наличия двух аргументов: входной и выходной файл
    if (argc < 6) {
        std::cerr << "Usage: projectDM.exe <input_file> <output_file> <budget> <alpha> <beta>\n";
        return 1;
    }

    fs::path inputPath = argv[1];   // Путь к входному файлу
    fs::path outputPath = argv[2];  // Путь к выходному файлу

    int totalBalance = std::stoi(argv[3]); // Бюджет на выбор команды

    float alpha = std::stof(argv[4]); // Коэф альфа
    float beta = std::stof(argv[5]); // Коэф бета

    // Проверка существования входного файла
    if (!fs::exists(inputPath)) {
        std::cerr << "Input file does not exist: " << inputPath << std::endl;
        return 1;
    }


    // Создание цветного языкового мультиграфа
    coloredMultiGraph languageGraph(inputPath.string());

    // Выделение подграфов по языкам (цветам)
    std::unordered_map<std::string, std::vector<Player>> subGraphs = getSubGraphs(languageGraph);

    // Создание множества всех команд (пятёрок) подходящих по языку и бюджету
    std::vector<Team> TotalTeams = getTotalTeams(subGraphs, totalBalance);

    // Выборка лучшей команды из множества всех команд
    Team bestTeam = findBestTeam(TotalTeams, alpha, beta);

    // Открытие выходного файла для записи результата
    std::ofstream fout(outputPath);
    if (!fout) {
        std::cerr << "Cannot write to output file: " << outputPath << std::endl;
        return 1;
    }

    for (const Player& player : bestTeam.players) {
        // ФИО и никнейм
        fout << player.nickname << " "
            << player.FIO.first << " "
            << player.FIO.last << " "
            << player.FIO.patronymic << " ";

        // Роль
        fout << roleToString(player.role) << " ";

        // Языки
        for (const auto& lang : player.langs)
            fout << lang << " ";

        // Стоимость
        fout << player.cost << " ";

        // Индивидуальные параметры
        fout << player.paramsInd.at("winRate") << " "
            << player.paramsInd.at("KD") << " "
            << player.paramsInd.at("HeadRate") << " "
            << player.paramsInd.at("hours") << " "
            << player.paramsInd.at("HLTV") << " "
            << player.paramsInd.at("ADR") << " ";

        // Командные параметры
        fout << player.paramsComp.at("couchRate") << " "
            << player.paramsComp.at("E") << " "
            << player.paramsComp.at("R") << " "
            << player.paramsComp.at("O") << " "
            << player.paramsComp.at("K") << " "
            << player.paramsComp.at("A") << "\n";
    }

    return 0;
}